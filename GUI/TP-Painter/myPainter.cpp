 /**
 * #(@)myPainter.cpp              ENSICAEN                       2006-02-22
 *
 * @author MASSE Nicolas (2004-Groupe4-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2004-Groupe4-MASSE) <thomas.limin@laposte.net>
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * Description des objectifs du programme, le sujet a traiter.
 * Pour le programme qui contient le main(),
 * la ligne de commande pour executer le programme.
 */


/**
 * Description succinte de l'algorithme utilise comme solution.
 * Eventuellement: Les references (cahier des charges,bibliographiques...).
 */

/*
 * @version	0.0.1
 *
 * @Fait:  Detail de ce qui a ete fait.
 *
 * @Afaire: Detail de ce qui n'a pas ete fait.
 */

 
#include <qapplication.h>
#include "MyPainter.h"

int main(int argc, char * argv[]) {
  QApplication app(argc,argv);  
  QWidget * mainWidget = new MyPainter();

  // Connecte le signal askForQuit() émit par
  // le Widget principal au slot quit() de l'objet
  // application.
  QObject::connect(mainWidget,SIGNAL(askForQuit()),
		   &app,SLOT(quit()));

  // Precise a l'objet application quel est le widget de 
  // la fenetre principale.
  app.setMainWidget(mainWidget);
  // Provoque l'affichage de la fenetre principale.
  mainWidget->show();

  // Passe la main a la boucle d'evenements.
  return app.exec();
}
