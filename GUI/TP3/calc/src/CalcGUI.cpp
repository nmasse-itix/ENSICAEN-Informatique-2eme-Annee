/**
 * #(@)CalcGUI.cpp             ENSICAEN                       2005
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

/**
 * Implementation of the CalcGUI class.
 */

/*
 * @version	0.0.1
 *
 * @done	all
 *
 * @todo	none
 */


#include "CalcGUI.h"

#include <qpushbutton.h>
#include <qlayout.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <iostream>

using namespace std;

static char * labels[4][4] = {
                                 {"7", "8", "9", "+"},
                                 {"4", "5", "6", "-"},
                                 {"1", "2", "3", "/"},
                                 {"0", ".", "=", "*"}
                             };

static enum ButtonID ids[4][4] = {
                                     {Button_7, Button_8, Button_9, Button_Plus},
                                     {Button_4, Button_5, Button_6, Button_Minus},
                                     {Button_1, Button_2, Button_3, Button_Divide},
                                     {Button_0, Button_Dot, Button_Equal, Button_Multiply}
                                 };

CalcGUI::CalcGUI()
        : QMainWindow() {

    // Main widget
    QWidget * central = new QWidget(this);
    this->setCentralWidget(central);

    // Vertical layout
    QVBoxLayout * vbox1 = new QVBoxLayout(central);

    // Display
    this->lbl1 = new QLabel(central);
    this->lbl1->setText(ctr.getText());
    vbox1->addWidget(lbl1);

    // Button group
    QButtonGroup * group = new QButtonGroup(central);
    vbox1->addWidget(group);
    connect(group, SIGNAL(clicked(int)), this, SLOT(buttonClicked(int)));

    QGridLayout * grid = new QGridLayout(group, 4, 4);

    // Buttons
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            QPushButton * bt = new QPushButton(tr(labels[r][c]), group);
            bt->setAccel(tr(labels[r][c]));
            grid->addItem(new QWidgetItem(bt), r, c);
        }
    }

    // Erase button
    QPushButton * btC = new QPushButton(tr("C"), central);
    btC->setAccel(tr("C"));
    vbox1->addWidget(btC);
    connect(btC, SIGNAL(clicked()), this, SLOT(cButtonClicked()));

    // Quit button
    QPushButton * btQuit = new QPushButton(tr("Quit"), central);
    vbox1->addWidget(btQuit);
    connect(btQuit, SIGNAL(clicked()), this, SLOT(quitApp()));

    // File menu
    QPopupMenu * fileMenu = new QPopupMenu();
    QAction * quitAction = new QAction(tr("&Quit"), tr("Alt+X"), this);
    quitAction->setStatusTip(tr("Exit application"));
    quitAction->addTo(fileMenu);
    connect(quitAction, SIGNAL(activated()), this, SLOT(quitApp()));

    // Help menu
    QPopupMenu * helpMenu = new QPopupMenu();
    QAction * aboutAction = new QAction(tr("&About"), tr("F1"), this);
    aboutAction->setStatusTip(tr("Display help"));
    aboutAction->addTo(helpMenu);
    connect(aboutAction, SIGNAL(activated()), this, SLOT(displayHelp()));

    // Menu bar
    QMenuBar * menu = new QMenuBar(this);
    menu->insertItem(tr("&File"), fileMenu);
    menu->insertSeparator();
    menu->insertItem(tr("&Help"), helpMenu);
}


CalcGUI::~CalcGUI() {}

void CalcGUI::buttonClicked( int n ) {
    if (ctr.command(ids[n % 4][n / 4])) {
        updateLabel();
    }
}

void CalcGUI::cButtonClicked( void ) {
    if (ctr.command(Button_C)) {
        updateLabel();
    }
}

void CalcGUI::quitApp( void ) {
    QApplication::exit();
}

void CalcGUI::displayHelp( void ) {
    QMessageBox::information(this, "About", "(C) 2006 - Thomas LIMIN & Nicolas MASSE", QMessageBox::Ok);
}

void CalcGUI::updateLabel( void ) {
    this->lbl1->setText(ctr.getText());
}



