#include "ColorWidget.h"



ColorWidget::ColorWidget(QWidget * parent):QWidget(parent)
{
  setBackgroundMode(NoBackground);
  theColor = new QColor(10,20,30);
}

void ColorWidget::paintEvent(QPaintEvent * )
{
  QPainter painter(this);
  // painter.fillRect(2,2,10,10,QBrush(QColor(10,20,30)));
  painter.fillRect(rect(),QBrush(*theColor));
}

void ColorWidget::changeColor()
{
  int r = rand()%255;
  int g = rand()%255;
  int b = rand()%255;

  theColor->setRgb(r,g,b);
  paintEvent(0);
  emit colorChanged(r,g,b);
}
