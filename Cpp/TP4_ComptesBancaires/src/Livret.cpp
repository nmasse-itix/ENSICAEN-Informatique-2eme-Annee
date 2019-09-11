/**
 * #(@)nomfichier.cpp             ENSICAEN                       2005
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
 * Implémentation de la classe Livret.
 */

#include <iostream>

#include "Livret.h"
#include <sstream>

Livret::Livret(std::string nom, double taux, double solde): Compte(nom, solde) {
    if ( ! this->setTaux(taux)) {
        this->setTaux(0);
    }
    this->setSoldeMini(this->solde());
    std::cout << *this << ": Livret::Livret(\"" << nom << "\", taux: " << taux << ", solde: " << solde << ")" << std::endl;
}


Livret::~ Livret() {
  std::cout << *this << ": Livret::~Livret()" << std::endl;
}

double Livret::taux() const {
    return _taux;
}


bool Livret::setTaux(double taux) {
    bool result = false;

    if (taux >= 0) {
        _taux = taux;
        result = true;
    }

    return result;
}


double Livret::soldeMini() const {
    return _soldeMini;
}


bool Livret::setSoldeMini(double solde) {
    bool result = false;

    if (solde >= 0) {
        _soldeMini = solde;
        result = true;
    } else {
      std::cerr << *this << ": Retrait::setSoldeMini(" << solde << ") : erreur, le solde mini ne devrait pas être négatif" << std::endl;
    }

    return result;
}

bool Livret::retrait( double montant ) {
    bool result = false;

    if ((this->solde() - montant) >= 0) {
        result = Compte::retrait(montant);
        if (result && (this->solde() < this->soldeMini())) {
            this->setSoldeMini(this->solde());
        }
    } else {
      std::cerr << *this << ": Livret::retrait(" << montant << ") : erreur, le livret n'est pas suffisamment approvisionné" << std::endl;
    }

    return result;
}

std::string Livret::toString( ) const {
  std::ostringstream oss;

    oss << "Livret(numeroCompte = ";
    oss << this->numeroDeCompte();
    oss << ", nomProprietaire = ";
    oss << this->nomProprietaire();
    oss << ", solde = ";
    oss << this->solde();
    oss << ", taux = ";
    oss << this->taux();
    oss << ")";

    return oss.str();
}

double Livret::priseDInterets() {
  double interet = this->soldeMini() * this->taux();
  std::cout << *this << " : Livret::priseDInterets() => " << interet << std::endl;
  this->depose(interet);
  this->setSoldeMini(this->solde());
  return interet;
}
