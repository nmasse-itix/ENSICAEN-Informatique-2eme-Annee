/**
 * #(@)Moneo.cpp             ENSICAEN                       2005
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
 * Implémentation de la classe Moneo.
 */

#include "Moneo.h"
#include <sstream>

using namespace std;


/*
 *
 * Définition des constructeurs/destructeur
 *
 */

Moneo::Moneo(CompteCheque & cpt, double soldeMax) {
    this->setCompte(cpt);
    this->setSoldeMax(soldeMax);
    this->setSolde(0);
    std::cout << *this << ": Moneo::Moneo(" << cpt << ", soldeMax: " << soldeMax << ")" << std::endl;
}


Moneo::~Moneo() {
    double montant = this->solde();
    this->compte().depose(montant);
    std::cout << *this << ": Moneo::~Moneo()" << std::endl;
}



/*
 *
 * Opérations bancaires.
 *
 */


bool Moneo::recharge() {
  bool ret = false;
  double montant = this->soldeMax() - this->solde();

  if (this->compte().retrait(montant)) {
    cout << *this << ": Moneo::recharge() => " << montant << std::endl;
    this->setSolde(this->soldeMax());
    ret = true;
  } else {
    cout << *this << ": Moneo::recharge() opération impossible, solde compte trop faible" << std::endl;
  }

  return ret;
}


bool Moneo::retrait(double montant) {
  bool ret = false;

  if (montant < 0) {
    cerr << *this << ": Moneo::retrait(" << montant << "): ne peut retirer un montant négatif." << endl;
  } else if (montant > this->solde()) {
    cerr << *this << ": Moneo::retrait(" << montant << "): solde trop faible." << endl;
  } else {
    cout << *this << ": Moneo::retrait(" << montant << ")" << endl;
    this->setSolde(this->solde() - montant);
    ret = true;
  }

  return ret;
}


/*
 *
 * Définition des accesseurs
 *
 */


CompteCheque & Moneo::compte() const {
    return *_compte;
}


void Moneo::setCompte(CompteCheque & cpt) {
    _compte = &cpt;
}


double Moneo::solde() const {
    return _solde;
}


void Moneo::setSolde(double theValue) {
    _solde = theValue;
}

double Moneo::soldeMax() const {
    return _soldeMax;
}


void Moneo::setSoldeMax(double theValue) {
    _soldeMax = theValue;
}



/*
 *
 * Méthodes utilitaires.
 *
 */

string Moneo::toString() const {
    ostringstream oss;

    oss << "Moneo(soldeMax = ";
    oss << this->soldeMax();
    oss << ", solde = ";
    oss << this->solde();
    oss << ", compte = ";
    oss << this->compte();
    oss << ")";

    return oss.str();
}



/*
 *
 * Fonctions
 *
 */
std::ostream & operator<<(std::ostream & st, const Moneo & cpt) {
    st << cpt.toString();
    return st;
}
