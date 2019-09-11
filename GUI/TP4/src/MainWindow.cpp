/** 
 * #(@)MainWindow.cpp             ENSICAEN                       2005
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

#include "MainWindow.h"

#include <qmenubar.h>
#include <qstring.h>
#include <qworkspace.h>
#include <qstatusbar.h>
#include <qmessagebox.h>

#include <iostream>
using namespace std;

MainWindow::MainWindow() {
    _workspace = new QWorkspace(this);
    this->setCentralWidget(_workspace);

    QPopupMenu * fileMenu = new QPopupMenu(this);
    fileMenu->insertItem("&Nouveau", this, SLOT(newDoc()), QKeySequence("CTRL+N"));
    fileMenu->insertItem("&Ouvrir...", this, SLOT(load()), QKeySequence("CTRL+O"));
    fileMenu->insertItem("&Enregistrer", this, SLOT(save()), QKeySequence("CTRL+S"));
    fileMenu->insertItem("Enre&gistrer sous...", this, SLOT(saveAs()));
    fileMenu->insertItem("&Fermer", this, SLOT(closeWindow()), QKeySequence("CTRL+W"));
    fileMenu->insertItem("&Quitter", this, SLOT(quit()), QKeySequence("CTRL+Q"));
    this->menuBar()->insertItem("&Fichier", fileMenu);

    _windowsMenu = new QPopupMenu(this);
    _windowsMenu->setCheckable( TRUE );
    connect(_windowsMenu, SIGNAL(aboutToShow()), 
            this, SLOT(windowsMenuAboutToShow()));
    this->menuBar()->insertItem("Fenê&tre", _windowsMenu);

    QPopupMenu * aboutMenu = new QPopupMenu(this);
    aboutMenu->insertItem("&A propos", this, SLOT(about()));
    this->menuBar()->insertItem("&Aide", aboutMenu);
    
    // le file dialog de l'application
    _fileDialog = new QFileDialog(this);
    _fileDialog->addFilter("HTML documents (*.htm *.html)");
    connect(_fileDialog, SIGNAL(fileSelected(const QString &)), 
            this, SLOT(load(const QString &)));
    
}

void MainWindow::load(const QString & filename) {
    ChildWindow * child = new ChildWindow(_workspace, filename);
}

void MainWindow::closeEvent(QCloseEvent * e) {
    // On ferme toutes les fenêtres
    QWidgetList windows = _workspace->windowList();
    for (int i = 0; i < int(windows.count()); ++i) {
        windows.at(i)->close();
    }
    
    // TODO : contrôler s'il reste encore des fenêtres ouvertes
    e->accept();
}

ChildWindow * MainWindow::newDoc() {
    ChildWindow * child = new ChildWindow(_workspace);
    return child;
}

void MainWindow::windowsMenuAboutToShow() {
    _windowsMenu->clear();
    int cascadeId = _windowsMenu->insertItem("&Cascade", _workspace, SLOT(cascade()));
    int tileId = _windowsMenu->insertItem("&Tile", _workspace, SLOT(tile()));

    if (_workspace->windowList().isEmpty()) {
        _windowsMenu->setItemEnabled( cascadeId, FALSE );
        _windowsMenu->setItemEnabled( tileId, FALSE );
    }

    _windowsMenu->insertSeparator();
    QWidgetList windows = _workspace->windowList();
    for ( int i = 0; i < int(windows.count()); ++i ) {
        int id = _windowsMenu->insertItem(windows.at(i)->caption(),
                                          this, SLOT(windowsMenuActivated( int ) ) );
        _windowsMenu->setItemParameter(id, i );
        _windowsMenu->setItemChecked( id, _workspace->activeWindow() == windows.at(i) );
    }
}

void MainWindow::load() {
    _fileDialog->show();
}

void MainWindow::save() {
    ChildWindow * win = dynamic_cast<ChildWindow *>(_workspace->activeWindow());
    if (win) {
        win->save();
    }
}

void MainWindow::saveAs() {
    ChildWindow * win = dynamic_cast<ChildWindow *>(_workspace->activeWindow());
    if (win) {
        win->saveAs();
    }
}

void MainWindow::closeWindow() {
    // TODO Si il n'y a pas de fenetre a fermer, le menu devrait être désactivé.
    QWidget * win = _workspace->activeWindow();
    if (win) {
      win->close();
    }
}

void MainWindow::about() {
    QMessageBox::about(this, "A propos...", "(C)2006 Thomas LIMIN & Nicolas MASSE");
}

void MainWindow::quit() {
    // On ferme toutes les fenêtres
    QWidgetList windows = _workspace->windowList();
    for (int i = 0; i < int(windows.count()); ++i) {
        windows.at(i)->close();
    }
    
    // TODO : contrôler s'il reste encore des fenêtres ouvertes
    emit askForQuit();
}

void MainWindow::windowsMenuActivated(int id) {
    QWidget* w = _workspace->windowList().at(id);
    if (w) {
        w->showNormal();
        w->setFocus();
    }
}
