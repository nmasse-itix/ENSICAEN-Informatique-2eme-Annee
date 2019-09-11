/** 
 * #(@)MainWindow.h             ENSICAEN                       2005
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qworkspace.h>
#include <qstring.h>
#include <qpopmenu.h>
#include <qtranslator.h>
#include <qtoolbar.h>
#include <qfiledialog.h>
#include <qsplitter.h>

#include "ChildWindow.h"

/**
 * La fenêtre principale du projet.
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

signals:
    /**
     * Cette classe émet ce signal lorsqu'elle veut que l'application se termine.
     */
    void askForQuit();

public:

    /**
     * Construit une nouvelle fenêtre.
     */
    MainWindow();

protected:

    /*
     * @see QT's doc
     */
    void closeEvent(QCloseEvent *);

private slots:

    /**
     * Ce slot est activé par la fenêtre de sélection de fichiers
     * lorsque qu'un fichier est sélectionné.
     */
    void load(const QString & filename);

    /**
     * Créé un nouveau document vierge.
     */
    ChildWindow * newDoc();

    /**
     * Cette slot est activé lorsque le menu "fenêtre" est sur le
     * point d'être activé, afin de remettre celui-ci à jour.
     */
    void windowsMenuAboutToShow();

    /**
     * Propose à l'utilisateur d'ouvrir un fichier.
     */
    void load();

    /**
     * Enregistre le fichier.
     */
    void save();

    /**
     * Enregistre le fichier en demandant à l'utilisateur de 
     * choisir un nom de fichier.
     */
    void saveAs();

    /**
     * Quitte l'application.
     */
    void quit();

    /**
     * Ferme la fenetre fille active
     */
    void closeWindow();

    /**
     * Affiche des information à propos de ce logiciel.
     */
    void about();

    /**
     * Lorsqu'un item du menu windows est cliqué, ce slot est activé.
     */
    void windowsMenuActivated(int id);

private:

    /**
     * L'espace de travail de l'application.
     */
    QWorkspace * _workspace;

    /**
     * Le menu "fenêtre"
     */
    QPopupMenu * _windowsMenu;
    
    /**
     * La fenêtre de sélection de fichiers.
     */
    QFileDialog * _fileDialog;
};


#endif /* MAINWINDOW_H */
