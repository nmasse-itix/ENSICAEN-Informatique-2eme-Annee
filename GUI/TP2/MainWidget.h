
#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qslider.h>
#include <qlcdnumber.h>
#include <iostream>

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
   void setText(const QString & s);
   void fontSizeChanged(int fontSize);
   void colorChanged(int colorIndex);
   void btColorPressed();
  

private:

  QLabel * _label;
  QLineEdit  * _rwTextInput;
  QLineEdit  * _roTextInput;
  QPushButton * _pushButtonColor;
  QPushButton * _pushButtonQuit;
  QComboBox * _chooseColor;
  QSlider * _slider;
  QLCDNumber * _lcd;
  QColor _currentColor;
};

#endif
