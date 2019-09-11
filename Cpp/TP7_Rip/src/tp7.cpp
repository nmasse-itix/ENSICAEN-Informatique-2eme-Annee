/**
 * #(@)tp7.cpp             ENSICAEN                       2006
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
 * Entry point of the project.
 */

/*
 * @version     2006-01-03
 *
 * @done        -
 *
 * @todo        -
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

#include "Network.h"
#include "Host.h"

using namespace std;

int main(int argc, char *argv[]) {

  // build a network
  Network n;
    if (argc > 1) {
        ifstream istr(argv[1]);
        n.growNetwork(istr);
    } else {
        n.growNetwork(cin);
    }
    

     cout << n << endl;
     
     n.sendMessage("A", "G", "Titi");
     
     n.removeLinkBetween("A", "C");
     
     // unused because useless
     //n.broadcastTables();
     
     cout << n << endl;

     n.sendMessage("A", "G", "Titi");
     
     n.removeLinkBetween("F", "D");
     
     cout << n << endl;
     
     n.sendMessage("A", "G", "Titi");
     
     return 0;
}
