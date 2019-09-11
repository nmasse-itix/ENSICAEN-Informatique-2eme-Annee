/**
 * #(@)epc.h                    ENSICAEN                       2006
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
 * Contient la déclaration des variables partagées entre les différents
 * fichiers.
 *
 * @version     05/04/2006
 *
 * done:        -
 *
 * todo:        -
 */

#ifndef EPC_H
#define EPC_H

/* Pour FILE* */
#include <stdio.h>

/** Le nom du programme, défini dans le fichier parser.y */
extern char* progname;

/** L'analyseur syntaxique, fonction définie par lex */
extern int yylex(void);

/** Le flux d'entrée utilisée par l'analyseur syntaxique */
extern FILE *yyin;

/**
 * Analyseur syntaxique, fonction définie par yacc 
 * dans le fichier parser.tab.c 
 */
extern int yyparse(void);

/** Définie dans le fichier scanner.l */
extern int line_no;

/** Définie par lex */
extern char * yytext;


#endif /* EPC_H */
