/** 
 * #(@)porte.cpp             ENSICAEN                       2005
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
 * Ce programme permet de definir des fonctions logiques en intention
 * et de les utiliser. Il ne prend pas de parametre.
 *
 * 
 * Trace d'execution
 * -------------------
 *
 * Table de verite par defaut :
 * +-----+-----+-----+
 * |b1\b2|  0  |  1  |
 * +-----+-----+-----+
 * |  0  |  0  |  0  |
 * +-----+-----+-----+
 * |  1  |  0  |  0  |
 * +-----+-----+-----+
 * 
 * Table de verite de la fonction ET :
 * +-----+-----+-----+
 * |b1\b2|  0  |  1  |
 * +-----+-----+-----+
 * |  0  |  0  |  0  |
 * +-----+-----+-----+
 * |  1  |  0  |  1  |
 * +-----+-----+-----+
 * 
 * Test OK
 */

#include <iostream>

using namespace std;

/**
 * Faire retourner par une fonction une reference a une variable locale 
 * est une erreur. Mais si cette variable est declaree static, alors cela
 * devient possible.
 *
 * En effet, lorsque l'on declare une variable locale a une fonction, cette
 * variable est alouee sur la pile et une fois la fonction terminee, la pile
 * est reajustee et la variable n'existe plus. Faire reference a cette 
 * variable est incorrect et conduit a des resultats errones.
 *
 * Mais lorsque l'on declare une variable "static", le compilateur 
 * reserve une zone memoire pendant toute l'execution du programme ; on
 * peut alors y faire reference à partir de n'importe quel moment de 
 * l'execution du programme.
 *
 * Le fait de retourner une reference permet d'utiliser l'appel de fonction
 * comme "lvalue", c'est une construction similaire à la suivante en C :
 *
 *            strncpy(dst, src, size)[size - 1] = '\0';
 * 
 */


/*
 * @version	1.0
 *
 * @Fait	Enonce + affichage de la table de verite.
 *
 * @Afaire	-
 */


/**
 * Cette fonction dispose d'un tableau statique de 4 booleens a deux entrees
 * qui definit la table de verite de la fonction logique. Les deux parametres
 * b1 et b2 sont les indices dans tableau du resultat de la fonction logique 
 * pour ces deux valeurs.
 *
 * Elle retourne une reference vers l'element du tableau qui contient le 
 * resultat de la fonction logique, ce qui permet d'utiliser un appel de
 * cette fonction comme "lvalue".
 *
 */
bool & porte(bool b1, bool b2) {
	static bool tableVerite[2][2] = {{false, false}, {false, false}};
	
	return tableVerite[int(b1)][int(b2)];
}


/**
 * Cette fonction affiche la table de verite definie en intention par 
 * l'intermediaire de la fonction porte(bool, bool). 
 *
 * @param st	le flux de sortie.
 */
void afficheTableVerite(ostream & st) {
	int b1, b2;
	
	// Entete de la table de verite
	st << "+-----+-----+-----+" << endl;
	st << "|b1\\b2|  0  |  1  |" << endl;
	st << "+-----+-----+-----+" << endl;

	// Parcours ligne / ligne
	for (b1 = 0; b1 <= 1; b1++) {
		// Entete de ligne
		st << "|  " << b1 << "  |";

		// Parcours colonne par colonne
		for (b2 = 0; b2 <= 1; b2++) {
			st << "  " << porte(bool(b1), bool(b2)) << "  |";
		}

		// Fin de la ligne
		st << endl;

		// Separation entre deux lignes
		st << "+-----+-----+-----+" << endl;
	}
}


/**
 * Point d'entree du programme. Ce programme n'accepte pas de parametres.
 */
int main(int argc, char ** argv) {
	cout << "Table de verite par defaut :" << endl;
	afficheTableVerite(cout);
	cout << endl;
	
	/* Definition de la fonction logique ET par extention */
	porte(true, false) = false;
	porte(false, true) = false;
	porte(true, true) = true;
	porte(false, false) = false;
	
	cout << "Table de verite de la fonction ET :" << endl;
	afficheTableVerite(cout);
	cout << endl;
	
	if (porte(true, true)) 
		cout << "Test OK" << endl;

	return 0;
}

