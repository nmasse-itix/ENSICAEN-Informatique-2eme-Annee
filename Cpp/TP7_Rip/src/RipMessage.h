/**
 * #(@)RipMessage.h             ENSICAEN                       2005
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
 * Defines a RIP message.
 */

/*
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */



#ifndef RIPMESSAGE_H
#define RIPMESSAGE_H

#include <string>

#include "Host.h"
class Host;             // fallback

/**
 * Represents a RIP message.
 * 
 * @author Nicolas MASSE
 * @author Thomas LIMIN
*/
class RipMessage {
public:
    /**
     * Constructs a RIP message.
     * 
     * @param srcHost       the source host.
     * @param dslHost       the hostname of the destination host.
     * @param cost          the number of hops needed to reach the destination host.
     */
    RipMessage(Host & srcHost, const std::string & dstHost, int cost);

    /**
     * Destructs this RIP message.
     */
    ~RipMessage();

    /**
     * Prints the details about this RIP message on the output stream.
     * 
     * @param st            the output stream.
     */
    void printOn(std::ostream & st) const;

    /**
     * Returns the host who sent this message.
     */
    Host& srcHost() const;

    /**
     * Returns the name of the destination host.
     */
    std::string dstHost() const;

    /**
     * Returns the number of hops needed to reach the destination host.
     */
    int cost() const;

private:
    Host & _srcHost;
    std::string _dstHost;
    int _cost;
};

/**
 * Prints the details about the RIP message on the output stream.
 */
std::ostream & operator<<(std::ostream & st, const RipMessage & msg);


#endif /* RIPMESSAGE_H */
