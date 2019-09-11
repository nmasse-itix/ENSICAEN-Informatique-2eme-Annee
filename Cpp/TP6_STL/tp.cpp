/** 
 * #(@)tp.cpp                 ENSICAEN                       2005
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
 *
 * Implementation des exercices 1 et 2.
 */


// STL includes
#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <stack>

#include <cstdlib> /* for random() */

using namespace std;

/**
 * Question 1A : Remplit un vecteur d'entier avec 20 nombres entre 0 et 100 
 * et les affiche.
 *
 * Trace :
 *    83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 72 36
 * 
 */
void question_1A(void) {
	/* Si on veut utiliser le vector comme une liste "classique", il ne faut
	 * pas d'éléments initiaux : vector<int> v(0);
	 * 
	 * Si on ne veut pas préciser le nombre initial d'éléments, il ne faut
	 * pas utiliser la notation :
	 *
	 *      vector<int> v();
	 * 
	 * sinon on le compilateur émet des erreurs :
	 * 
	 * tp.cpp:33: error: request for member `push_back' in `v', which is of
	 *    non-aggregate type `std::vector<int, std::allocator<int> > ()()'
	 *    
	 * le constructeur par defaut s'appelle de la manière suivante :
	 *     vector<int> v;
	 */
	vector<int> v;

	for (int i = 0; i < 20; i++) {
		/* L'ordre est conservé */
		v.push_back(random() % 100);
	}

	
	cout << "Question 1A: ";
	
	for (vector<int>::iterator i = v.begin(); i != v.end(); i++) {
		cout << *i << " ";
	}

	cout << endl;
}

/**
 * Question 1B : Remplit un set d'entier avec 20 nombres entre 0 et 100, 
 * deux fois le nombre 0 et les affiche. 
 *
 * Trace :
 *    0 2 11 22 23 29 30 35 42 56 58 62 67 68 69 82 93
 *   
 * Remarque :
 *    les nombres sont ordonnées par ordre croissant et le numéro 0
 *    n'apparait qu'une fois.
 *
 */
void question_1B(void) {
	set<int> s;

	for (int i = 0; i < 20; i++) {
		/* Les éléments sont triés par ordre croissant */
		s.insert(random() % 100);
	}

	/* Et on ne peut insérer qu'une seule fois le même élément */
	s.insert(0);
	s.insert(0);
	
	cout << "Question 1B: ";
	
	for (set<int>::iterator i = s.begin(); i != s.end(); i++) {
		cout << *i << " ";
	}

	cout << endl;
}

/**
 * Dépose dix éléments sur la pile et les reprend. 
 * La pile n'est pas une collection.
 *
 * Trace :
 *      9 8 7 6 5 4 3 2 1 0
 */
void question_1C(void) {
	stack<int> s;

	for (int i = 0; i < 10; i++) {
		s.push(i);
	}

	cout << "Question 1C: ";
	for (int i = 0; i < 10; i++) {
		cout << s.top() << " ";
		
		/* pop() renvoie void */
		s.pop();
	}
	
	cout << endl;
}

/**
 * Insere 5000 éléments dans un vecteur et note les changements de 
 * capacité du vecteur.
 *
 * Trace :
 *     [0] 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
 * 
 * Remarque :
 *     Initialement, le vecteur a une capacite nulle. Puis sa capacité 
 *     augmente de manière exponentielle. Ceci permet de minimiser le
 *     nombre d'allocations mémoire pour un taux d'inutilisation de la 
 *     mémoire compris entre 0 et 50 %.
 */
void question_2(void) {
	vector<int> v;
	size_t taille = v.capacity();

	cout << "Question 2: [" << taille << "] ";
	
	for (int i = 0; i < 5000; i++) {
		v.push_back(i);

		size_t ntaille = v.capacity();
		if (taille != ntaille) {
			taille = ntaille;
			cout << ntaille << " ";
		}
		
	}

	cout << endl;
}

int main(int argc, char ** argv) {
	question_1A();
	question_1B();
	question_1C();
	question_2();
	
	return 0;
}

