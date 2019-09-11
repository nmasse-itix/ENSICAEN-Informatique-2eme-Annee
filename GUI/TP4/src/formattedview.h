/**
 * #(@)formattedview.h             ENSICAEN                       2005
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



#ifndef FORMATEDVIEW_H
#define FORMATEDVIEW_H

#include <qtextedit.h>

/**
 * Cette classe affiche la page HTML formatée.
 * 
 * @author Nicolas MASSE <nicolas27.masse@laposte.net>
 * @author Thomas LIMIN <thomas.limin@laposte.net>
 */
class FormattedView : public QTextEdit {
    Q_OBJECT
            
public slots:
    /**
     * Ce slot est déclenché lorsque le code source la page a été 
     * modifié.
     */
    void sourceChanged(QString * text);
    
public:
    /**
     * Construit une nouvelle vue.
     */
    FormattedView(QWidget *parent = 0, const char *name = 0);

    ~FormattedView();

};

#endif
