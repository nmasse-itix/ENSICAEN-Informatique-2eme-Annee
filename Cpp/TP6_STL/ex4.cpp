/** 
 * #(@)ex4.cpp                 ENSICAEN                       2006
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
 * TP7 - EX4 : Utilisation d'un tas pour trier.
 */


// STL includes
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>

#include <cstdlib> /* for exit() */

using namespace std;

/**
 * Sorts the vector using a heap.
 *
 * @param v		a vector
 * @return		a sorted copy of the vector
 */
template<typename T, class Cmp> vector<T> trier(vector<T> & v) {
	priority_queue<T, vector<T>, Cmp> pq;
	vector<T> vs;

        for (typename vector<T>::iterator i = v.begin(); i != v.end(); i++) {
                pq.push(*i);
	}
	
	while (! pq.empty()) {
		vs.push_back(pq.top());
		pq.pop();
	}
	
	return vs;
}

/**
 * Fill a vector with 20 integers and sort it using a heap.
 *
 * Trace :
 *   Unsorted vector : 83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 
 *   72 36
 *   
 *   Sorted vector - less<int> : 93 92 90 86 86 83 77 72 63 62 59 49 40 36 35 
 *   27 26 26 21 15
 *   
 *   Sorted vector - greater<int> : 15 21 26 26 27 35 36 40 49 59 62 63 72 77 
 *   83 86 86 90 92 93
 *
 *
 * @param argc		number of arguments
 * @param argv		arguments
 * @return		0
 */
int main(int argc, char ** argv) {
	vector<int> v;
	
	for (int i = 0; i < 20; i++) {
		/* L'ordre est conservé */
		v.push_back(random() % 100);
	}
	
	cout << "Unsorted vector : ";
	for (vector<int>::iterator i = v.begin(); i != v.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	
	/* Remark : notice the space between the two ">" after 
	 * the function name */
	vector<int> vs = trier<int, less<int> >(v);
	
	cout << "Sorted vector - less<int> : ";
	for (vector<int>::iterator i = vs.begin(); i != vs.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	
	vs = trier<int, greater<int> >(v);
	
	cout << "Sorted vector - greater<int> : ";
	for (vector<int>::iterator i = vs.begin(); i != vs.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	
	return 0;
}

