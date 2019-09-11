/**
 * #(@)RipMessage.cpp             ENSICAEN                       2005
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
 * Implementation of the class RipMessage.
 */

/*
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */


#include <iostream>

#include "RipMessage.h"

using namespace std;


RipMessage::RipMessage(Host & srcHost, const std::string & dstHost, int cost)
        : _cost(cost), _srcHost(srcHost), _dstHost(dstHost) {}


RipMessage::~RipMessage() {}


std::ostream & operator<<(std::ostream & st, const RipMessage & msg) {
    msg.printOn(st);

    return st;
}

void RipMessage::printOn(std::ostream & st) const {
    st << "<host \"" << _srcHost.hostname()
    << "\" can reach host \"" << _dstHost
    << "\" with " << _cost << " hops>";
}


Host& RipMessage::srcHost() const {
    return _srcHost;
}


std::string RipMessage::dstHost() const {
    return _dstHost;
}


int RipMessage::cost() const {
    return _cost;
}
