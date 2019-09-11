/**
 * #(@)statview.cpp             ENSICAEN                       2005
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



#include "statview.h"

StatView::StatView(HTMLDocModel * model, QWidget *parent, const char *name)
        : QLabel(parent, name) {
        
    this->_docModel = model;
}


StatView::~StatView() {}

void StatView::sourceChanged(QString * /* text */) {
    QString lignes = QString::number(this->_docModel->numLines());
    QString cars = QString::number(this->_docModel->numChars());
    
    this->setText(QString("Lignes : ") + lignes + QString(" / Caractères : ") + cars);
}

