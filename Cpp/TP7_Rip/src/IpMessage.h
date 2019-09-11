/**
 * #(@)IpMessage.h             ENSICAEN                       2005
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
 * Defines an IP message.
 */

/*
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */



#ifndef IPMESSAGE_H
#define IPMESSAGE_H

#include <string>

/**
 * Represents an IP message.
 * 
 * @author Nicolas MASSE
 * @author Thomas LIMIN
 */
class IpMessage {
public:
    /**
     * Constructs an IP message.
     * 
     * @param srcHost       the source host.
     * @param dslHost       the hostname of the destination host.
     * @param cost          the number of hops needed to reach the destination
     *                      host.
     */
    IpMessage(const std::string & srcHost, const std::string & dstHost,
              const std::string & message);

    /**
     * Destructs this IP message.
     */
    ~IpMessage();

    /**
     * Prints the details about this RIP message on the output stream.
     * 
     * @param st            the output stream.
     */
    void printOn(std::ostream & st) const;

    /**
     * Returns the name of the host who sent this message.
     */
    const std::string & srcHost() const;

    /**
     * Returns the name of the destination host.
     */
    const std::string & dstHost() const;

    /**
     * Returns the number of hops needed to reach the destination host.
     */
    const std::string & message() const;

private:
    std::string _srcHost;
    std::string _dstHost;
    std::string _message;
};

/**
 * Prints the details about the IP message on the output stream.
 */
std::ostream & operator<<(std::ostream & st, const IpMessage & msg);


#endif /* RIPMESSAGE_H */
