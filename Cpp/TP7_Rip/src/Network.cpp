/**
 * #(@)Network.cpp             ENSICAEN                       2006-01-03
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
 * Implementation of the Network class
 */

#include "Network.h"
#include "IpMessage.h"

/*
 * @version	2006-01-03
 *
 * @done	-
 *
 * @todo	-
 */


std::deque<std::pair<Host *, RipMessage> > Network::_queue;


Network::Network() : _hosts() {}


Network::~Network( ) {
    std::map<std::string, Host *>::const_iterator i;

    // destroy Host dynamic object
    for (i = _hosts.begin(); i != _hosts.end(); ++i) {
        delete i->second;
    }
}


bool Network::growNetwork( std::istream & data ) {
    std::string line;
    const std::string delims = " \t";

    int wordNbr;
    std::string words[2];

    // loop until end of stream is reached
    while (std::getline(data, line)) {
        // cut the line into wordsHostHost
        std::string::size_type idBegin, idEnd;
        wordNbr = 0;

        // search beginning of the first word
        idBegin = line.find_first_not_of(delims);

        // while beginning of a word found
        while ((idBegin != std::string::npos)  && (wordNbr < 2)) {
            // search end of the actual word
            idEnd = line.find_first_of(delims, idBegin);

            if (idEnd == std::string::npos) {
                // end of word is end of line
                idEnd = line.length();
            }

            words[wordNbr] = line.substr(idBegin, idEnd - idBegin);
            ++ wordNbr;
            // search beginning of an other word
            idBegin = line.find_first_not_of(delims, idEnd);
        }
        
        if (wordNbr >= 2) {
            // we have enough information to create a new Link
            this->addLinkBetween(words[0], words[1]);
        }
    }
}


bool Network::addLinkBetween(const std::string & nameHostA, const std::string & nameHostB) {
    std::map<std::string, Host *>::const_iterator it;
    Host * hostA;
    Host * hostB;
    bool result = false;

    it = _hosts.find(nameHostA);

    if (it == _hosts.end()) {
        // host not found in network, we need to crete a new Host and insert it
        hostA = new Host(nameHostA);
        _hosts.insert(std::make_pair<std::string, Host*>(nameHostA, hostA));
    } else {
        // host found
        hostA = it->second;
    }

    it = _hosts.find(nameHostB);

    if (it == _hosts.end()) {
        // host not found in network, we need to crete a new Host
        hostB = new Host(nameHostB);
        _hosts.insert(std::make_pair<std::string, Host*>(nameHostB, hostB));
    } else {
        // host found
        hostB = it->second;
    }

    hostA->addNeighbor(*hostB);
    hostB->addNeighbor(*hostA);

    Network::processQueue();
  
    return result;
}

bool Network::removeLinkBetween( const std::string & nameHostA, const std::string & nameHostB ) {
  bool result = false;
  std::map<std::string, Host *>::const_iterator it;
  Host * hostA;
  Host * hostB;

  it = _hosts.find(nameHostA);

  if (it != _hosts.end()) {
    // host found
    hostA = it->second;
    result = true;
  }

  it = _hosts.find(nameHostB);

  if (it != _hosts.end()) {
    // host found
    hostB = it->second;
    result = result && true;
  }
  
  if (result) {
    result = hostA->removeNeighbor(*hostB) && hostB->removeNeighbor(*hostA); 
  }
  
  Network::processQueue();
  
  return result;
}



void Network::printOn(std::ostream & st) const {
    st << "Network: " << std::endl << "Hosts:" << std::endl;

    std::map<std::string, Host *>::const_iterator i;
    for (i = _hosts.begin(); i != _hosts.end(); ++i) {
        st << *((*i).second);
    }
}

void Network::broadcastTables(void) {
    std::map<std::string, Host *>::const_iterator i;
    for (i = _hosts.begin(); i != _hosts.end(); ++i) {
        i->second->broadcastRoutingTable();
    }
    
    Network::processQueue();
}


std::ostream & operator <<( std::ostream & st, const Network & n ) {
    n.printOn(st);
    return st;
}

Host * Network::getHost(std::string hostname ) const {
  Host * h = 0;
  std::map<std::string, Host *>::const_iterator it;
  it = _hosts.find(hostname);
  
  if (it != _hosts.end()) {
    h = (*it).second;
  }
  return h;
}


void Network::processQueue(void) {
    while (! _queue.empty()) {
        std::pair<Host *, RipMessage> p = _queue.front();
        _queue.pop_front();
        
        p.first->handleRipMessage(p.second);
    }
}

void Network::addToQueue(Host * h, const RipMessage & m) {
    _queue.push_back(std::make_pair<Host *, RipMessage>(h, m));
}

void Network::sendMessage(const std::string & nameHostA, 
                          const std::string & nameHostB, 
                          const std::string & message) {

                              Host * h = getHost(nameHostA);
                              IpMessage m(nameHostA, nameHostB, message);
                              
                              h->handleIpMessage(m);
}

