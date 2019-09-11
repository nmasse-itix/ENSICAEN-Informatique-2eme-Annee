 /**
 * #(@)ex1.h              ENSICAEN                       2005-09-20
 *
 * @author MASSE Nicolas (2005-Groupe4-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe4-MASSE) <thomas.limin@laposte.net>
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * Premier TP, découverte du C++, des entrées/sorties, des références
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


/**
 * Lecture au clavier d'un tableau d'entier
 *
 * @param tableau	le tableau à remplir
 * @param taille	la taille du tableau
 */
void lectureClavierTableau(int * tableau, int taille);


/**
 * Affichage des éléments du tableau sur la sortie standard
 *
 * Lecture au clavier d'un tableau d'entier
 *
 * @param tableau	le tableau à afficher
 * @param taille	la taille du tableau
 */
void affichageTableau(int * tableau, int taille);


/**
 * Echange de deux entiers, passage par adresse/pointeur
 *
 * @param entier1	adresse du premier entier
 * @param entier2	adresse du second entier
 */
void echange(int * entier1, int * entier2);


/**
 * Echange de deux entiers, passage par référence
 *
 * @param entier1	premier entier
 * @param entier2	second entier
 */
void echange(int & entier1, int & entier2);


/**
 * Echange de deux entiers, passage par valeurs
 * (cette fonction est volontairement défaillante, il n'est pas
 * possible d'échanger deux variable à l'aide d'une fonction
 * à qui l'on ne passe que les valeurs des variables. De plus, 
 * elle est commentée car si elle est disponible, elle rend la
 * résolution de surcharge ambigue entre la version echange(int, int)
 * et la version echange(int &, int &), le compilateur ne pouvant déterminer
 * laquelle des deux doit etre appelée, les deux acceptant des entiers en
 * parametres)
 *
 * @param entier1	premier entier
 * @param entier2	second entier
 */
/*
void echange(int entier1, int entier2) {
  int tmp = entier1;
  entier1 = entier2;
  entier2 = tmp;
}
*/


/**
 * Recherche et retour du minimum d'un tableau d'entiers
 *
 * @param tableau	le tableau dont il faut retourner le minimum
 * @param taille	la taille du tableau
 */
int & getMin(int * const tableau, int taille);


/**
 * Recherche et retour du maximum d'un tableau d'entiers
 *
 * @param tableau	le tableau dont il faut retourner le maximum
 * @param taille	la taille du tableau
 */
int & getMax(int * const tableau, int taille);


/**
 * Retourne un élément tiré au hasard dans le tableau
 *
 * @param tableau	le tableau dont il faut retourner le maximum
 * @param taille	la taille du tableau
 */
int & getRandom(int * const tableau, int taille);


/**
 * Effectue le mélange du tableau  l'aide d'un nombre
 * donné d'échnges
 *
 * @param tableau	le tableau à melanger
 * @param taille	la taille du tableau
 * @param nbEchange	le nombre d'échange à faire
 */
void melanger(int * const tableau, int taille, int nbEchange);
