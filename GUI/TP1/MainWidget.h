/**
 * @file   MainWidget.h
 * @author Sebastien Fourey
 * @date   Jan 3 2005
 * 
 * @brief  Classe Widget principal de l'application
 * 
 */

#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <iostream>
using namespace std;

#include "ColorWidget.h"

/**
 * Classe du widget de la fenetre principale
 * de l'application.
 */
class MainWidget : public QWidget {

  // Pour indiquer a "moc" que cette classe
  // possede des signaux et des slots.
  Q_OBJECT


public:
   MainWidget();

signals:
   void askForQuit();

public slots:
  void quitPressed();
  void colorChanged(int r, int g, int b);

protected:
  void mouseMoveEvent(QMouseEvent * e);
  void mousePressEvent(QMouseEvent * e);
  void mouseReleaseEvent(QMouseEvent * e);

private:
  QLabel *label;
  QPushButton *pushButtonQuit, *pushButtonRandomColor;
  QLineEdit  *lineDisplay;
  QLineEdit  *lineDisplay2;
  ColorWidget * colorWidget;
  bool displayPosition;
};

#endif
