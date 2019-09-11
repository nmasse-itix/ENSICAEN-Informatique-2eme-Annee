/**
 * #(@)statview.h             ENSICAEN                       2005
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



#ifndef STATVIEW_H
#define STATVIEW_H

#include <qlabel.h>

#include "htmldocmodel.h"

/**
 * Cette classe est une vue statistique de la page HTML.
 * Elle affiche le nombre de caractères et de lignes dans
 * le code source de la page. Les objets de cette classe
 * sont destinés à être placés dans une barre d'état.
 * 
 * @author Nicolas MASSE <nicolas27.masse@laposte.net>
 * @author Thomas LIMIN <thomas.limin@laposte.net>
 */
class StatView : public QLabel {

    Q_OBJECT

public slots:
    /**
     * Ce slot est activé lorsque le code source de la page HTML a changé.
     */
    void sourceChanged(QString * text);

public:
    StatView(HTMLDocModel * model, QWidget *parent = 0, const char *name = 0);

    ~StatView();

private:
    /**
     * Le modèle.
     */
    HTMLDocModel * _docModel;
};

#endif
