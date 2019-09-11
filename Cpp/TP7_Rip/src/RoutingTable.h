/**
 * #(@)RoutingTable.h             ENSICAEN                       2005
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
 * 
 */

/*
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */

#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H

#include <map>

#include "Host.h"
class Host;                     // fallback

#include "RoutingTableEntry.h"
class RoutingTableEntry;	// fallback

#include "RipMessage.h"
class RipMessage;               // fallback

/** The parent class of the class RoutingTable */
typedef std::map<std::string, RoutingTableEntry *> BasicRoutingTable;

/**
 * Represents a routing table.
 * 
 * @author Nicolas MASSE <nicolas27.masse@laposte.net>
 * @author Thomas LIMIN <thomas.limin@laposte.net>
*/
class RoutingTable : public BasicRoutingTable {
public:
    /**
     * Constructs a new empty routing table.
     */
    RoutingTable();


    /**
     * Destructs this routing table.
     */
    ~RoutingTable();

    /**
     * Tests if this routing table contains the specified host.
     * 
     * @param host          the host.
     * @return              true if this routing table contains the host, 
     *                      else false.
     */
    bool contains(const std::string & host) const;

    /**
     * Returns the routing table entry of the specified host.
     * 
     * @param host          the host.
     * @return              the routing table entry of the host.
     */
    RoutingTableEntry & routingTableEntry(const std::string & host) const;

    /**
     * Adds a routing entry to this routing table. If an entry already exists
     * for this host, this function checks wether the newcost is lower in order to
     * update the routing table only when necessary.
     * 
     * @return	true if the routing table has been updated, false otherwise
     */
    bool update(const std::string & dstHost, Host & host, int cost, int * updatedCost);
    
    /**
     * Prints details about the routing table on the stream.
     * 
     * @param st            the stream.
     */
    void printOn(std::ostream & st) const;

private:
  
};

/**
 * Prints the details about the routing table on the output stream.
 */
std::ostream & operator<<(std::ostream & st, const RoutingTable & rt);

#endif /* ROUTING_TABLE_H */
