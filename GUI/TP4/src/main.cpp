/** 
 * #(@)main.cpp             ENSICAEN                       2005
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

#include <qapplication.h>
#include <qtextcodec.h>

#include "MainWindow.h"


int main(int argc, char * argv[]) {

    // réglage du charset avec lequel QT lit les chaine de type C dans le code
    QTextCodec * codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForCStrings (codec);

    QApplication app(argc, argv);
    QWidget * mainWindow = new MainWindow();

    // Connecte le signal askForQuit() émis par
    // le Widget principal au slot quit() de l'objet
    // application.
    QObject::connect(mainWindow, SIGNAL(askForQuit()),
    		   &app, SLOT(quit()));

    // Precise a l'objet application quel est le widget de
    // la fenetre principale.
    app.setMainWidget(mainWindow);
    
    // Provoque l'affichage de la fenetre principale.
    mainWindow->show();

    // Passe la main a la boucle d'evenements.
    return app.exec();
}
