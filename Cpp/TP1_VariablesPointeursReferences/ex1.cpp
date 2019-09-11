 /**
 * #(@)ex1.cpp              ENSICAEN                       2005-09-20
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


#include "ex1.h"

void lectureClavierTableau(int * tableau, int taille) {
  cout << "Veuiler saisir " << taille << " entiers" << endl;
  for (int i = 0; i < taille; i++) {
    cin >> tableau[i];
  }
}


void affichageTableau(int * tableau, int taille) {
  cout << "Affichage d'un tableau contenant " << taille << " valeurs" << endl;

  for (int i = 0; i < taille; i++) {
    cout << tableau[i] << endl;
  }
}


void echange(int * entier1, int * entier2) {
  int tmp = *entier1;
  *entier1 = *entier2;
  *entier2 = tmp;
}


void echange(int & entier1, int & entier2) {
  int tmp = entier1;
  entier1 = entier2;
  entier2 = tmp;
}


int & getMin(int * const tableau, int taille) {
  int min = tableau[0];
  int idMin = 0;

  for (int i = 1; i < taille; i ++) {
    if (tableau[i] < min) {
      min = tableau[i];
      idMin = i;
    }
  }

  return tableau[idMin];
}


int & getMax(int * const tableau, int taille) {
  int max = tableau[0];
  int idMax = 0;

  for (int i = 1; i < taille; i ++) {
    if (tableau[i] > max) {
      max = tableau[i];
      idMax = i;
    }
  }

  return tableau[idMax];
}


int & getRandom(int * const tableau, int taille) {
  // récupératoin d'un nombre aléatoire x, tel que 0 <= x < taille
  // à l'aide des bits de poids fort du résultat de rand
  int index = static_cast<int>(taille * (rand() / (RAND_MAX + 1.0)));

  return tableau[index];
}


void melanger(int * const tableau, int taille, int nbEchange) {
  for (int i = nbEchange - 1; i >= 0; i--) {
    echange(getRandom(tableau, taille), getRandom(tableau, taille));
  }
}
