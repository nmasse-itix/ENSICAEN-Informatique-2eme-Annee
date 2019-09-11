/**
 * #(@)Network.h             ENSICAEN		2006-01-03
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

/*
 * @version	2006-01-03
 *
 * @done	-
 *
 * @todo	-
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <map>
#include <string>
#include <iostream>
#include <deque>

#include "Host.h"
class Host;     // fallback


/**
 * The Network class is in charge of building a Network, providing a data file
 * the network is the owner of the hosts
 */
class Network {

public:
    
  /**
   * Network default constructor
   */
  Network();
  
  /**
   * Network default destructor
   */
  ~Network();
  
  /**
   * Add the new hosts and links present in the data stream.
   * 
   * @param data	the stream from wich network data will be read
   * @return		bool
   */
  bool growNetwork(std::istream & data);
  
  /**
   * Add a link in the network.
   * A link is only a pair of hosts who are linked. If the hosts
   * doesn't appear in the network, they are added
   * 
   * @param nameHostA	the first host
   * @param nameHostB	the second host
   * @return		state of the operation
   */
  bool addLinkBetween(const std::string & nameHostA, const std::string & nameHostB);
  
  /**
   * Sends a message m from A to B
   * 
   * @param nameHostA	the first host
   * @param nameHostB	the second host
   * @param message     the message
   */
  void sendMessage(const std::string & nameHostA, const std::string & nameHostB, 
                   const std::string & message);
  
  /**
   * Remove a link between two hosts in the network
   *
   * @param nameHostA	the first host
   * @param nameHostB	the second host
   * @return		state of the operation
   */
  bool removeLinkBetween(const std::string & nameHostA, const std::string & nameHostB);
  
  /**
   * Write a representation of the network into a stream
   *
   * @param st	output stream
   */
  void printOn(std::ostream & st) const; 
  
  /**
   * Broadcast the routing table of each host to its neighbors.
   */
  void broadcastTables();
  
  /**
   * Retrieve an host thanks to its hostname
   * 
   * @param hostname		the hostname
   * @return			the host
   */
  Host * getHost(std::string hostname) const;

  
  /**
   * Process the queue.
   */
  static void processQueue(void);
       
  /**
   * Add a message to the queue. 
   * 
   * @param h       the destination host
   * @param m       the message
   */
  static void addToQueue(Host * h, const RipMessage & m);
    
    
  private:
    
    /**
     * the collection of Hosts in the network
     */
    std::map<std::string, Host *> _hosts;
    
    /**
     * The double ended queue.
     */
    static std::deque<std::pair<Host *, RipMessage> > _queue;
};


/**
 * Prints the details about the network on the output stream.
 */
std::ostream & operator<<(std::ostream & st, const Network & n);


#endif /* NETWORK_H */

