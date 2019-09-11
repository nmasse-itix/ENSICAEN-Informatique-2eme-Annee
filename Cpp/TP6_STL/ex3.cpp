/** 
 * #(@)ex3.cpp                 ENSICAEN                       2005
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
 */


// STL includes
#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include <cstdlib> /* for exit() */

using namespace std;

int main(int argc, char ** argv) {
	if (argc != 2) {
		cout << "Usage : " << argv[0] << " <file>" << endl;
		exit(1);
	}
	
	ifstream st(argv[1]);
	if (! st.is_open()) {
		cout << "Erreur lors de l'ouverture du fichier !" << endl;
		exit(2);
	}
	
	set<char> s;
	
	char c = 0;
	while (!st.eof()) {
		st >> c;
		s.insert(c);
	}
	
	st.close();
	
	cout << "Nombre de caracteres differents : " << s.size() << endl;
	
	for (set<char>::iterator i = s.begin(); i != s.end(); i++) {
		cout << *i;
	}
	
	cout << endl;
	
	return 0;
}

