#include "MainWidget.h"

#include <qstring.h>
#include <qcolordialog.h>
#include <qvalidator.h>
#include "CodeValidator.h"

MainWidget::MainWidget() {

  this->setGeometry(10,10,300,350);

  int initialFontSize = 12;

  _label = new QLabel("Widgets, signaux, slots, couleurs, fontes", this);
  _label->setGeometry(10,10,280,40);
  _label->setFont(QFont("Arial", initialFontSize, QFont::Normal));


  _rwTextInput = new QLineEdit("",this);
  _rwTextInput->setGeometry(50,70,200,30);
  _rwTextInput->setAlignment(Qt::AlignLeft);

  // expression régulière correspondant à la validation simple
  //QRegExp rx("\\d|\\w*");
  QValidator * vd = new CodeValidator(this);
  _rwTextInput->setValidator(vd);

  _roTextInput = new QLineEdit("",this);
  _roTextInput->setGeometry(50,110,200,30);
  _roTextInput->setAlignment(Qt::AlignLeft);
  _roTextInput->setReadOnly(true);

  QObject::connect(_rwTextInput, SIGNAL(textChanged(const QString &)),
		   this, SLOT(setText(const QString &)));

  _pushButtonColor = new QPushButton("Couleur",this);
  _pushButtonColor->setGeometry(70,150,160,30);
  QObject::connect(_pushButtonColor, SIGNAL(clicked()), this, SLOT(btColorPressed()));

  _chooseColor = new QComboBox(false, this);
  _chooseColor->setGeometry(90,190,120,30);
  _chooseColor->insertItem(QString("Black"));
  _chooseColor->insertItem(QString("Blue"));
  _chooseColor->insertItem(QString("Green"));
  _chooseColor->insertItem(QString("Red"));
  _chooseColor->insertItem(QString("Yellow"));

  QObject::connect(_chooseColor, SIGNAL(activated(int)), this, SLOT(colorChanged(int)));

  _slider = new QSlider(6, 20, 1,  initialFontSize, Qt::Horizontal, this);
  _slider->setGeometry(60,260,170,20);

  _lcd = new QLCDNumber(2, this);
  _lcd->setGeometry(230, 245, 40, 40);
  _lcd->display(initialFontSize);
  QObject::connect(_slider, SIGNAL(valueChanged(int)),
		   _lcd, SLOT(display(int)));


  QObject::connect(_slider, SIGNAL(valueChanged(int)),
		   this, SLOT(fontSizeChanged(int)));


  _pushButtonQuit = new QPushButton("Quitter",this);
  _pushButtonQuit->setGeometry(100,290,80,30);
   
  QObject::connect(_pushButtonQuit,SIGNAL(clicked()),
		   this,SLOT(quitPressed()));

  // QObject::connect(_pushButtonColor,SIGNAL(clicked()),
  //		   colorWidget,SLOT(changeColor()));

  //QObject::connect(colorWidget,SIGNAL(colorChanged(int,int,int)),
  //		   this,SLOT(colorChanged(int,int,int)));


}

void MainWidget::quitPressed() {
  emit askForQuit();
}



void MainWidget::setText(const QString & s) {
  _roTextInput->setText(s.upper());
}

void MainWidget::fontSizeChanged(int fontSize) {
  _roTextInput->setFont(QFont("Arial", fontSize ,QFont::Normal));
}

void MainWidget::colorChanged(int colorIndex) {
  QColor c;
  switch(colorIndex) {
  case 0:
    c = Qt::black;
    break;
  case 1:
    c = Qt::blue; 
    break;
  case 2:
    c = Qt::green;
    break;
  case 3:
    c = Qt::red;
    break;
  case 4:
    c = Qt::yellow;
    break;
  default:
    c = Qt::black;
  }

  _currentColor = c;
  _roTextInput->setPaletteForegroundColor(c);
}

void MainWidget::btColorPressed() {
  QColor c =  QColorDialog::getColor(_currentColor);
  if (c.isValid()) {
    _currentColor = c;
    _roTextInput->setPaletteForegroundColor(c);
  }
}
