/**
 * @file   ColorWidget.h
 * @author Sebastien Fourey
 * @date   Mon Jan 3 2005
 * 
 * @brief  Classe implementant un Widget qui se remplit
 * avec une couleur de fond et change celle-ci de maniere
 * aleatoire lorsque qu'un slot (une methode) est appelee.
 * 
 */
           
#ifndef COLORWIDGET_H
#define COLORWIDGET_H
#include <qwidget.h>
#include <qpen.h>
#include <qcolor.h>
#include <qpainter.h>

/**
 * Widget personnalise qui se remplit d'une couleur
 * et change celle-ci aleatoirement sur demande.
 * 
 */
class ColorWidget : public QWidget {
  // Pour indiquer a "moc" que cette classe
  // possede des signaux et des slots.
  Q_OBJECT

public:
  
  ColorWidget():theColor(0) { }
  ColorWidget(QWidget *);
  ~ColorWidget() { delete theColor; }
  
protected:
  /** 
   * Implemente la reponse du Widget aux
   * evenement de rafraichissement.
   * @param e L'evenement recu.
   */
  void paintEvent(QPaintEvent*);
  
public slots: 
  
    /** 
     * Slot declanchant le changement de la couleur
     * par tirage aleatoire.
     */
    void changeColor();
  
signals: 
  
  /** 
   * Signal emit lorsque la couleur a ete changee.
   * 
   * @param int Composante rouge.
   * @param int Composant verte.
   * @param int Composante bleue.
   */
  void colorChanged(int r, int g, int b);
private:
  QColor * theColor;
};

#endif

   
