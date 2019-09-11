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
 * Implantation de la classe Banque.
 */

#include <iostream>

/*
 * @Fait	tout
 *
 * @Afaire	-
 */



#include "Banque.h"

#include <cstdlib>
#include <sstream>
#include "CompteCheque.h"
#include "Livret.h"
#include "PlanEpargneLogement.h"

Banque::Banque() {
    this->_nbCompte = TAILLE_BANQUE;
    
    for (int i = 0; i < _nbCompte; i++) {
        std::ostringstream oss;
        oss << i;
        this->_comptes[i] = this->creerNouveauCompte(oss.str());
    }
}


Banque::~Banque() {
    int nbCompte = this->nbCompte();

    for (int i = 0;  i < nbCompte; i++) {
        delete  _comptes[i];
        _comptes[i] = 0;
    }
}

int Banque::nbCompte() const {
    return this->_nbCompte;
}


Compte * Banque::creerNouveauCompte(std::string nom) const {
    int type = random(4);
    double solde = random(500) * 10.0;
    Compte * cpt = 0;

    switch(type) {
    case 0:
        cpt = new Compte(nom, solde);
        break;
    case 1:
        cpt = new CompteCheque(nom, -500, solde);
        break;
    case 2:
        cpt = new Livret(nom, 0.1, solde);
        break;
    default:
        cpt = new PlanEpargneLogement(nom, 0.1, solde);
        break;
    }

    return cpt;

}

int random(int randMax) {
     return (int) (((double)randMax) * (rand() / (RAND_MAX + 1.0)));
}

Compte * const * Banque::comptes() const {
  return this->_comptes; 
}

double Banque::calculeSommeSolde() const {
  double somme = 0;
  Compte * const * comptes = this->comptes();
  for (int i = this->nbCompte() - 1; i >= 0; i--) {
    somme += comptes[i]->solde(); 
  }
  
  return somme;
}

bool Banque::effectueVirements( int nbVirement ) const {
  Compte * const * comptes = this->comptes();
  int nbCompte = this->nbCompte();
  double soldeInitial = this->calculeSommeSolde();
  
  for (int i = nbVirement -1; i >= 0; i--) {
    Compte * src = comptes[random(nbCompte)];
    Compte * dest = 0;
    double montant = random(500) * 10;
    
    do {
      dest = comptes[random(nbCompte)];
    } while (src == dest);
    
    src->virement(dest, montant);
  }
  
  return soldeInitial == this->calculeSommeSolde();
}


