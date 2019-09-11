/**
 * #(@)IpMessage.cpp             ENSICAEN                       2005
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
 * Implementation of the class IpMessage.
 */

/*
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */


#include <iostream>

#include "IpMessage.h"

using namespace std;


IpMessage::IpMessage(const std::string & srcHost, const std::string & dstHost, 
                     const std::string & message) : _message(message), _srcHost(srcHost),
                    _dstHost(dstHost) {}


IpMessage::~IpMessage() {}


std::ostream & operator<<(std::ostream & st, const IpMessage & msg) {
    msg.printOn(st);

    return st;
}

void IpMessage::printOn(std::ostream & st) const {
    st << "<host \"" << _srcHost
            << "\" says \"" << _message
            << "\" to host \"" << _dstHost << "\">";
}


const std::string & IpMessage::srcHost() const {
    return _srcHost;
}


const std::string & IpMessage::dstHost() const {
    return _dstHost;
}


const std::string & IpMessage::message() const {
    return _message;
}
