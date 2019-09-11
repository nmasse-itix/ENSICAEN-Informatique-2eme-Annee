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


#ifndef COMPTECHEQUE_H
#define COMPTECHEQUE_H

#include <iostream>

#include <Compte.h>

/**
 * Un compte chèque est un compte pour lequel il existe un montant maximum de
 * découvertautorisé. Outre cette donnée, on pourra donc ajouter une méthode pemettant
 * d'obtenir ou de modifier ce montant. L'opération de retrait devra tenir compte de
 * cette nouvelle donnée.
 * 
 * @author Nicolas MASSE
 * @author Thomas LIMIN
*/
class CompteCheque : public Compte {

public:
  /**
   * Constructeur de compte cheque
   * 
   * @param nom			le nom du titulaire du comte
   * @param decouvertAutorisé	le montant de découvert autorisé (0 par défaut)
   * @param solde		le solde du compte (0 par défaut)
   */
    CompteCheque(std::string nom, double decouvertAutorise = 0, double solde = 0);
    
    /**
     * Destructeur
     */
    ~CompteCheque();

    /**
     * Effectue un retrait si et seulement si le solde après retrait est supérieur
     * ou égal au montant de découvert autorisé
     * 
     * @param montant		le montant du retrait
     **/
    bool retrait(double montant);

    /**
     * Renseigne le montant de découvert autorisé. Le montant doit être
     * supérieur ou égal à 0, sans quoi le montant reste inchangé et false
     * est retourné.
     * 
     * @param decouvert		le montant de découvert autorisé
     * @return			true si le montant est correctement modifié
     */
    bool setDecouvertAutorise(double decouvert);

    /**
     * Retourne le montant de découvert autorisé
     *
     *  @return			decouvert autorisé
     */
    double decouvertAutorise() const;
    
    /**
     * Retourne une représentation textuelle de ce compte.
     */
    std::string toString() const;


private:

    /**
     * Le montant de découvert autorisé. Par exemple, la valeur
     * 200 indique que le solde minimum du compte est -200 (inclus)
     */
    double _decouvertAutorise;

};

#endif
