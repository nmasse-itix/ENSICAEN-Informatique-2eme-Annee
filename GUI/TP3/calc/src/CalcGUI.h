/**
 * #(@)CalcGUI.h             ENSICAEN                       2005
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
 * GUI of the calc.
 */

#include <iostream>


/*
 * @version	0.0.1
 *
 * @done	all
 *
 * @todo	none
 */



#ifndef CALCGUI_H
#define CALCGUI_H

#include <qobject.h>
#include <qmainwindow.h>
#include <qlabel.h>


#include "Controller.h"

/**
 * @author Nicolas MASSE
 */
class CalcGUI : public QMainWindow {
    Q_OBJECT

public:
    /**
     * Constructs a new GUI.
     */
    CalcGUI();

    /**
     * Destructs the GUI.
     */
    ~CalcGUI();

public slots:
    /**
     * Called when a digit button is pressed.
     */
    void buttonClicked(int n);
    
    /**
     * Called when cancel button pressed.
     */
    void cButtonClicked(void);
    
    /**
     * Called to quit the app.
     */
    void quitApp(void);
    
    /**
     * Called in order to display help.
     */
    void displayHelp(void);
    
    /**
     * Updates the label of the calc.
     */
    void updateLabel(void);

private:
    Controller ctr;
    QLabel * lbl1;
};

#endif /* CALCGUI_H */
