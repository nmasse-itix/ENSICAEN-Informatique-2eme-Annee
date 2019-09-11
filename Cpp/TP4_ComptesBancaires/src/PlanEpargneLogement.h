/** 
 * #(@)PlanEpargneLogement.h             ENSICAEN                     2005
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
 * Déclaration de la classe PlanEpargneLogement.
 */

 
#ifndef PLANEPARGNELOGEMENT_H
#define PLANEPARGNELOGEMENT_H

#include <iostream>

#include "Livret.h"

/**
 * Represente un plan epargne logement.
 *
 * @author Nicolas MASSE
 * @author Thomas LIMIN
 */
class PlanEpargneLogement : public Livret {

  public:
    
    /**
     * Constructeur de plan epargne logement.
     * 
     * @param nom	        le nom du titulaire du compte
     * @param taux		le taux d'intêret
     * @param solde		le solde initial du compte
     */
    PlanEpargneLogement(std::string nom, double taux = 0, double solde = 0);

    /**
     * Destructeur
     */
    ~PlanEpargneLogement();
    
    /**
     * Retrait. Sur un PEL, il est impossible d'avoir un solde négatif.
     * De plus le seul montant de retrait autorisé est le solde du PEL
     * La méthode de retrait prend en compte ces restrictions
     * 
     * @param montant		le montant du retrait
     * @return true si le retrait a bien été effectué
     */
    bool retrait(double montant);
    
    /**
     * Retourne le taux d'interêt. Pour un PEL, il correspond
     * au taux initial multiplié par le coefficient global
     * 
     * @return le taux;
     */
    double taux() const;
    
    /**
     * Retourne une représentation textuelle de ce compte.
     */
    std::string toString() const;
    
    /**
     * Permet de modifier le coefficient général
     * le coefficient doit être >= 0
     * 
     * @param coef	le nouveau coefficient
     * @return		true si ok
     */
    static bool setCoefficient(double coef);

	
    
  private:
    
    /**
     * Pour récupérer le coefficient
     * 
     * @return	le coefficient actuel
     */
    static double coefficient();
    
    /**
     * le coefficient qui est appliqué au taux de toutes les instance de PlanEpargneLogement
     * il est initialisé à 1 lors du chargement de la classe.
     */
    static double _coefficient;

};

#endif
