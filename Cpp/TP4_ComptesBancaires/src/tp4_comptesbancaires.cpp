/** 
 * #(@)tp4_comptesbancaires.cpp          ENSICAEN               2005
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
 * Programme de test du TP4
 */

#include <iostream>

/*
 * @Fait	tout
 *
 * @Afaire	-
 */


 


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Banque.h"
#include "PlanEpargneLogement.h"

using namespace std;

int main(int argc, char *argv[]) {

    PlanEpargneLogement::setCoefficient(0.5);
    srand(time(0));
        
    Banque b;
    
    std::cout << std::endl << std::endl << "Somme des soldes: " << b.calculeSommeSolde() << std::endl << std::endl;
    std::cout << std::endl << std::endl << "Constance des soldes: " << b.effectueVirements(50) << std::endl << std::endl;

    return EXIT_SUCCESS;
}
