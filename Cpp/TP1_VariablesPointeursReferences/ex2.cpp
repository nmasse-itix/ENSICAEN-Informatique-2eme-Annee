 /**
 * #(@)ex2.cpp              ENSICAEN                       2005-09-20
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
 * Exercice 2 du TP 1 de C++.
 */

#include "ex1.h"

/**
 * la taille maximale du tableau
 */
#define TAILLE_MAX 10

/**
 * Fonction principale.
 *  - demande à l'utilisateur de remplir un tableau
 *  - permute le mini et le maxi du tableau
 *  - affiche le tableau
 *
 * La ligne de commande doit préciser le nombre de case du tableau, qui
 * doit etre strictement positive et inférieure ou égale à TAILLE_MAX
 */
int main(int argc, char ** argv) {
  int tableau[TAILLE_MAX];

  // récupération sur la ligne de commande du parametre "taille du tableau"
  int taille = int(argv[1]);
  lectureClavierTableau(tableau, taille);
  echange(getMin(tableau, taille), getMax(tableau, taille));
  affichageTableau(tableau, taille);
}

 
