/** 
 * #(@)ChildWindow.h             ENSICAEN                       2005
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

#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <qmainwindow.h>
#include <qstring.h>

#include "sourceeditor.h"
#include "htmldocmodel.h"
#include "formattedview.h"
#include "overview.h"
#include "statview.h"

/**
 * Cette classe représentes les fenêtres filles MDI. Elles permettent
 * d'éditer du code HTML.
 * 
 * @author Nicolas MASSE <nicolas27.masse@laposte.net>
 * @author Thomas LIMIN <thomas.limin@laposte.net>
 */
class ChildWindow : public QMainWindow {

    Q_OBJECT

public:
    /**
     * Construit une nouvelle fenêtre avec une page HTML vierge.
     */
    ChildWindow(QWidget * parent);
    
    /**
     * Construit une nouvelle fenêtre et charge le fichier spécifié.
     */
    ChildWindow(QWidget * parent, const QString & fileName);

    /*
     * @see QT's doc
     */
    void closeEvent(QCloseEvent *);

    /**
     * Enregistre le fichier source.
     * 
     * @return true si le fichier a été enregistré, false sinon
     */
    bool save();

    /**
     * Enregistre le fichier source en demandant le nom de fichier
     * à l'utilisateur.
     * 
     * @return true si le fichier a été enregistré, false sinon
     */
    bool saveAs();

protected:

public slots:

    /**
     * Ce slot est déclenché lorsque le champ d'édition du code source
     * est modifié.
     */
    void textWindowViewDataModified();

private:
    /**
     * Initialise les widgets.
     */
    void initWidgets();
    
    /**
     * Nombre de documents créés depuis le lancement du programme.
     */
    static int nDocuments;

    /**
     * Champ d'édition du code source.
     */
    SourceEditor * _editor;
    
    /**
     * Le modèle.
     */
    HTMLDocModel * _docModel;
    
    /**
     * Une vue, affiche la page formatée.
     */
    FormattedView * _formattedView;
    
    /**
     * Une vue d'ensemble de la page.
     */
    OverView  * _overView;
    
    /**
     * Affiche des statistiques concernant le texte.
     */
    StatView * _statView;
};


#endif /* CHILDWINDOW_H */
