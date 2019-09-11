/**
 * #(@)PlanEpargneLogement.cpp             ENSICAEN                      2005
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
 * Implémentation de la classe PlanEpargneLogement.
 */

/*
 * @Fait	tout
 *
 * @Afaire	-
 */



#include "PlanEpargneLogement.h"
#include <sstream>

double PlanEpargneLogement::_coefficient = 1;

PlanEpargneLogement::PlanEpargneLogement( std::string nom, double taux, double solde ) : Livret(nom, taux, solde) {
    std::cout << *this << ": PlanEpargneLogement::PlanEpargneLogement(\"" << nom << "\", taux: " << taux << ", solde: " << solde << ")" << std::endl;
}


PlanEpargneLogement::~PlanEpargneLogement() {
    std::cout << *this << ": PlanEpargneLogement::~PlanEpargneLogement()" << std::endl;
}


bool PlanEpargneLogement::retrait( double montant ) {
    bool result = false;

    if (montant == this->solde()) {
        result = Livret::retrait(montant);
    } else {
      std::cerr << *this << ": PlanEpargneLogement::retrait(" << montant << ") : erreur, le montant du retait doit être égal au solde" << std::endl;
    }

    return result;
}

std::string PlanEpargneLogement::toString( ) const {
    std::ostringstream oss;

    oss << "Plan-Epargne-Logement(numeroCompte = ";
    oss << this->numeroDeCompte();
    oss << ", nomProprietaire = ";
    oss << this->nomProprietaire();
    oss << ", solde = ";
    oss << this->solde();
    oss << ", taux: ";
    oss << this->taux();
    oss << ")";
    return oss.str();
}

double PlanEpargneLogement::coefficient() {
  return PlanEpargneLogement::_coefficient;
}

bool PlanEpargneLogement::setCoefficient(double coef) {
  bool result = false;
  
  if (coef >= 0) {
    _coefficient = coef;
    result = true;
  } else {
    std::cerr << "PlanEpargneLogement::setCoefficient(" << coef << ")" << std::endl;
  }
  
  return result;
}


double PlanEpargneLogement::taux() const {
  return Livret::taux() * PlanEpargneLogement::coefficient();
}







