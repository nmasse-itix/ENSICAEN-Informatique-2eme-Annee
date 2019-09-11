/**
 * #(@)nomfichier.h             ENSICAEN                       2005
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

#include <iostream>

#ifndef BANQUE_H
#define BANQUE_H

#include "Compte.h"

/* Nombre de comptes dans une banque */
#define TAILLE_BANQUE 10

/**
 * Définition de la classe Banque. Une banque est un regroupement de comptes.
 * 
 * @author Nicolas MASSE
 * @author Thomas LIMIN
 */
class Banque {

public:

    /**
     * Constructeur de Banque
     */
    Banque();

    /**
     * Destructeur de Banque
     */
    ~Banque();
    
    /**
     * Calcule la somme des soldes des comptes
     *
     * @return la somme des solde des comptes
     */
    double calculeSommeSolde() const;
    
    /**
     * Effectue le nombre voulue d'opération de virement,
     * les comptes sources, destination et le montant étant
     * choisis aléatoirement
     * 
     * @param nbVirement	le nombre de virement à effectuer (>=0)
     * @return			true si le solde total reste constant, false sinon
     */
    bool effectueVirements(int nbVirement) const;
    
  private:
    
    /**
     * Retourne le nombre de compte gérés
     * 
     * @return		le nb de comptes
     */
    int nbCompte() const;
    
    /**
     * Cree un nouveau compte. Le type précis de l'objet retourné
     * est choisi aléatoirement dans {Compte, CompteCheque, Livret,
     * PlanEpargneLogement}
     * 
     * @param nom	le nom du compte à créer
     * @return		un nouveau compte
     */
    Compte * creerNouveauCompte(std::string nom) const;

    /**
     * Retoune le tableau de comptes
     * 
     * @return _comptes
     */
    Compte * const * comptes() const;
    
    /**
     * Le tableau de comptes gérés par cette banque
     */
    Compte * _comptes[TAILLE_BANQUE];
    
    /**
     * Le nombre de comptes gérés par la banque
     */
    int _nbCompte;

};

/**
 * Tire un nombre aléatoire compris dans [ 0, randMax [
 * 
 * @param randMax	la limite supérieure (exclue)
 * @return		un nombre aléatoire;
 */
int random(int randMax);


#endif /* BANQUE_H */
