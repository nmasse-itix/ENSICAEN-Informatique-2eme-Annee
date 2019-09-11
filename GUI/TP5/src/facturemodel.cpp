/**
 * #(@)facturemodel.cpp             ENSICAEN                       2005
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
 * @version     0.0.1
 *
 * @done        -
 *
 * @todo        -
 */

#include "facturemodel.h"

#include <iostream>
using namespace std;

FactureModel::FactureModel(FactureImpl * facture, QObject * parent, const char * name) : QObject(parent, name) {
    this->_ui = facture;
}


FactureModel::~FactureModel() {}



const QString & FactureModel::nom() const {
    return _nom;
}


void FactureModel::setNom(const QString& theValue) {
    _nom = theValue;
    this->notify();
}


const QString & FactureModel::prenom() const {
    return _prenom;
}


void FactureModel::setPrenom(const QString& theValue) {
    _prenom = theValue;
    this->notify();
}


const QString & FactureModel::adresse1() const {
    return _adresse1;
}


void FactureModel::setAdresse1(const QString& theValue) {
    _adresse1 = theValue;
    this->notify();
}


const QString & FactureModel::adresse2() const {
    return _adresse2;
}


void FactureModel::setAdresse2(const QString& theValue) {
    _adresse2 = theValue;
    this->notify();
}


const QString & FactureModel::codePostal() const {
    return _codePostal;
}


void FactureModel::setCodePostal(const QString& theValue) {
    _codePostal = theValue;
    this->notify();
}


const QString & FactureModel::ville() const {
    return _ville;
}


void FactureModel::setVille(const QString& theValue) {
    _ville = theValue;
    this->notify();
}

void FactureModel::celluleChangee(int row, int col) {
    _table[row][col] = _ui->factureTable->text(row, col);
    this->notify();
}

void FactureModel::notify() {
    emit factureChanged();
}

const QString & FactureModel::cellule(int row, int col) const {
    return _table[row][col];
}
