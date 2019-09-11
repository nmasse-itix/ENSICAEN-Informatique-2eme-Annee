 /**
 * #(@)checkMatrix.cpp              ENSICAEN                       2005-10-18
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
 * Test de la classe Matrix, objet du TP3
 */

#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char ** argv) {
    unsigned int truc;
    
    cout << "isPowerOfTwo(0) = " << isPowerOfTwo(0, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(1) = " << isPowerOfTwo(1, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(2) = " << isPowerOfTwo(2, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(3) = " << isPowerOfTwo(3, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(4) = " << isPowerOfTwo(4, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(5) = " << isPowerOfTwo(5, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(6) = " << isPowerOfTwo(6, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(7) = " << isPowerOfTwo(7, &truc) << " (" << truc << ")" << endl;
    cout << "isPowerOfTwo(0x80000000) = " << isPowerOfTwo(0x80000000, &truc) << " (" << truc << ")" << endl;
    
    
  Matrix a(1,2);
  Matrix b;
//  Matrix * c;

  bool result = a == b;

  cout << "a == b ? " << result << endl; 

  Matrix d(2, 3);
  Matrix e(3, 3);
  
  d.setValueAt(1, 1, 11);
  d.setValueAt(1, 2, 12);
  d.setValueAt(1, 3, 13);
  d.setValueAt(2, 1, 21);
  d.setValueAt(2, 2, 22);
  d.setValueAt(2, 3, 23);
    
  e.setValueAt(1, 1, 1);
  e.setValueAt(2, 2, 1);
  e.setValueAt(3, 3, 1);
  
  Matrix f = d * e;
  cout << d << e;
  cout << f;
  
  //Matrix q(1,1);
  //q.setValueAt(1, 1, 4);
  
  Matrix q(2,2);
  q.setValueAt(1, 1, 1);
  q.setValueAt(1, 2, 2);
  q.setValueAt(2, 1, 3);
  q.setValueAt(2, 2, 4);
  
  //for (unsigned int i = 1; i <= q.getLineNb(); i++) {
  //    for (unsigned int j = 1; j <= q.getColNb(); j++) {
  //        q.setValueAt(i, j, (i * j) % 7);
  //    }
  //}
  
  Matrix iq = q.invert();
  cout << "Avant l'inversion:" << endl << q << endl;
  cout << "Résultat de l'inversion:" << endl << iq << endl;
  /*
  cout << "Entrez une matrice au clavier, dont le format est le suivant :" << endl;
  cout << "nlignes ncols 11 12 13 21 22 23 ..." << endl;
  
  cin >> &c;
  
  cout << *c;
  
  delete c;
  */
}
