 /**
 * #(@)MyPainter.cpp              ENSICAEN                       2005-02-22
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


#include "MyPainter.h"
#include <qpainter.h>
#include <qmenubar.h>


MyPainter::MyPainter() {
  QMenuBar * menu = new QMenuBar(this);
  QPopupMenu * file = new QPopupMenu( menu );
  menu->insertItem( "&File", file );
}


void MyPainter::paintEvent (QPaintEvent * e) {

  QPainter paint(this);
  paint.fillRect(this->rect(), Qt::black);
  

  if(!_points.empty()) {

    paint.setPen(Qt::green);

    std::list<QPoint>::iterator it = _points.begin();
    std::list<QPoint>::iterator end = _points.end();


    QPoint a = *it;
    QPoint b;


    for (++it; it != end; ++it) {
      QPoint b = *it;
      paint.drawLine(a, b);
      a = b;
    }

  }

}

void MyPainter::mousePressEvent ( QMouseEvent * e ) {
  QPoint o(e->pos());
  _points.push_back(o);
  update();
}
 
