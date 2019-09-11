/**
 * #(@)htmldocmodel.cpp             ENSICAEN                       2005
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


#include "htmldocmodel.h"

#include <qfile.h>

HTMLDocModel::HTMLDocModel(SourceEditor * editor)
        : QObject() {

    this->_source = new QString();
    this->_filename = 0;
    this->_numLines = 0;
    this->_editor = editor;
    this->_modified = false;
}


HTMLDocModel::~HTMLDocModel() {
    delete this->_source;
}

QString * HTMLDocModel::getSource() const {
    return this->_source;
}

void HTMLDocModel::changeSource(const QString & string) {
    delete this->_source;
    this->_source = new QString(string);
    this->_modified = true;

    this->update();
}

void HTMLDocModel::setNumLines( int lines ) {
    this->_numLines = lines;
}

int HTMLDocModel::numLines( ) {
    return this->_numLines;
}

int HTMLDocModel::numChars( ) {
    if (_source) {
        return this->_source->length();
    } else {
        return 0;
    }
}

void HTMLDocModel::setFilename(const QString & name) {
    delete this->_filename;
    this->_filename = new QString(name);
}

QString * HTMLDocModel::filename() {
    return this->_filename;
}

bool HTMLDocModel::save() {
    bool ret = false;
    
    QFile file(*_filename);
    file.open(IO_WriteOnly);
    
    if (file.isOpen()) { // ouverture réussie ?
        QTextStream stream(&file);

        stream << *_source;

        file.close();
        this->_modified = false;
        
        ret = true;
    }
    
    return ret;
}

bool HTMLDocModel::load( const QString & fileName ) {
    bool ret = false;
    
    QFile file(fileName);
    file.open(IO_ReadOnly);

    if (file.isOpen()) { // ouverture réussie ?
        QByteArray arr = file.readAll();
        QString data(arr.data());
        file.close();
        this->changeSource(data);
        _editor->setText(data);

        this->setFilename(fileName);
        this->_modified = false;
        
        ret = true;
    }

    return ret;
}

bool HTMLDocModel::saveAs(const QString & fileName) {
    this->setFilename(fileName);
    return this->save();
}

bool HTMLDocModel::isModified( ) {
    return this->_modified;
}

void HTMLDocModel::update( ) {
    emit sourceChanged(this->_source);
}

