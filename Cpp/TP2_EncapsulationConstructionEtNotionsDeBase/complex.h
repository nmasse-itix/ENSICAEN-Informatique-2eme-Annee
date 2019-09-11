 /**
 * #(@)complex.h              ENSICAEN                       2005-02-27
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


#ifndef __COMPLEXE_H__
#define __COMPLEXE_H__

#include <iostream>

/**
 * Définition d'une classe complexe fournissant les services de base
 * (voir énoncé TP2)
 *
 * @author	MASSE Nicolas & LIMIN Thomas
 * @version	0.0.1
 */
class Complex {

 public:


  /**
   * Constructeur par défaut.
   *
   * @param re	partie réelle du nombre complexe, 0 par défaut
   * @param im	partie imaginaire du nmbre complexe, 0 par defaut
   */
  Complex(double re = 0, double im = 0);


  /**
   * Construit un complexe de module 1 a partir de son argument.
   *
   * @param angle	l'argument du complexe
   */
  Complex(double angle);


  /**
   * Constructeur par recopie (clone)
   */
  Complex(const Complex & cpx);


  /**
   * Destructeur
   */
  ~Complex();

  /**
   * Retourne la partie réelle.
   *
   * @return	la partie réelle du complexe
   */
  double getRealPart() const;
  

  /**
   * Retourne la partie imaginaire.
   *
   * @return	la partie imaginaire du complexe
   */
  double getImaginaryPart() const;


  /**
   * Modifie la partie réelle
   *
   * @param re	la nouvelle partie réelle affectée
   */
  void setRealPart(double re);


  /**
   * Modifie la partie imaginaire.
   *
   * @param im	la nouvelle partie imaginaire affectée
   */
  void setImaginaryPart(double im);


  /**
   * Retourne le module.
   *
   * @return	le module du nombre complexe
   */
  double getMagnitude() const;


  /**
   * Retourne l'argument en radians
   *
   * return	l'argument du nombre complexe
   */
  double getAngle() const;


  /**
   * Retourne un nouveau complexe résultant de la rotation
   * de l'instance de complexe par l'angle donné
   *
   * @param c		centre de rotation
   * @param angle	angle de rotation en radians
   * @return		le resultat de la rotation
   */
  Complex rotate(Complex & c, double angle) const;
  
  /**
   * Donne une représentation sous la forme a + ib du nombre complexe
   * et la copie dans le flux passé en argument
   *
   * @param output	le flux dans lequel sera écrit la représentation
   */
  void writeTo(std::ostream & output) const;

  /**
   * Effectue la somme de ce complexe et de celui passe en parametre.
   *
   * @param c2		le complexe a ajouter
   * @return		la somme des deux complexes
   */
  Complex operator+(const Complex & c2) const;
  
  /**
   * Effectue la difference de ce complexe et de celui passe en parametre.
   *
   * @param c2		le complexe a soustraire
   * @return		la difference des deux complexes
   */
  Complex operator-(const Complex & c2) const;
  
  /**
   * Effectue le produit de ce complexe et de celui passe en parametre.
   *
   * @param c2		le complexe a multiplier
   * @return		le produit des deux complexes
   */
  Complex operator*(const Complex & c2) const;
  
  /**
   * Operateur d'affectation
   *
   * @param c2		le complexe a affecter
   * @return		le complexe
   */
  Complex & operator=(const Complex & c2);
  
  /**
   * Echange les parties réelles et imaginaires
   */
  void swapRealAndImaginaryPart();

 private:

  /**
   * Partie entière du nombre complexe
   */
  double _re;

  /**
   * Partie imaginaire du nombre complexe
   */
  double _im;


  
};


/**
 * Effectue le produit de deux nombres complexes.
 *
 * @param cpx1	premier complexe
 * @param cpx1	second complexe
 * @return	un nombre complexe issu du produit
 *		des deux premiers. La propriété est transférée à l'appelant.
 */
Complex product(const Complex & cpx1, const Complex & cpx2);


/**
 * Effectue la somme de deux nombres complexes.
 *
 * @param cpx1	premier complexe
 * @param cpx1	second complexe
 * @return	un nombre complexe issu de la somme
 *		des deux premiers. La propriété est transférée à l'appelant.
 */
Complex sum(const Complex & cpx1, const Complex & cpx2);


/**
 * Effectue la difference de deux nombres complexes
 *
 * @param cpx1	premier complexe
 * @param cpx1	second complexe
 * @return	un nombre complexe issu de la difference
 *		des deux premiers (cpx1 - cpx2 => cpx3).
 */
Complex minus(const Complex & cpx1, const Complex & cpx2);

/**
 * Normalise un complexe.
 *
 * @param cpx	le complexe a normaliser
 * @return	le complexe normalise
 */
Complex normalize(Complex cpx);

/**
 * Retourne le complexe qui a le plus grand module.
 *
 * @param c1	le premier complexe
 * @param c2	le deuxieme complexe
 * @return 	le plus grand des deux.
 */
Complex & getMax(Complex & c1, Complex & c2);


/**
 * Remplit le tableau de n elements avec une suite de nombre
 * complexes de 0 à n-1.
 *
 * @param n	le nombre d'éléments dans le tableau
 * @param tab	le tableau
 */
void remplirTableau(int n, Complex * tab);


#endif /* def __COMPLEXE_H__ */
