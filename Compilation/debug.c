/**
 * #(@)debug.c              ENSICAEN                       2005
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

#include <stdio.h>

/* Header commun */
#include "epc.h"

/** Le nom du programme, indispensable pour l'édition des liens */
char * progname = "test";

/**
 * Programme de test : analyse lexicalement l'entrée standard.
 */
int main() {
    for (;;)
        yylex();

}

