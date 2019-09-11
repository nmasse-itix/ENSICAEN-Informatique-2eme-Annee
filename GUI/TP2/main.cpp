/**
 * @file   main.cc
 * @author Sebastien Fourey
 * @date   Mon Jan 3  2005
 * 
 * @brief  Programme principale d'un exemple
 * d'application Qt.
 * 
 */

#include <qapplication.h>
#include "MainWidget.h"

int
main(int argc, char * argv[])
{
  QApplication app(argc,argv);  
  QWidget * mainWidget = new MainWidget();

  // Connecte le signal askForQuit() émis par
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
