 /**
 * #(@)checkComplex.cpp              ENSICAEN                       2005-09-29
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
 * Test de la classe complexe, objet du TP2
 */

#include "complex.h"

int main(int argc, char ** argv) {
  Complex a(1, 1);
  Complex b(3, 4);
  Complex c;

  std::cout << "a: ";
  a.writeTo(std::cout);

  std::cout << std::endl << "b: ";
  b.writeTo(std::cout);

  std::cout << std::endl << "c: ";
  c.writeTo(std::cout);
  std::cout << std::endl;

  std::cout << std::endl << "a * b: " << std::endl;
  (a * b).writeTo(std::cout);
  std::cout << std::endl;

  std::cout << std::endl << "a - b: " << std::endl;
  (a - b).writeTo(std::cout);
  std::cout << std::endl;

  std::cout << std::endl << "a + b: " << std::endl;
  (a + b).writeTo(std::cout);
  std::cout << std::endl;

  std::cout << "Normalisation" << std::endl;
  c = normalize(a);
  c.writeTo(std::cout);
  std::cout << std::endl;
  std::cout << "Fin de la normalisation" << std::endl << std::endl;
 
  std::cout << "Rotation" << std::endl;
  c = b.rotate(a, M_PI / 2);
  c.writeTo(std::cout);
  std::cout << std::endl;
  std::cout << "Fin de la rotation" << std::endl << std::endl;
 
  std::cout << "Debut de 'Complex d = getMax(a, b)'" << std::endl;
  Complex d = getMax(a, b);
  std::cout << "Fin de 'Complex d = getMax(a, b)'" << std::endl << std::endl;
 
  
  std::cout << "Debut de 'c = getMax(a, b)'" << std::endl;
  c = getMax(a, b);
  std::cout << "Fin de 'c = getMax(a, b)'" << std::endl << std::endl;
 
  std::cout << "Debut de l'initialisation du tableau (taille 10)" << std::endl;
  Complex tab[10];
  std::cout << "Fin de l'initialisation du tableau" << std::endl << std::endl;
  
  std::cout << "Appel de la fonction remplirTableau(3, tab)" << std::endl;
  remplirTableau(3, tab);
  std::cout << "Fin de l'appel" << std::endl << std::endl;
  
  return 0;
}
