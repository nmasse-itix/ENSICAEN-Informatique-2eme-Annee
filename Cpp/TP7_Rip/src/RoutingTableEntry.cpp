/**
 * #(@)RoutingTableEntry.cpp             ENSICAEN                       2005
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
 * Implementation of the RoutingTableEntry class.
 */

/*
 * @version	2006-01-03
 *
 * @done	-
 *
 * @todo	-
 */


#include <iostream>

#include "RoutingTableEntry.h"

using namespace std;

RoutingTableEntry::RoutingTableEntry(Host & gateway, int cost) : _gateway(&gateway), _cost(cost) { }

Host& RoutingTableEntry::gateway() const {
  return (* _gateway);
}




int RoutingTableEntry::cost() const {
    return _cost;
}

void RoutingTableEntry::cost(int cost) {
  _cost = cost;
}

void RoutingTableEntry::gateway(Host & gateway) {
  _gateway = &gateway;
}
