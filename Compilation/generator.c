/** -*- c-basic-offset: 3 -*- 
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin 
 * F-14050 Caen Cedex 
 * 
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre 
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author Regis Clouard 
 *
 * @version 2006-03-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "generator.h"

/**
 * @file generator.c
 *
 * Theses functions do not care about memory management.
 * @todo Manage memory.
 */

/**
 * Init the parser's union.
 */
void init(struct t_code * s) {
    s->after = "";
    s->before = "";
    s->code = "";
    s->place = "";
    s->type = "";
}


/**
 * Does not create new string.
 */
char *trim( char *s ) {
    // Bug : s[strlen(s)-2]='\0';
    s[strlen(s)-1]='\0';
   return s+1;
}

/**
 * Creates a new string.
 */
char *prod( const char *s ) {
   if (s!=NULL &&  (strlen(s) > 0)) {
      char* ns=(char*)malloc((strlen(s)+6)*sizeof(char));
      strcpy(ns,"   ");
      strcat(ns,s);
      strcat(ns,";\n");
      return ns;
   } else {
      return strdup("");
   }
}

/* The current temporary counter. */
static int _tempCounter=0;

static struct s_table *_symbolTable=NULL;

/**
 * Creates a new string that can be free.
 */
char *newTemp( char * type) {
   char *_name=(char *)malloc(7*sizeof(char));

   sprintf(_name,"__t%03d",_tempCounter++);
   addType(_name,type);
   return _name;
}

/* Current number of label. */
static int _label=0;

/**
 * Creates a new string that can be free.
 */
char *newLabel( ) {
   char *_name=(char *)malloc(5*sizeof(char));

   sprintf(_name,"__L%03d",_label++);
   return _name;
}

/**
 * Creates a new string.
 */
char *concat( const char *item, ... ) {
   //const char *p;
   va_list argp;
   //int i;
   char *s;
   int size=strlen(item)+1;
   char *statement=(char *)malloc(size*sizeof(char));
   
   va_start(argp, item);
   strcpy(statement,item);
   while ((s = va_arg(argp, char *))!= NULL) {
      statement=realloc(statement,size+strlen(s));
      statement[size-1]='\0';
      strcat(statement,s);
      size+=strlen(s); 
   }
   
   va_end(argp);
   statement[size-1]='\0';
   return statement;
}

/**
 * Allocates a new entry in the symbol table, but
 * the structure field are already allocated.
 * @param a name for the identifier.
 * @param type a type name (int, float, void ...).
 */
void addType(char *identifier, char* type) {
   struct s_table *ns= (struct s_table *)(malloc(sizeof(struct s_table)));

   strcpy(ns->name,identifier);
   strcpy(ns->type,type);
   ns->next=_symbolTable;
   _symbolTable=ns;
}

/**
 * Retourne le type d'un symbole
 */
char * getType(char * id) {
    struct s_table * se = _symbolTable;
    while (se != NULL) {
        if (strcmp(se->name, id) == 0) {
            return se->type;
        }
        
        se = se->next;
    }
    
    // type par defaut
    return "void";
}

/**
 * Goes through the symbol table and builds
 * the convenient C statement liek: type variable;
 * One line per variable.
 */
char *genDeclarationVars( ) {
   char *s,*s1;
   struct s_table *t=_symbolTable;
   
   s=NULL;
   while ( t!= NULL) {
      s1=s;
      s=concat(prod(concat(t->type," ",t->name,NULL)),s1,NULL);
      if (s1) free(s1);
      t=t->next;
   }
   return s;
}
