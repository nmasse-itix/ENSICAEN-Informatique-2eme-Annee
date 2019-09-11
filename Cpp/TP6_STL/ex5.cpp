/** 
 * #(@)ex5.cpp                 ENSICAEN                       2006
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
 * TP7 : Utilisation des conteneurs de la STL.
 * TP7 - EX5 : Tableaux associatifs.
 */


// STL includes
#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <cstdlib> /* for exit() */

using namespace std;


/**
 * Tests the implementation of associative arrays.
 *
 * Trace :
 *   Liste des personnes :
 *   JCVD    45
 *   Le chat 10
 *   Nicolas 21
 *   Thomas  21
 * 
 * We can notice that the keys are sorted.
 * 
 * @param argc		number of arguments
 * @param argv		arguments
 * @return		0
 */
int main(int argc, char ** argv) {
	map<string, int> age;
	
	age["Nicolas"] = 21;
	age["Thomas"] = 21;
	age["JCVD"] = 45;
	age["Le chat"] = 10;
	
	cout << "Liste des personnes : " << endl;
	for (map<string, int>::const_iterator i = age.begin(); i != age.end(); ++i) {
		/* i->first is the key, i->second is the value */
		cout << i->first << '\t' << i->second << endl;
	}
	cout << endl;
	
	return 1;
}

