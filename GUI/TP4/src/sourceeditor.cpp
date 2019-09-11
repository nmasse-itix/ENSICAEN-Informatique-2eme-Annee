/**
 * #(@)sourceeditor.cpp             ENSICAEN                       2005
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



#include "sourceeditor.h"

SourceEditor::SourceEditor(QWidget *parent, const char *name)
        : QTextEdit(parent, name) {
        
    this->setTextFormat(Qt::PlainText);
}


SourceEditor::~SourceEditor() {}


