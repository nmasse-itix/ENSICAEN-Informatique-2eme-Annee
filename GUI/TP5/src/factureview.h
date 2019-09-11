/** 
 * #(@)factureview.h             ENSICAEN                       2005
 *
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/*
 * @version	0.0.1
 *
 * @done	-
 *
 * @todo	-
 */

#ifndef FACTUREVIEW_H
#define FACTUREVIEW_H

#include "facturemodel.h"

#include <qwidget.h>
#include <qtextedit.h>
#include <qpainter.h>


/**
 * Cette classe est une vue du MVC.
 * 
 * @author Nicolas MASSÉ <nicolas27.masse@laposte.net>
 */
class FactureView : public QWidget {

    Q_OBJECT
            
public:
    FactureView(QWidget* parent = 0, 
                const char* name = 0, WFlags fl = 0);

    ~FactureView();
    
    /**
     * Définit le modèle du MVC.
     */
    void setModel(FactureModel * model);
    
    /**
     * Méthode appelée par Qt afin de rafraichir.
     */
    virtual void paintEvent(QPaintEvent *);
    
public slots:
    /**
     * Mets à jour l'aperçu de la facture.
     */
    void updateFacture();
    
private:
    void drawFacture(QPainter & painter);
    void drawHeader(QPainter & painter);
    void drawTable(QPainter & painter);
    void drawTableLine(QPainter & painter, int n, const QString & p, const QString & q, const QString & u, const QString & h);
    FactureModel * _model;
};

#endif
