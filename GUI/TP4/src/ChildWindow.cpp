/**
 * #(@)ChildWindow.cpp             ENSICAEN                       2005
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


#include "ChildWindow.h"

#include <qtextedit.h>
#include <qlayout.h>
#include <qsplitter.h>
#include <qtabwidget.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qstatusbar.h>

#include <iostream>
using namespace std;

// Alloue de l'espace pour la variable statique
int ChildWindow::nDocuments = 1;

ChildWindow::ChildWindow(QWidget * parent) : QMainWindow(parent, 0, WDestructiveClose) {
    this->initWidgets();

    this->setCaption(QString("Nouveau document ").append(QString::number(ChildWindow::nDocuments)));
    ChildWindow::nDocuments++;

    this->show();
}

ChildWindow::ChildWindow(QWidget * parent, const QString & fileName) : QMainWindow(parent, 0, WDestructiveClose) {
    this->initWidgets();

    if (_docModel->load(fileName)) {
        this->setCaption(fileName);
        this->show();
    } else {
        // Erreur, on ferme la fenêtre
        this->close();
        QMessageBox::critical(parent, "Impossible de charger le fichier", "Une erreur est survenue lors de l'ouverture du fichier.");
    }
}

void ChildWindow::initWidgets() {
    QSplitter * splitter = new QSplitter(this);
    this->setCentralWidget(splitter);

    // Shows the status bar
    QStatusBar * statusBar = this->statusBar();
    statusBar->show();

    QTabWidget * tw = new QTabWidget(splitter);

    _editor = new SourceEditor(tw);
    _docModel = new HTMLDocModel(_editor);
    _formattedView = new FormattedView(tw);

    _statView = new StatView(_docModel, statusBar);
    statusBar->addWidget(_statView, 0, true);

    _overView = new OverView(splitter);

    tw->addTab(_editor, "Code source");
    tw->addTab(_formattedView, "Rendu WYSIWYG");

    connect(_editor, SIGNAL(textChanged()),
            this, SLOT(textWindowViewDataModified()));

    connect(_docModel, SIGNAL(sourceChanged(QString *)),
            _formattedView, SLOT(sourceChanged(QString *)));

    connect(_docModel, SIGNAL(sourceChanged(QString *)),
            _overView, SLOT(sourceChanged(QString *)));

    connect(_docModel, SIGNAL(sourceChanged(QString *)),
            _statView, SLOT(sourceChanged(QString *)));

}

void  ChildWindow::closeEvent(QCloseEvent * e) {
    if (_docModel->isModified()) { // modifié ?
        int res = QMessageBox::question(this, "Enregistrement", "Le fichier a été modifié, voulez-vous enregistrer les modifications ?", QMessageBox::Yes | QMessageBox::Default, QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
        if (res == QMessageBox::Yes) {
            if (this->save()) { // enregistrement ok ?
                e->accept(); // on ferme la fenêtre
            } else {
                e->ignore(); // on refuse la fermeture de fenêtre
            }
        } else if (res == QMessageBox::No) {
            e->accept(); 
        } else { // cancel
            e->ignore();
        }
    } else {
        e->accept();
    }
}

bool  ChildWindow::save() {
    bool ret = false;
    
    if (_docModel->filename()) { // déjà un nom de fichier ?
        ret = _docModel->save();
    } else {
        ret = this->saveAs();
    }
    
    if (ret) {
        this->statusBar()->message("Enregistrement... Ok", 5000);
    } else {
        this->statusBar()->message("Enregistrement... Erreur", 5000);
    }

    return ret;
}

bool  ChildWindow::saveAs() {
    bool ret = false;
    
    QString filename = QFileDialog::getSaveFileName(0, "HTML documents (*.htm *.html)", this);
    if (filename != "") {
        if (_docModel->saveAs(filename)) {
            this->setCaption(filename);
            ret = true;
        } else {
            ret = false;
        }
    }

    return ret;
}

void  ChildWindow::textWindowViewDataModified() {
    _docModel->changeSource(_editor->text());
    _docModel->setNumLines(_editor->lines());
}
