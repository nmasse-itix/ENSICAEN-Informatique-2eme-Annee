/**
 * #(@)Host.h             ENSICAEN                       2005
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
 * Represents a host in a network.
 */

#include <iostream>
#include <set>

/**
 * See the description of the Bellman-Ford algorithm.
 */

/*
 * @version	2006-01-03
 *
 * @done	-
 *
 * @todo	-
 */



#ifndef HOST_H
#define HOST_H

#include <string>

#define INFINITE 100

#include "RoutingTable.h"
class RoutingTable;         // fallback

#include "RipMessage.h"
class RipMessage;           // fallback

#include "IpMessage.h"
class IpMessage;            // fallback

#include "Network.h"
class Network;              // fallback

/**
 * Represents a host of a network.
 * 
 * @author Nicolas MASSE
 * @author Thomas LIMIN
 */
class Host {
public:
    /**
     * Constructs a new host with the specified name and no friend.
     * 
     * @param hostname      the hostname.
     */
    Host(std::string hostname);

    /**
     * Destructs this host.
     */
    ~Host();

    /**
     * Returns the hostname.
     * 
     * @return              the hostname.
     */
    std::string hostname() const;

    /**
     * Adds a neighbor.
     * 
     * @param neighbor          the neighbor.
     */
    bool addNeighbor(Host & neighbor);
    
    /**
     * Remove a neighbor
     * 
     * @param neighbor		the neighbor
     */
    bool removeNeighbor(Host & neighbor);
    
    /**
     * Broadcasts the RIP message to all neighbors, 
     * except if the neighbor is the dstHost of the rip mesg
     * 
     * @param msg           the RIP message.
     */
    void broadcastRipMessage(const RipMessage & msg) const;

    /**
     * Broadcasts the routing table of this host to its neighbors.
     * 
     */
    void broadcastRoutingTable(void);
    
    /**
     * Prints details about the host on the stream.
     * 
     * @param st            the stream.
     */
    void printOn(std::ostream & st) const;
    
    
    /**
     * Asks this host to handle a RIP message.
     * 
     * @param message       the RIP message to handle.
     */
    void handleRipMessage(const RipMessage & msg);
    
    /**
     * Asks this host to handle an IP message.
     * 
     * @param message       the IP message to handle.
     */
    void handleIpMessage(const IpMessage & msg);
    
    /**
     * Send the rip message to destination if it is usefull:
     * 	-  if rip message indicate a route to reach destination
     *  -  if the destination is the gateway to reach the dstHost of the rip message
     */
    void sendRipMessage(Host & dest, const RipMessage & msg) const;
    
    
private:
    /**
     * Initializes the routing table of this host.
     */
    void initRoutingTable(void);

    /**
     * The hostname.
     */
    std::string _hostname;

    /**
     * The routing table.
     */
    RoutingTable * _routingTable;
    
    /**
     * A Collection of neighbors. A set is use because hosts must
     * appears only one time in this collection
     */
    std::set<Host *> _neighbors;
    
};

/**
 * Prints the details about the host on the output stream.
 */
std::ostream & operator<<(std::ostream & st, const Host & host);

/**
 * Compares two host, using their name.
 * 
 * @param h1        the first host.
 * @param h2        the second host.
 * @return          true if h1.hostname() == h2.hostname()
 */
bool operator==(const Host & h1, const Host & h2);

#endif /* HOST_H */

