/**
 * #(@)RoutingTableEntry.h           ENSICAEN                   2005
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
 * Represents an entry of a routing table.
 */

/*
 * @version	2006-01-03
 *
 * @done	-
 *
 * @todo	-
 */



#ifndef ROUTINGTABLEENTRY_H
#define ROUTINGTABLEENTRY_H

#include "Host.h"
class Host;		// fallback

/**
 * @author Nicolas MASSE
 * @author Thomas LIMIN
 */
class RoutingTableEntry {
public:
    /**
     * Creates a new routing table entry with the gateway and the cost specified.
     */
    RoutingTableEntry(Host& gateway, int cost = 0);


    /**
     * Returns the gateway host of this routing table entry.
     * 
     * @return      the neighbour host.
     */
    Host& gateway() const;
    
    /**
     * Set the gateway
     * 
     * @param gateway	the new gateway
     */
    void gateway(Host & gateway);


    /**
     * Returns the number of hops to reach the destination host.
     * 
     * @return      the number of hops needed to reach the destination host.
     */
    int cost() const;
    
    /**
     * Set the cost
     * 
     * @param cost	the new cost
     */
    void cost(int cost);

private:
    /**
     * The gateway.
     */
    Host * _gateway;

    /**
     * The number of hops to reach the destination host.
     */
    int _cost;
};

#endif /* ROUTINGTABLEENTRY_H */
