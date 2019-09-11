/**
 * #(@)Moneo.h               ENSICAEN                       2005
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
 * TP Compte bancaire
 */

#ifndef MONEO_H
#define MONEO_H

#include <string>
#include <iostream>
#include "CompteCheque.h"

/**
 * Représente un porte monnaie monéo.
 */
class Moneo {

public:
    /*
     *
     * Constructeurs/destructeur
     *
     */


    /**
     * Construit un porte monnaie Moneo
     */
    Moneo(CompteCheque & cpt, double soldeMax);
    
    /**
     * Détruit un porte monnaie Moneo: le montant contenu dans le
     * porte monnaie est reversé sur le compte associé
     */
    ~Moneo();

    
    /*
     *
     * Getteurs
     *
     */
    
    
    /**
     * Retourne le compte chèque associé.
     */
    CompteCheque & compte() const;

    /**
     * Retourne le solde de ce porte monnaie.
     */
    double solde() const;

    /**
     * Retourne une représentation textuelle de ce compte.
     */
    std::string toString() const;


    /*
     *
     * Opérations bancaires
     *
     */

    /**
     * Recharge le porte monnaie d'un montant (nécessairement positif).
     * 
     * @param montant   le montant à déposer.
     */
    bool recharge(double montant);

    /**
     * Recharge le porte monnaie à son solde maximum.
     * 
     */
    bool recharge();

    /**
     * Retire un montant (nécessairement positif) de ce porte monnaie.
     * 
     * @param montant   le montant à retirer.
     */
    bool retrait(double montant);

private:
  
    /**
     * Definit le solde de ce compte.
     */
    void setSolde(double theValue);
    
    /**
     * Definit le solde maximum de ce compte.
     */
    void setSoldeMax(double theValue);
    
    /**
     * Retourne le solde maximum de ce porte monnaie.
     */
    double soldeMax() const;
    
    
    /**
     * Definit le compte chèque associé.
     */
    void setCompte(CompteCheque & theValue);
    
    


    /**
     * Le compte chèque associé, ne peut pas être null.
     */
    CompteCheque * _compte;

    /**
     * Le solde de ce compte, ne peut pas être négatif.
     */
    double _solde;

    /**
     * Le solde maximum de ce compte, ne peut pas être négatif.
     */
    double _soldeMax;

};

/**
 * Affiche un porte monnaie Monéo sur un flux de sortie
 */
std::ostream & operator<<(std::ostream & st, const Moneo & cpt);

#endif /* MONEO_H */
