/**
 * #(@)RoutingTable.cpp             ENSICAEN                       2005
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
 * Implementation of the RoutingTable.
 */

/*
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */

#include "RoutingTable.h"


using namespace std;


RoutingTable::RoutingTable()
        : BasicRoutingTable() {}


RoutingTable::~RoutingTable() {
    for (BasicRoutingTable::const_iterator i = this->begin();
            i != this->end();
            ++i) {

        delete i->second;

    }
}

bool RoutingTable::contains(const string & host) const {
    BasicRoutingTable::const_iterator it = this->find(host);

    return it != this->end();
}

bool RoutingTable::update(const string & dstHost, Host & gateway, int cost, int * updatedCost) {

    bool updated = false;

    RoutingTable::iterator it = this->find(dstHost);

    if (it != this->end()) {
        // dstHost is already present in the routing table...
        // check if the new cost is lower than the older
        RoutingTableEntry * rte = (*it).second;

        if (cost < rte->cost()) {
            // a shorter way to reach dstHost has been found, table entry
            // must be updated
            rte->cost(cost);
            rte->gateway(gateway);
            *updatedCost = cost;
            updated = true;
        } else if ((&gateway == &rte->gateway())) {
          // change must be apply because it come from the current gateway to reach
          // the wanted host
            cout << "Modification from GW: route to " << dstHost << " through " << gateway.hostname() << " with " << cost << " hops" << std::endl;
            
                rte->cost(cost);
                *updatedCost = cost;
                updated = true;
        } else if (cost >= INFINITE) {
                  std::cout <<  "Host receive broken route to " << dstHost << " from a neighbor which is not the gateway" << std::endl;
                  *updatedCost = rte->cost();
                  
                  updated = true;
        } else {
            std::cout << "Default case: route to " << dstHost << " through " << gateway.hostname() << " with " << cost << " hops" << std::endl;
        }
    } else {
        // dstHost is not in the routing table, it must be added
        (*this)[dstHost] = new RoutingTableEntry(gateway, cost);
        *updatedCost = cost;
        updated = true;
    }

    return updated;

}

// bool RoutingTable::remove(const std::string & dstHost) {
//   bool result = false;
//   RoutingTable::iterator it = this->find(dstHost);
//
//   if (it != this->end()) {
//     // the matching table entry has been found
//     RoutingTableEntry * rte = it->second;
//     delete rte;
//     this->erase(it);
//     result = true;
//   }
//
//   return result;
//
// }


std::ostream & operator <<(std::ostream & st, const RoutingTable & rt) {
    rt.printOn(st);

    return st;
}

void RoutingTable::printOn(std::ostream & st) const {
    for (BasicRoutingTable::const_iterator i = this->begin();
            i != this->end();
            ++i) {

        st << "[route to \"" << i->first
        << "\" through \"" << i->second->gateway().hostname()
        << "\" with " << i->second->cost() << " hops]" << endl;
    }
}

RoutingTableEntry & RoutingTable::routingTableEntry(const std::string & host) const {
    BasicRoutingTable::const_iterator it = this->find(host);
    RoutingTableEntry * rte = 0;

    if (it != this->end()) {
        rte = it->second;
    }

    return *rte;
}


