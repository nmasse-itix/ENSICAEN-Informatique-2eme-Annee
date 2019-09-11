/**
 * #(@)CompteCheque.cpp             ENSICAEN                       2005
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


/*
 * @Fait	tout
 *
 * @Afaire	-
 */



#include "CompteCheque.h"
#include <sstream>

CompteCheque::CompteCheque(std::string nom, double decouvertAutorise, double solde) : Compte(nom, solde) {
    if ( ! this->setDecouvertAutorise(decouvertAutorise)) {
        this->setDecouvertAutorise(0);
    }
    std::cout << *this << ": CompteCheque::CompteCheque(\"" << nom << "\")" << std::endl;
}

CompteCheque::~CompteCheque() {
  std::cout << *this << ": CompteCheque::~CompteCheque()" << std::endl;
}


bool CompteCheque::retrait(double montant) {
    bool result = false;

    if ((this->solde() - montant) >=  - this->decouvertAutorise()) {
        Compte::retrait(montant);
        result = true;
    } else {
        std::cerr << *this << ": CompteCheque::retrait(" << montant << ") : erreur, le compte chèque n'est pas suffisamment approvisionné" << std::endl;
    }

    return result;
}


double CompteCheque::decouvertAutorise() const {
    return _decouvertAutorise;
}


bool CompteCheque::setDecouvertAutorise(double decouvert) {
    bool result = false;

    if (decouvert >= 0) {
        _decouvertAutorise = decouvert;
        result = true;
    }

    return result;
}

std::string CompteCheque::toString( ) const {
    std::ostringstream oss;

    oss << "CompteCheque(numeroCompte = ";
    oss << this->numeroDeCompte();
    oss << ", nomProprietaire = ";
    oss << this->nomProprietaire();
    oss << ", découvertAutorisé = ";
    oss << this->decouvertAutorise();
    oss << ", solde = ";
    oss << this->solde();
    oss << ")";

    return oss.str();
}
