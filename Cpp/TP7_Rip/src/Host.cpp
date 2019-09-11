/**
 * #(@)Host.cpp             ENSICAEN                       2005
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
 * Implementation of the Host class.
 */

#include <iostream>

#include "Host.h"

using namespace std;

Host::Host(string hostname) :
_hostname(hostname),_routingTable(new RoutingTable()) {

    initRoutingTable();
    std::cout << "New Host: " << hostname << std::endl;
}


Host::~Host() {
    delete _routingTable;
}

ostream & operator<<(ostream & st, const Host & host) {
    host.printOn(st);

    return st;
}


std::string Host::hostname() const {
    return _hostname;
}

bool Host::addNeighbor(Host & neighbor) {
    // check if the host is already in the neighbors collection
    bool result = false;
    std::pair< std::set<Host *>::iterator, bool> place;
    place = _neighbors.insert(&neighbor);

    if (place.second == true) {
        RoutingTable::const_iterator  it, end;
        end = _routingTable->end();

        // dumping routing table to new neighbor via RipMessage
        for (it = _routingTable->begin(); it != end; ++it) {
            RoutingTableEntry * rte = (*it).second;
            RipMessage rip(*this, (*it).first, rte->cost());
            this->sendRipMessage(neighbor, rip);
        }
        result = true;
    }

    return result;
}


bool Host::removeNeighbor(Host & neighbor) {
    
    // remove the neighbor from neighbors list
    _neighbors.erase(&neighbor);
    
    // broadcast an infinite route towards all destination who used to
    // use the removed neighbor as getaway
    RoutingTable::iterator rtEnd = _routingTable->end();
    
    for (RoutingTable::iterator it = _routingTable->begin(); it != rtEnd; ++it) {
      RoutingTableEntry * rte = it->second;
      if (&(rte->gateway()) == &neighbor) {
        int updatedCost;
        _routingTable->update(it->first, rte->gateway(), INFINITE, &updatedCost);
        RipMessage msg(*this, it->first, INFINITE);
        this->broadcastRipMessage(msg); 
      }
    }
    
    return true;
}



void Host::broadcastRipMessage(const RipMessage & msg) const {
    for (std::set
                <Host *>::const_iterator i = _neighbors.begin();
                i != _neighbors.end();
                ++i) {

            this->sendRipMessage( *(*i), msg);
        }
}


void Host::broadcastRoutingTable(void) {
    for (BasicRoutingTable::const_iterator i = _routingTable->begin();
         i != _routingTable->end();
         ++i) {
             RipMessage m(i->second->gateway(), i->first, i->second->cost());
             this->broadcastRipMessage(m);
         }
}


void Host::initRoutingTable(void) {
    int cost;
    _routingTable->update
    (_hostname, *this, 0, &cost);
}

void Host::printOn(ostream & st) const {
    st << "Host: " << _hostname << "\nNeighbors:";
    set
        <Host *>::const_iterator it, end;

    end = _neighbors.end();

    for (it = _neighbors.begin(); it != end; ++it) {
        st << " " << (*it)->hostname();
    }

    st << "\nRoutingTable: " << endl << *_routingTable << endl;
}

void Host::handleRipMessage(const RipMessage & msg) {
    cout << _hostname << ": Received RIP message: " << msg << endl;

    int cost = msg.cost() + 1;

    int newCost;

    if (_routingTable->update(msg.dstHost(), msg.srcHost(), cost, &newCost)) {
        // routing table has been updated
        RipMessage newMsg(*this, msg.dstHost(), newCost);
        this->broadcastRipMessage(newMsg);
 
    }
}



bool operator ==(const Host & h1, const Host & h2) {
    return h1.hostname() == h2.hostname();
}

void Host::sendRipMessage( Host & dest, const RipMessage & msg ) const {
    // dont send to the dest if rip message
    // indicate a route to reach it
    if (dest.hostname() != msg.dstHost()) {
        // dont send rip message if the dst is the gateway to reach the dstHost
        // => split horizon
        RoutingTableEntry * rte = (*_routingTable)[msg.dstHost()];
        if (&(rte->gateway()) != &dest) {
            std::cout << _hostname << " sending Rip message to " << dest.hostname() << std::endl;
            Network::addToQueue(&dest, msg);
        }
    }

}

void Host::handleIpMessage(const IpMessage & msg) {
    cout << _hostname << " received a message : " << msg << endl;
    
    if (msg.dstHost() == _hostname) {
      cout << _hostname << ": It's for me !" << endl;
    } else {
        Host & h = (*_routingTable)[msg.dstHost()]->gateway();
        h.handleIpMessage(msg);
    }
    
}

