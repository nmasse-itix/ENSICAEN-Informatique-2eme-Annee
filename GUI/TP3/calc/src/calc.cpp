/**
 * #(@)calc.cpp             ENSICAEN                       2005
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "CalcGUI.h"

#include <stdio.h>
#include <stdlib.h>
#include <qapplication.h>


/**
 * Entry point of the app.
 */
int main(int argc, char *argv[]) {
    QApplication app( argc, argv );
    CalcGUI gui;
    
    app.setMainWidget(&gui);
    gui.show();
  
    return app.exec();
}
