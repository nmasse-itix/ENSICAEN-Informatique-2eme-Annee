/**
 * #(@)parser.y              ENSICAEN                       2005
 *
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/*
 * @version     05/04/2006
 *
 * done:        -
 *
 * todo:        -
 */

/**
 * @file parser.y
 *
 * Part of the Pascal grammar in Yacc format, based originally on BNF.
 * The grammar has been massaged somewhat to make it LALR, and limited
 * to integer type, and if and while control structure.
 */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Fonctions utilitaires */
#include "generator.h"

/* Header commun */
#include "epc.h"

/* voir le corps de la méthode ci-dessous */
int yyerror(char * s);

/** Le nom du programme, utilisée par yacc */
char * progname;
%}

/**
 * The list of attributes associated to each terminal
 * and non terminal of the grammar.
 */
%union {
   char strval[255]; /* The value of the token. */

   /**
    * This structure defines the convenient
    * information for building the code.
    */
   struct t_code {
      char* code;   /* The string that contains the 3 address code */
      char* place;  /* The name of the identifier or the temporary variable. */
      char* before; /* The name of the label before the code. */
      char* after;  /* The name of the label after the code. */
      char* type;   /* The name of the type (int, float, ...). */
   } code3a;
}

/* Les jetons */
%token AND ASSIGNMENT 
%token COLON COMMA DO DOT END EQUAL
%token GE GT IF IN INTEGER LBRAC LE
%token LPAREN LT MINUS NOT NOTEQUAL OF OR
%token PBEGIN PLUS
%token PROGRAM
%token RBRAC RPAREN
%token SEMICOLON DIV MULT THEN
%token VAR WHILE
%token <strval> IDENTIFIER
%token <strval> REALNUMBER
%token <strval> INTNUMBER
%token <strval> CHARACTER_STRING

/* Operator associativity. */
%left PLUS MINUS
%left OR AND NOT
%right MULT DIV

/* The axiom. */
%start program

/* Information de typage des non termimaux */
%type <code3a> identifier number term type_denoter sign
%type <code3a> compound_statement statement_sequence procedure_statement
%type <code3a> simple_expression expression instruction 
%type <code3a> actual_parameter_list relop variable_declaration
%type <code3a> program_heading block statement_part 
%%
program: program_heading SEMICOLON block DOT
    {
        puts("#include <stdio.h>");
        puts("#include <math.h>");
        puts($1.code);
        puts($3.code);
    }
	;
        
program_heading: PROGRAM identifier
    {
        init(&$$);
        $$.code = concat("/* nom du programme : '", $2.place, "' */", NULL);
    }
    ;

block: variable_declaration_part statement_part 
    {
        init(&$$);
        $$.code = concat("int main(void) {\n",
                         $2.code,
                         prod("return 0"),
                         "}\n", NULL);
    }
    ;
   
statement_part: compound_statement
   {
        init(&$$);
        $$.code = concat("  /* début des variables */\n",
                         genDeclarationVars(),
                         "  /* fin des variables */\n\n",
                         $1.code, NULL);
   }
    ;

variable_declaration_part : VAR variable_declaration_list SEMICOLON
   {
   }
	|
   {
   }
   ;
    
variable_declaration_list : variable_declaration_list SEMICOLON variable_declaration
   {
   }

	| variable_declaration
   {
   }

	;
variable_declaration : identifier COLON type_denoter
   {
       init(&$$);
       addType($1.place, $3.type);
       $$.type = $3.type;
   }
	| identifier COMMA variable_declaration
   {
       init(&$$);
       addType($1.place, $3.type);
       $$.type = $3.type;
   }

	;
type_denoter: INTEGER
   {
       init(&$$);
       $$.type = "int";
   }
        ;
    
compound_statement: PBEGIN statement_sequence SEMICOLON END
   {
       init(&$$);
       $$.code = concat("  { /* début du bloc */\n", $2.code, "  } /* fin du bloc */\n", NULL);
   }
	;
statement_sequence: instruction
   {
       init(&$$);
       $$.code = $1.code;
   }
	| statement_sequence SEMICOLON instruction 
   {
       init(&$$);
       $$.code = concat($1.code, $3.code, NULL);
   }
	;
/* INSTRUCTION */
instruction: identifier ASSIGNMENT expression   /* S -> id:=E */
   {
        init(&$$);
        $$.code = concat($3.code, prod(concat($1.place , " = ", $3.place, NULL)), NULL);
   }
	| procedure_statement /* S->procedure(args) */
   {
       $$ = $1; // pass through
   }
	| compound_statement /* S -> BEGIN S END */
   {
       $$ = $1; // pass through
   }
	| IF expression THEN instruction /* S -> IF THEN */
   {
        $$.after = newLabel();
        $$.code = concat($2.code,
                         prod(concat("if (", $2.place, " == 0) goto ", $$.after, NULL)),
                         $4.code,
                         prod(concat($$.after, ":", NULL)),
                         NULL);
   }
	| WHILE expression DO instruction /* S-> WHILE DO */
   {
        $$.before = newLabel();
        $$.after = newLabel();
        $$.code = concat(prod(concat($$.before, ":", NULL)), 
                         $2.code,
                         prod(concat("if (", $2.place, " == 0) goto ", $$.after, NULL)),
                         $4.code,
                         prod(concat("goto ", $$.before, NULL)),
                         prod(concat($$.after, ":", NULL)),
                         NULL);
   }
	;
/* PROCEDURE CALL */
procedure_statement: identifier /* no actual parameter list */
   {
        init(&$$);
        $$.code = prod(concat($1.place, "()", NULL));
        $$.type = "void";
   }
	| identifier LPAREN actual_parameter_list RPAREN /* with actual argument list */
   {
       init(&$$);
       $$.code = concat($3.code, prod(concat($1.place, "(", $3.place, ")", NULL)), NULL);
       $$.type= "void";
   }
	;
actual_parameter_list: expression
   {
       $$ = $1; // pass through
   }
	| actual_parameter_list COMMA expression
   {
       init(&$$);
       $$.code = concat($1.code, $3.code, NULL);
       $$.place = concat($1.place, ", ", $3.place, NULL);
   }
	;
/* EXPRESSIONS */
expression: simple_expression
   {
       $$ = $1; // pass through
   }
	| simple_expression relop simple_expression
   {
       init(&$$);
       $$.type = $1.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($1.code, $3.code, prod(concat($$.place, " = ", $1.place, " ", $2.code , " ", $3.place, NULL)), NULL);
   }
	;
simple_expression: term /* E -> T */
   {
       $$ = $1; // pass through
   }
	| sign term /* E-> +/- T */
   {
       init(&$$);
       $$.type = $2.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($2.code, 
                        prod(concat($$.place, " = ", $1.code, " ", $2.place, NULL)), 
                        NULL);
   }
	| NOT simple_expression /* E-> NOT E */
   {
       init(&$$);
       $$.type = $2.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($2.code, 
                        prod(concat($$.place, " = ! ", $2.place, NULL)), 
                        NULL);
       
   }
	| simple_expression PLUS simple_expression  /* E -> E + E */
   {
       init(&$$);
       $$.type = $1.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($1.code, $3.code, prod(concat($$.place, " = ", $1.place, " + ", $3.place, NULL)), NULL);
   }
	| simple_expression MINUS simple_expression  /* E -> E - E */
   {
       init(&$$);
       $$.type = $1.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($1.code, $3.code, prod(concat($$.place, " = ", $1.place, " - ", $3.place, NULL)), NULL);
   }
	| simple_expression MULT simple_expression  /* E -> E * E */
   {
       init(&$$);
       $$.type = $1.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($1.code, $3.code, prod(concat($$.place, " = ", $1.place, " * ", $3.place, NULL)), NULL);
   }
	| simple_expression DIV  simple_expression  /* E -> E / E */
   {
       init(&$$);
       $$.type = $1.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($1.code, $3.code, prod(concat($$.place, " = ", $1.place, " / ", $3.place, NULL)), NULL);
   }
	| simple_expression AND  simple_expression  /* E -> E AND E */
   {
       init(&$$);
       $$.type = $1.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($1.code, $3.code, prod(concat($$.place, " = ", $1.place, " && ", $3.place, NULL)), NULL);
   }
	| simple_expression OR  simple_expression  /* E -> E OR E */
   {
       init(&$$);
       $$.type = $1.type; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($1.code, $3.code, prod(concat($$.place, " = ", $1.place, " || ", $3.place, NULL)), NULL);
   }
	| LPAREN expression RPAREN  /* E -> (E) */
   {
        $$ = $2; // pass through
   }
	;
term: identifier
   {
       init(&$$);
       $$.place = $1.place;
       $$.type = $1.type;
   }
	| identifier LPAREN actual_parameter_list RPAREN /* Function call */
   {
       init(&$$);
       $$.type = "int"; // TODO type checking
       $$.place = newTemp($$.type);
       $$.code = concat($3.code,
                        prod(concat($$.place, " = ", $1.place, "(", $3.place, ")", NULL)), 
                        NULL);
   }
	| number
   {
       $$ = $1; // pass through
   }
	| CHARACTER_STRING
   {
       init(&$$);
       $$.type = "char *";
       $$.place = newTemp($$.type);
       $$.code = prod(concat($$.place, " = ", concat("\"", trim($1), "\"", NULL), NULL));
} 
	;
identifier: IDENTIFIER
    {
       init(&$$);
       $$.place = strdup($1);
       $$.type = getType($1);
    }
	;
number: INTNUMBER
    {
        init(&$$);
        $$.place = strdup($1);
        $$.type = "int";
    }
	;
sign: PLUS
   {
        init(&$$);
        $$.code = "+";
   }
	| MINUS
   {
        init(&$$);
        $$.code = "-";
   }
	;
relop: EQUAL
   {
       init(&$$);
       $$.code = "==";
   }
	| NOTEQUAL
    {
       init(&$$);
       $$.code = "!=";
    }
	| LT
   {
        init(&$$);
        $$.code = "<";
   }
	| GT
   {
       init(&$$);
       $$.code = ">";
   }
	| LE
   {
       init(&$$);
       $$.code = "<=";
   }
	| GE
   {
        init(&$$);
        $$.code = ">=";
   }
	;
%%

/**
 * Provides a yyerror routine which simply reports error line. 
 * It is called when the parser finds something not covered by any rule. 
 *
 * @param s the error message to print.
 */
int yyerror(char * s) { 
  fprintf(stderr, "%s:%d: %s: at or before '%s'\n", progname, line_no, s, yytext);
  return 0;
}
