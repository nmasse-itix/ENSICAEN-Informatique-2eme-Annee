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

/*
 * @Fait	tout
 *
 * @Afaire	-
 */



#ifndef LIVRET_H
#define LIVRET_H

#include "Compte.h"

/**
 * Un livret est un compte dont le solde ne peut être négatif. Il est rémunéré
 * sur la base d'un taux d'intérêts spécifié à l'ouverture que l'on suppose fixe
 * 
 * @author Thomas LIMIN
 * @author Nicolas MASSE
 */
class Livret : public Compte {
public:

    /**
     * Constructeur de livret.
     * 
     * @param nom		le nom du titulaire du compte
     * @param taux		le taux d'intêret
     * @param solde		le solde initial du compte
     */
    Livret(std::string nom, double taux = 0, double solde = 0);

    /**
     * Destructeur
     */
    ~Livret();

    /**
     * Retrait. Sur un livret, il est impossible d'avoir un solde négatif.
     * La méthode de retrait prend en compte cette restriction et interdit
     * les retrait qui mettraient dans cette situation.
     * 
     * @param montant		le montant du retrait
     * @return true si le retrait a bien été effectué
     */
    bool retrait(double montant);

    /**
     * Calcule les interêts perçus sur ce compte.
     * Cette valeur correspond à la somme mini présente
     * sur le compte depuis la dernière prise d'interêts
     * par le taux d'interêt. Le montant perçu est immédiatement
     * ajouté au compte.
     * 
     * @return le montant des interêts perçus
     */
    double priseDInterets();


    /**
     * Met à jour le taux d'interêt. Doit être >= 0
     *
     * @param taux	le nouveaux taux d'interêt
     * @return true si modification réussie
     */
    bool setTaux(double taux);

    /**
     * Retourne le taux d'interêt associé à ce livret
     * 
     * @return le taux d'interêt
     */
    virtual double taux() const;

    /**
     * Retourne le taux d'interêt associé à ce livret
     * 
     * @return le solde minimum
     */
    double soldeMini() const;

    /**
     * Retourne une représentation textuelle de ce Livret.
     */
    std::string toString() const;


private:
  
    /**
     * Met à jour le sole minimum. Doit être >= 0
     *
     * @param solde	le nouveaux solde minimum
     * @return true si modification réussie
     */
    bool setSoldeMini(double solde);



    /**
     * Le taux d'interêt appliqué à ce livret
     */
    double _taux;

    /**
     * Le solde mnimum de ce compte depuis la dernière prise d'interêts
     */
    double _soldeMini;

};

#endif
