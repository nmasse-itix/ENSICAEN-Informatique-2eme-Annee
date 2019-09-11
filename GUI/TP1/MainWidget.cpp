#include "MainWidget.h"

MainWidget::MainWidget() {

  setGeometry(100,100,300,300);

  label = new QLabel("Colors, signals, and slots",this);
  label->setGeometry(10,10,290,30);
  label->setFont(QFont("Arial",14,QFont::Bold));

  lineDisplay = new QLineEdit("",this);
  lineDisplay->setGeometry(50,110,200,30);
  lineDisplay->setAlignment(Qt::AlignHCenter);
  lineDisplay->setReadOnly(true);

  lineDisplay2 = new QLineEdit("Mon Super Widget",this);
  lineDisplay2->setGeometry(50,70,200,30);
  lineDisplay2->setAlignment(Qt::AlignHCenter);
  lineDisplay2->setReadOnly(true);
  
  colorWidget = new ColorWidget(this);
  colorWidget->setGeometry(100,160,80,30);

  pushButtonRandomColor = new QPushButton("Random color",this);
  pushButtonRandomColor->setGeometry(60,200,160,30);

  pushButtonQuit = new QPushButton("Quitter",this);
  pushButtonQuit->setGeometry(100,250,80,30);
   
  QObject::connect(pushButtonQuit,SIGNAL(clicked()),
		   this,SLOT(quitPressed()));

  QObject::connect(pushButtonRandomColor,SIGNAL(clicked()),
		   colorWidget,SLOT(changeColor()));

  QObject::connect(colorWidget,SIGNAL(colorChanged(int,int,int)),
		   this,SLOT(colorChanged(int,int,int)));

  
  
//  setMouseTracking(true);
  setCaption("pouet");
  
  displayPosition = false;
}

void MainWidget::quitPressed()
{
  emit askForQuit();
}

void MainWidget::colorChanged(int r, int g, int b)
{
  char texte[255];
  sprintf(texte,"Color: R(%d) G(%d) B(%d)",r,g,b);
  lineDisplay->setText(texte);
}

void MainWidget::mouseMoveEvent(QMouseEvent * e) {
  if (displayPosition) {
	  char texte[255];
	  sprintf(texte,"(%d, %d)",e->x(), e->y());
	  lineDisplay2->setText(texte);
  }
}


void MainWidget::mousePressEvent(QMouseEvent * e) {
	displayPosition = true;
	
	switch (e->button()) {
	case Qt::LeftButton:
		lineDisplay2->setAlignment(Qt::AlignLeft);
		break;
	case Qt::RightButton:
		lineDisplay2->setAlignment(Qt::AlignRight);
		break;
	case Qt::MidButton:
		lineDisplay2->setAlignment(Qt::AlignHCenter);
		break;
	default:
		break;
	}
}

void MainWidget::mouseReleaseEvent(QMouseEvent * e) {
	displayPosition = false;
}

