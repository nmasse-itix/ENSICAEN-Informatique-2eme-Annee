/**
 * #(@)Compte.cpp             ENSICAEN                       2005
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
 * Implémentation de la classe Compte.
 */

#include "Compte.h"
#include <sstream>

using namespace std;

/* Variable de classe, voir Compte.h */
long Compte::_prochainNumeroDeCompte = 1;


/*
 *
 * Définition des constructeurs/destructeur
 *
 */

Compte::Compte(string nom, double solde) {
    this->setNomProprietaire(nom);
    this->setSolde(solde);
    this->setNumeroDeCompte(Compte::prochainNumeroDeCompte());
    cout << *this << ": Compte::Compte(\"" << nom << "\")" << endl;
}


Compte::~Compte() {
    cout << *this << ": Compte::~Compte()" << endl;
}


/*
 *
 * Définition des accesseurs
 *
 */


string Compte::nomProprietaire() const {
    return _nomProprietaire;
}


void Compte::setNomProprietaire(string theValue) {
    _nomProprietaire = theValue;
}


long Compte::numeroDeCompte() const {
    return _numeroDeCompte;
}


void Compte::setNumeroDeCompte(long theValue) {
    _numeroDeCompte = theValue;
}


double Compte::solde() const {
    return _solde;
}


void Compte::setSolde(double theValue) {
    _solde = theValue;
}

long Compte::prochainNumeroDeCompte() {
    return Compte::_prochainNumeroDeCompte++;
}


/*
 *
 * Méthodes utilitaires.
 *
 */

string Compte::toString() const {
    ostringstream oss;

    oss << "Compte(numeroCompte = ";
    oss << this->numeroDeCompte();
    oss << ", nomProprietaire = ";
    oss << this->nomProprietaire();
    oss << ", solde = ";
    oss << this->solde();
    oss << ")";
    return oss.str();
}



/*
 *
 * Fonctions
 *
 */
std::ostream & operator<<(std::ostream & st, const Compte & cpt) {
    st << cpt.toString();
    return st;
}



/*
 *
 * Opérations bancaires.
 *
 */


bool Compte::depose(double montant) {
    bool result = false;

    if (montant < 0) {
        std::cerr << *this << ": Compte::depose(" << montant << "): ne peut deposer un montant négatif." << std::endl;
    } else {
        cout << *this << ": Compte::depose(" << montant << ")" << endl;
        this->setSolde(this->solde() + montant);
        result = true;

    }

    return result;
}


bool Compte::retrait(double montant) {
    bool result = false;

    if (montant < 0) {
        std::cerr << *this << ": Compte::retrait(" << montant << "): ne peut retirer un montant négatif." << std::endl;
    } else {
        std::cout << *this << ": Compte::retrait(" << montant << ")" << std::endl;
        this->setSolde(this->solde() - montant);
        result = true;
    }

    return result;
}

bool Compte::virement( Compte * compteDest, double montant ) {
  bool result = false;
  
  if (this->retrait(montant)) {
    if (compteDest->depose(montant)) {
      std::cout << "Virement réussi: " << montant << " " << *this << " => " << *compteDest << std::endl;
      result = true;
    } else {
      this->depose(montant);
      std::cerr << "Erreur lors du virement: depot refusé " << montant << " " << *this << " => " << *compteDest << std::endl;
    }
  } else {
    std::cerr << "Erreur lors du virement: retrait refusé " << montant << " " << *this << " => " << *compteDest << std::endl;
  }
  
  return result;
}
