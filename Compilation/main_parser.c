/**
 * #(@)main_parser.c              ENSICAEN                       2005
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

/**
 * Executes the parser and the semantic analyzer.
 * Generates the intermediate code to standard output.
 * The compiler accepts only one Pascal file.
 */

#include "parser.tab.h"
#include "epc.h"

#include <string.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
    if (argc == 1) {
        fprintf(stderr,"%s: no input files\n",argv[0]);
        exit(1);
    }

    if (strcmp(argv[1],"-h") == 0) {
        fprintf(stderr,"Usage: %s [options] file\n",argv[0]);
        fputs("Options:",stderr);
        fputs("  -h                   Display this information",stderr);
        exit(0);
    }

    yyin=fopen(argv[1], "r");     /* Open the input for the parser. */

    /* @todo: !! Add a function to get only the name of the */
    /* file without the path. */
    progname=argv[1];

    if (!yyin) {     /* Cannot open input file. */
        fprintf(stderr,"%s: %s: No such file or directory\n",argv[0],argv[1]);
        fprintf(stderr,"%s: no input file\n",argv[0]);
        return 1;
    }
    
    if (yyparse()) {
        fprintf(stderr,"%s: %s: compilation failed\n",argv[0],argv[1]);
        return 1;
    }

    return 0;
}

