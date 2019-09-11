 /**
 * #(@)MyPainter.h            ENSICAEN                       2006-02-22
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

#ifndef _MYPAINTER_H_
#define _MYPAINTER_H_

#include <list>
#include <qwidget.h>

class MyPainter : public QWidget {

  // Pour indiquer a "moc" que cette classe
  // possede des signaux et des slots.
  Q_OBJECT

    public:

  MyPainter();


 protected:

  virtual void paintEvent (QPaintEvent * e);

  void mousePressEvent ( QMouseEvent * e );


 private:
  std::list<QPoint> _points;


};


#endif /* _MYPAINTER_H_ */
