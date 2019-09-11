/**
 * #(@)htmldocmodel.h             ENSICAEN                       2005
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



#ifndef HTMLDOCMODEL_H
#define HTMLDOCMODEL_H

#include <qobject.h>
#include <qstring.h>

#include "sourceeditor.h"

/**
 * Le modèle MVC du projet.
 * 
 * @author Nicolas MASSE <nicolas27.masse@laposte.net>
 * @author Thomas LIMIN <thomas.limin@laposte.net>
 */
class HTMLDocModel : public QObject {
    Q_OBJECT

signals:
    /**
     * Ce slot est déclenché lorsque le code source la page a été 
     * modifié.
     */
    void sourceChanged(QString * source);

public:
    /**
     * Construit un nouveau modèle.
     */
    HTMLDocModel(SourceEditor * editor);

    /**
     * Détruit le modèle.
     */
    ~HTMLDocModel();

    /**
     * Retourne le code source de la page.
     */
    QString * getSource() const;
    
    /**
     * Définit le nombre de lignes dans la page.
     */
    void setNumLines(int lines);
    
    /**
     * Retourne le nombre de lignes dans le code source de la page.
     */
    int numLines();
    
    /**
     * Retourne le nombre de caractères dans le code source de la page.
     */
    int numChars();
    
    /**
     * Définit le nom de fichier de la page HTML.
     */
    void setFilename(const QString & name);
    
    /**
     * Retourne le nom de fichier de la page HTML.
     */
    QString * filename();

    /**
     * Retourne l'état de modification de la copie du fichier en mémoire.
     */
    bool isModified();
    
public slots:
    /**
     * Change le code source de la page
     */
    void changeSource(const QString & string);

    /**
     * Enregistre le code source de la page sur le disque.
     */
    bool save();
    
    /**
     * Charge le code source de la page.
     */
    bool load(const QString & fileName);
    
    /**
     * Enregistre le code source de la page dans le fichier spécifié.
     */
    bool saveAs(const QString & fileName);
    
    /**
     * Prévient les écouteurs que le code source a été modifié.
     */
    void update();

private:
    /**
     * L'éditeur de code source.
     */
    SourceEditor * _editor;
    
    /**
     * Le code source de la page.
     */
    QString * _source;
    
    /**
     * Le nom de fichier.
     */
    QString * _filename;
    
    /**
     * Le nombre de lignes dans le code source de la page.
     */
    int _numLines;
    
    /**
     * État de modification de la page.
     */
    bool _modified;
};

#endif
