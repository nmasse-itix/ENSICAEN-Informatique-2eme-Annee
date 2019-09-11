/** -*- c-basic-offset: 3 -*- 
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin 
 * F-14050 Caen Cedex 
 * 
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre 
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#ifndef GENERATOR_H
#define GENERATOR_H

#include "parser.tab.h"

/**
 * @author Regis Clouard 
 * @author Nicolas Massé
 * @author Thomas Limin
 * 
 * @version 2006-03-06
 */

/**
 * @file generator.h
 * This file contains functions for managing
 * symbol table and intermediate code.
 */

/**
 * The symbol table.
 */
struct s_table {
   char name[255];       /* the name of the symbol */
   char type[255];       /* The C type of symbol : int, float, void. */
   struct s_table *next; /* The next symbol. */
};

extern struct s_table *_symbolTable;

/**
 * Initialise une structure de donnees du parseur.
 */
void init(struct t_code * s);

/**
 * Retourne le type d'un symbole.
 */
char * getType(char * id);

/**
 * Creates a new entry in the symbol table
 * for the given identifier with the specified type.
 * Available types are those of the C language.
 * For example, the following call adds the integer
 * variable 'i' in the symbol table:
 * <pre>
 * addType("i","int");
 * </pre>
 * @param the name of the identifier.
 * @param type the type name (int, float, void ...).
 */
void addType( char *identifier, char *type ) ;

/**
 * Returns the code for the declaration
 * of all the variables in the symbol table.
 * @return the code.
 */
char* genDeclarationVars();

/**
 * Creates a new tempory variable name with the
 * specified type. Available types are those
 * of the C language: int, float, etc. For 
 * example the following call creates a new
 * integer variable:
 * <pre>
 * char * variable=newTemp("int");
 * </pre>
 * The variable name template looks like __txxx where
 * xxx is a serial integer number that begins with 1.
 * For example, the second call to newTemp returns: __t002
 * Also, adds the variable in the symbol table.
 *
 * @param type the type of the temporary variable.
 * @return a new variable name.
 */
char* newTemp( char *type );

/**
 * Creates a new label name.
 * The label name takes the form of __Lxxxx
 * where xxxx is an integer. For example,
 * the second call to newLabel() return __L002
 * @return the string with the label name.
 */
char *newLabel( ) ;

/**
 * Catenates the given strings into one single string.
 * The result string is dynamically allocated. So a free
 * is necessary for destruction.
 * @param items the list of input strings.
 * @return the new statement.
 */
char *concat( const char *item, ... );

/**
 * Returns the given string without the first and
 * the last character. For example this is convenient
 * for getting text from Pascal string:
 * <pre>
 * trim("'this a text'"); -> returns "this a text"
 * </pre>
 * @param s the string to process.
 * @return the string modified.
 */
char *trim( char *s );

/**
 * Builds a C statement with
 * the given code.
 * Adds semicolon and indents each line.
 * @param s the given code.
 * @return the C statement.
 */
char *prod( const char *s ) ;

#endif /* GENERATOR_H */
