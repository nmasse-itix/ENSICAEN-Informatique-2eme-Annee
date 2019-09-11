/**
 * #(@)Compte.h               ENSICAEN                       2005
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

#ifndef COMPTE_H
#define COMPTE_H

#include <string>
#include <iostream>

/**
 * Représente un compte bancaire générique.
 */
class Compte {
public:
    /*
     *
     * Constructeurs/destructeur
     *
     */


    /**
     * Construit un compte.
     */
    Compte(std::string nom, double solde = 0);

    /**
     * Détruit un compte.
     */
    virtual ~Compte();

    /**
     * Retourne le nom du propriétaire de ce compte.
     */
    std::string nomProprietaire() const;


    /**
     * Retourne le numéro de ce compte.
     */
    long numeroDeCompte() const;


    /**
     * Retourne le solde de ce compte.
     */
    double solde() const;

    /**
     * Retourne un numéro de compte unique.
     */
    static long prochainNumeroDeCompte();


    /*
     *
     * Méthodes utilitaires.
     *
     */


    /**
     * Retourne une représentation textuelle de ce compte.
     */
    virtual std::string toString() const;


    /*
     *
     * Opérations bancaires
     *
     */

    /**
     * Dépose un montant (nécessairement positif) sur ce compte
     * 
     * @param montant   le montant à déposer.
     * @return true si l'opération s'est bien passée
     */
    virtual bool depose(double montant);

    /**
     * Retire un montant (nécessairement positif) sur ce compte.
     * 
     * @param montant   le montant à retirer.
     * @return true si l'opération s'est bien passée
     */
    virtual bool retrait(double montant);
    
    /**
     * Effectue un virement. Le montant est transféré depuis
     * l'objet compte courant vers l'objet compte fournis en
     * paramètre.
     * 
     * @param compteDest	la destination du montant viré
     * @param montant		le montant viré
     */
    bool virement(Compte * compteDest, double montant);

private:
    /**
     * Definit le solde de ce compte.
     */
    void setSolde(double theValue);
    
    
    /**
     * Definit le nom du propriétaire de ce compte.
     */
    void setNomProprietaire(std::string theValue);
    
    
    /**
     * Définit le numéro de compte de ce compte.
     */
    void setNumeroDeCompte(long theValue);
    
    


    /**
     * Le nom du propriétaire, ne peut pas être null.
     */
    std::string _nomProprietaire;

    /**
     * Le numéro du compte.
     */
    long _numeroDeCompte;

    /**
     * Le solde du compte, peut être négatif.
     */
    double _solde;

    /**
     * Le prochain numéro de compte.
     */
    static long _prochainNumeroDeCompte;
};

/**
 * Affiche un compte bancaire sur un flux de sortie
 */
std::ostream & operator<<(std::ostream & st, const Compte & cpt);

#endif /* COMPTE_H */
