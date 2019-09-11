/**
 * #(@)scanner.l              ENSICAEN                       2005
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
 * @version	05/04/2006
 *
 * done:	-
 *
 * todo:	-
 */


%{
#include <stdio.h>
#include <string.h>

/* Header généré par yacc */
#include "parser.tab.h"

/* Header commun */
#include "epc.h"

/**
 * Affiche le jeton sur la sortie standard et le retourne.
 *
 * @param x   le jeton
 * @return    le jeton
 */
#ifdef DEBUG
#define A(x) {printf("Trouve: %s = \"%s\"\n", #x, yytext); return x;}
#else
#define A(x) {return x;}
#endif

/** Le numéro de la ligne courante */
int line_no = 1;

/* Termine un commentaire ? */
void commenteof();

%}

ID	[a-zA-Z][a-zA-Z0-9_]*
INT	[0-9]+
REAL    [0-9]*\.[0-9]+
A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]


%%

"(*"                        |
"{"				{   int c;
                                    while ((c = input())) {
				       if (c == '}')
					  break;
				       else if (c == '*') {
					  if ((c = input()) == ')')
					     break;
					  else
					     unput (c);
				       } else if (c == '\n')
					  line_no++;
				       else if (c == 0)
					  commenteof();
				}
}
{A}{N}{D}			{A(AND)}
{N}{O}{T}			{A(NOT)}
{O}{R}				{A(OR)}
{D}{O}				{A(DO)}
{I}{F}				{A(IF)}
{I}{N}				{A(IN)}
{E}{N}{D}			{A(END)}
{O}{F}				{A(OF)}
{B}{E}{G}{I}{N}			{A(PBEGIN)}
{P}{R}{O}{G}{R}{A}{M}		{A(PROGRAM)}
{T}{H}{E}{N}			{A(THEN)}
{V}{A}{R}			{A(VAR)}
{W}{H}{I}{L}{E}			{A(WHILE)}
{I}{N}{T}{E}{G}{E}{R}		{A(INTEGER)}
":="				{A(ASSIGNMENT)}
'[^']*'				{strcpy(yylval.strval, yytext); A(CHARACTER_STRING)}
":"				{A(COLON)}
";"                             {A(SEMICOLON)}
","				{A(COMMA)}
"."				{A(DOT)}
"="				{A(EQUAL)}
">="				{A(GE)}
">"				{A(GT)}
"<"                             {A(LT)}
"<>"                            {A(NOTEQUAL)}
"<="                            {A(LE)}
"["				{A(LBRAC)}
"]"                             {A(RBRAC)}
"("				{A(LPAREN)}
")"                             {A(RPAREN)}
"-"				{A(MINUS)}
"+"				{A(PLUS)}
"/"				{A(DIV)}
"*"				{A(MULT)}
{INT}                           {strcpy(yylval.strval, yytext); A(INTNUMBER)}
{REAL}                          {strcpy(yylval.strval, yytext); A(REALNUMBER)}
{ID}				{strcpy(yylval.strval, yytext); A(IDENTIFIER)}
[ \t\f]				;
\n                              line_no++;
.				fprintf (stderr,"%s:%d: error: '%c' (%d): illegal character\n", progname,line_no,yytext[0], yytext[0]);
%%

/**
 * Prints error message in case of bad comment pattern.
 */
void commenteof() {
   fprintf (stderr, "%s:%d:error: unexpected EOF inside comment at line\n", progname, line_no);
   exit (1);
}

/**
 * If the application requires yylex to continue processing
 * with another source of input, returns TRUE.
 *
 * @return always TRUE.
 */
int yywrap () {
   return 1;
}


