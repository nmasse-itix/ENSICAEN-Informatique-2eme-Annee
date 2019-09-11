/**
 * #(@)factureimpl.cpp             ENSICAEN                       2005
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
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */



#include "factureimpl.h"
#include "factureview.h"

#include <qmessagebox.h>

#include <iostream>
using namespace std;

FactureImpl::FactureImpl(QWidget* parent, const char* name, WFlags fl)
        : Facture(parent,name,fl) {

    _model = new FactureModel(this);
    this->factureView->setModel(_model);
}

FactureImpl::~FactureImpl() {
    delete _model;
}

/*$SPECIALIZATION$*/
void FactureImpl::helpAbout() {
    QMessageBox::about(this, "A propos...", "(C)2006 Thomas LIMIN & Nicolas MASSE");
}

void FactureImpl::fileExit() {
    this->close();
}

void FactureImpl::filePrint() {
    QMessageBox::warning(this, "Not yet implemented...", "Not yet implemented !");
}

void FactureImpl::fileSaveAs() {
    QMessageBox::warning(this, "Not yet implemented...", "Not yet implemented !");
}

void FactureImpl::fileSave() {
    QMessageBox::warning(this, "Not yet implemented...", "Not yet implemented !");
}

void FactureImpl::fileOpen() {
    QMessageBox::warning(this, "Not yet implemented...", "Not yet implemented !");
}

void FactureImpl::fileNew() {
    QMessageBox::warning(this, "Not yet implemented...", "Not yet implemented !");
}

void FactureImpl::editClearAll() {
    QMessageBox::warning(this, "Not yet implemented...", "Not yet implemented !");
}

void FactureImpl::nomChanged( const QString & s ) {
    _model->setNom(s);
}

void FactureImpl::villeChanged( const QString & s ) {
    _model->setVille(s);
}

void FactureImpl::prenomChanged( const QString & s ) {
    _model->setPrenom(s);
}

void FactureImpl::adresse1Changed( const QString & s ) {
    _model->setAdresse1(s);
}

void FactureImpl::adresse2Changed( const QString & s ) {
    _model->setAdresse2(s);
}

void FactureImpl::cpChanged( const QString & s ) {
    _model->setCodePostal(s);
}

void FactureImpl::tableChanged(int row, int col) {
    
    switch (col) {
    case 2:
    case 3:
    case 4: 
    { // les colonnes 2, 3 et 4 sont liées
        QString q = this->factureTable->text(row, 2);
        QString p = this->factureTable->text(row, 3);
    
        double res = p.toDouble() * q.toDouble();
        this->factureTable->setText(row, 4, QString::number(res));
        _model->celluleChangee(row, 4);
        _model->celluleChangee(row, col);
    }
        break;
    default:
        _model->celluleChangee(row, col);
        break;
    }
    
}

