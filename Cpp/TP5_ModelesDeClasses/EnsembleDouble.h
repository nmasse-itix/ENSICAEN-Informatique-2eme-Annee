/**
 * @file   EnsembleDouble.h
 * @author Sebastien Fourey
 * @date   Thu Nov 18
 * 
 * @brief Declaration de la classe EnsembleDouble.  
 * 
 */
#ifndef ENSEMBLEDOUBLE_H
#define ENSEMBLEDOUBLE_H

#include <iostream>
#include <ostream>
using namespace std;

/**
 * Classe permettant de representer un ensemble de
 * double en utilisant uniquement la notion d'egalite entre
 * double. Aucune relation d'ordre n'est utilisee (par exemple
 * pour avoir un representation ordonnee en memoire qui accelererait
 * les recherches).<br>
 * Seul l'operateur == est utilise pour tester l'egalite de deux 
 * elements.
 */
class EnsembleDouble {

  class Noeud {
    double valeur;
    Noeud * suivant;
  public:
    Noeud(double valeur, Noeud * suivant=0):valeur(valeur),suivant(suivant) { }
    ~Noeud() { delete suivant; }
    double getValeur() { return valeur; }
    Noeud * getSuivant() { return suivant; }
    void setSuivant(Noeud * suivant) { Noeud::suivant = suivant; }
  };

  Noeud * liste;

public:

  /** 
   * Construit un ensemble vide.
   */
  EnsembleDouble():liste(0) { }

  /** 
   * Construit un singleton.
   */
  EnsembleDouble(double x) { liste = new Noeud(x); }

  /** 
   * Destructeur.
   */
  ~EnsembleDouble();

  /** 
   * Test si l'ensemble est vide.
   *
   * @return true si l'ensemble est vide, sinon false.
   */
  bool estVide() { return liste == 0; }

  /** 
   * Envoie tous les elements dans un flot de sortie.
   * 
   * @param out un flot de sortie.
   * 
   * @return le flot de sortie donne en parametre.
   */
  ostream & flush(ostream & out) const;

  /** 
   * Test l'appartenance d'un element a l'ensemble.
   * 
   * @param x un double.
   * 
   * @return true sie est dans l'ensemble, false sinon.
   */
  bool contient(double x) const;

  /** 
   * Test l'inclusion dans un autre ensemble.
   * 
   * @param e un ensemble
   * 
   * @return true si "je" suis inclus dans e, false sinon.
   */
  bool estInclusDans(const EnsembleDouble & autre) const;

  /** 
   * Ajoute un "objet" a l'ensemble.
   * 
   * @param e un double a ajouter à l'ensemble.
   */
  void ajoute(double x);

  /** 
   * Retire un double de l'esemble.
   * 
   * @param x un double a retirer.
   */
  void retire(double x);


  /** 
   * Ajoute tous les elements dans un autre ensemble.
   * 
   * @param e un ensemble
   */
  void ajouteDans(EnsembleDouble & e) const;

  /** 
   * Retire tous les elements dans un autre ensemble.
   * Apres a.enleveDe(b), b vaut b - a (- ensembliste)
   *
   * @param e un ensemble dont il faut retirer des elements.
   */
  void retireDe(EnsembleDouble & e) const;


  /** 
   * Operateur d'affectation d'un ensemble.
   * 
   * @param e un ensemble
   * 
   * @return une reference a moi-meme
   */
  EnsembleDouble & operator=(const EnsembleDouble & e);


  /** 
   * Constructeur par recopie.
   * 
   * @param e un ensemble
   */
  EnsembleDouble(const EnsembleDouble & e);

private:

  /** 
   * Methode recursive de suppression d'un element dans
   * une liste chainee.
   *
   * @param liste une liste.
   * @param x un element.
   * 
   * @return le liste sans l'element.
   */
  Noeud * retireRec(Noeud * liste, double x);

};

/** 
 * Operateur << pour les enembles de double.
 * 
 * @param out un flot de sortie.
 * @param e un ensemble de doubles.
 * 
 * @return le flot de sortie donne en argument.
 */
ostream & operator<<(ostream & out, const EnsembleDouble & e);


/** 
 * Creation d'un singleton.
 * 
 * @param x un double
 * 
 * @return le singleton {x}
 */
EnsembleDouble singleton(double x);

/** 
 * Creation d'un ensemble vide.
 * 
 * @param x un double
 * 
 * @return le singleton {x}
 */
EnsembleDouble ensembleVide();

/** 
 * Teste l'egalite de deux ensembles.
 * 
 * @param a un ensemble.
 * @param b un ensemble.
 * 
 * @return true si a=b (i.e., a est inclus dans b et b est inclus dans a),
 *         sinon false.
 */
bool egale(const EnsembleDouble & a, const EnsembleDouble & b);
bool operator==(const EnsembleDouble & a, const EnsembleDouble & b);
bool operator<(const EnsembleDouble & a, const EnsembleDouble & b);
bool operator>(const EnsembleDouble & a, const EnsembleDouble & b);


/** 
 * Union de deux ensembles de doubles.
 * 
 * @param a un ensemble de doubles.
 * @param b un ensemble de doubles.
 * 
 * @return a union b.
 */
EnsembleDouble reunion(const EnsembleDouble & a, const EnsembleDouble & b);
EnsembleDouble operator+(const EnsembleDouble & a, const EnsembleDouble & b);
EnsembleDouble operator|(const EnsembleDouble & a, const EnsembleDouble & b);

/** 
 * Difference de deux ensembles.
 * 
 * @param a un ensemble de doubles.
 * @param b un ensemble de doubles.
 * 
 * @return a prive de b.
 */
EnsembleDouble difference(const EnsembleDouble & a, const EnsembleDouble & b);
EnsembleDouble operator-(const EnsembleDouble & a, const EnsembleDouble & b);

/** 
 * Difference symetrique entre deux ensembles de doubles.
 * 
 * @param a un ensemble de doubles.
 * @param b un ensemble de doubles.
 * 
 * @return (a prive de b) union (b prive de a)
 */
EnsembleDouble diffSymetrique(const EnsembleDouble & a, const EnsembleDouble & b);
EnsembleDouble operator^(const EnsembleDouble & a, const EnsembleDouble & b);


/** 
 * Intersection entre deux ensembles de doubles.
 * 
 * @param a un ensemble de doubles.
 * @param b un ensemble de doubles.
 * 
 * @return l'intersection de a et b.
 */
EnsembleDouble intersection(const EnsembleDouble & a, const EnsembleDouble & b);
EnsembleDouble operator&(const EnsembleDouble & a, const EnsembleDouble & b);

#endif
