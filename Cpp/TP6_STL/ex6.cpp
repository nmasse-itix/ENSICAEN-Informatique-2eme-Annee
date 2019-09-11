/** 
 * #(@)ex6.cpp                 ENSICAEN                       2006
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
 * TP7 - EX6 : Matrice creuse à l'aide d'une map.
 */

/*
 * @version	2006
 * 
 * @done	-
 *
 * @todo	debug HollowMatrix.h
 */


// STL includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>

#include <cstdlib> /* for exit() */


#include "HollowMatrix.h"

using namespace std;

/**
 * Prints the results of the comparison of the two pairs. Example :
 * 
 * code 	: printPair(make_pair<int, int>(1, 10), 
 * 			    make_pair<int, int>(2, 1), "<");
 * on screen	: (1, 10) < (2, 1) = true
 * 
 * @param p1		the first pair.
 * @param p2		the second pair.
 * @param op		the operator (<, >, == or !=)
 */
template<typename T1, typename T2> 
void printPair(pair<T1, T2> p1, pair<T1, T2> p2, string op) {
	cout << "(" << p1.first << ", " << p1.second << ") ";
	cout << op;
	cout << " (" << p2.first << ", " << p2.second << ") = ";

	if (op == "<") {
		cout << (p1 < p2);
	} else if (op == ">") {
		cout << (p1 > p2);
	} else if (op == "!=") {
		cout << (p1 != p2);
	} else if (op == "==") {
		cout << (p1 == p2);
	} else {
		cout << "not true, not false";
	}
	
	cout << endl;
}
		
/**
 * Tests the truth of the order relations on pairs. Results are printed 
 * on the screen.
 */
void testPairs(void) {
	/* true */
	printPair(make_pair<int, int>(1, 10), make_pair<int, int>(2, 1), "<");

	/* true */
	printPair(make_pair<int, int>(0, 0), make_pair<int, int>(0, 10), "<");

	/* false, equal */
	printPair(make_pair<int, int>(0, 0), make_pair<int, int>(0, 0), "<");

	/* true */
	printPair(make_pair<int, double>(1, 8.5), 
		  make_pair<int, double>(1, 9), "<");

	/* true */
	printPair(make_pair<int, int>(0, 0), make_pair<int, int>(0, 1), "!=");

	/* false, equal */
	printPair(make_pair<int, int>(0, 5), make_pair<int, int>(0, 5), ">");

	/* false, equal */
	printPair(make_pair<int, int>(0, 5), make_pair<int, int>(0, 5), "<");

	/* true */
	printPair(make_pair<int, int>(0, 5), make_pair<int, int>(0, 5), "==");

	/* false, "debrie" > "clouard" */
	printPair(make_pair<string, int>("debrie", 10), 
		  make_pair<string, int>("clouard", 40), "<");

	cout << endl;
}

void testMatrix(void) {
	HollowMatrix m;

	m.setValue(1, 1, 1);
	m.setValue(2, 2, 1);
	m.setValue(3, 3, 1);
	m.setValue(4, 4, 1);
	
	m.setValue(2, 3, 23);
	if (m(2 ,3) != 23 || m(3, 2) == 23) {
		cout << "Erreur: " << __FILE__ << ":" << __LINE__ << endl;
	}
	
	m.setValue(3, 4, -2.3);
	m.setValue(2, 4, 1.23456789);

	cout << "check: " << 1 << 1.0 << 2 << -3 << 4 << endl;
	cout << endl;
	
	/* original matrix */
	cout << m;
	cout << endl;
	
	/* add 4 columns */
	m.setValue(1, 8, 1);
	cout << m;
	cout << endl;
	
	/* delete 4 columns */
	m.setValue(1, 8, 0);
	cout << m;
	cout << endl;

	/* We can modify the matrix using the functions of the map class */
	m[make_pair<int, int>(5, 5)] = 666;
	cout << m;
	cout << endl;
	
	cout << "check: " << 1 << 1.0 << 2 << -3 << 4 << endl;
}

/**
 * Tests the order relations on pairs. Tests the implementation of the matrix.
 * 
 * @param argc		number of arguments
 * @param argv		arguments
 * @return		0
 */
int main(int argc, char ** argv) {
	/* Displays boolean as "true" or "false" */
	cout << setiosflags(ios_base::boolalpha);

	testPairs();
	testMatrix();
	
	return 1;
}

