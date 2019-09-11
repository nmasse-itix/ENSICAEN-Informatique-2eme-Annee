/**
 * #(@)factureview.cpp             ENSICAEN                       2005
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

#include "factureview.h"

FactureView::FactureView(QWidget* parent, const char* name, WFlags fl)
  : QWidget(parent, name, fl), _model(0) {
}


FactureView::~FactureView() {}

void FactureView::setModel(FactureModel * model) {
    // on déconnecte l'ancien modèle
    if (this->_model != 0) {
        disconnect(this->_model, SIGNAL(factureChanged()),
                   this, SLOT(updateFacture()));
        this->_model = 0;
    }

    // et on connecte le nouveau
    this->_model = model;
    connect(this->_model, SIGNAL(factureChanged()),
            this, SLOT(updateFacture()));

    // on recalcule l'aperçu
    this->updateFacture();
}

void FactureView::updateFacture() {
    this->repaint();
}

void FactureView::drawFacture(QPainter & painter) {
    QRect bounds = painter.window();
    QFont font(painter.font());
    
    painter.fillRect(bounds, QColor(255, 255, 255));
    
    if (this->_model) {
        this->drawHeader(painter);
        painter.setFont(font);
        this->drawTable(painter);
    }
    
} 

void FactureView::drawHeader(QPainter & painter) {
    QRect bounds = painter.window();
    QFont font(painter.font());
    int w = bounds.width();
    int h = bounds.height();
    
    painter.setBrush(QColor(220, 220, 220));
    font.setPointSize(int(0.02 * h));
    QFontMetrics fm(font);
    
    QString nom_prenom = _model->nom() + " " + _model->prenom();
    QString cp_ville = _model->codePostal() + " " + _model->ville();
    
    int max = 0;
    int tmp = 0;
    
    tmp = fm.width(nom_prenom);
    if (tmp > max) {
        max = tmp;
    }
    tmp = fm.width(_model->adresse1());
    if (tmp > max) {
        max = tmp;
    }
    tmp = fm.width(_model->adresse2());
    if (tmp > max) {
        max = tmp;
    }
    tmp = fm.width(cp_ville);
    if (tmp > max) {
        max = tmp;
    }
    
    painter.drawRoundRect (int(0.05 * w), int(0.02 * h), int(max + 0.08 * w), int(0.15 * h), 15 , 35);
    painter.setFont(font);
    painter.drawText(int(0.08 * w), int(0.055 * h), nom_prenom);
    painter.drawText(int(0.08 * w), int(0.085 * h), _model->adresse1());
    painter.drawText(int(0.08 * w), int(0.115 * h), _model->adresse2());
    painter.drawText(int(0.08 * w), int(0.145 * h), cp_ville);
}

void FactureView::drawTable(QPainter & painter) {
    QRect bounds = painter.window();
    QFont font(painter.font());
    int w = bounds.width();
    int h = bounds.height();
    
    int top = int(0.2 * h);
    int left = int(0.05 * w);
    int right = int(0.95 * w);
    int bottom = int(0.8 * h);
    int height = bottom - top;
    int width = right - left;
    int cwidth = int(0.15 * w);
    int s3 = right - cwidth;
    int s2 = s3 - cwidth;
    int s1 = s2 - cwidth;
    int lheight = int(0.04 * h);
    int hs1 = top + lheight;
    
    painter.setBrush(QColor(200, 200, 200));
    
    painter.drawRect(left, top, width, height);
    painter.drawLine(s1, top, s1, bottom);
    painter.drawLine(s2, top, s2, bottom);
    painter.drawLine(s3, top, s3, bottom);
    painter.drawLine(left, hs1, right, hs1);
    
    painter.drawRect(s3, bottom + lheight, cwidth, lheight);
    painter.drawRect(s3, bottom + 3 * lheight, cwidth, lheight);

    
    font.setPixelSize(lheight / 3);
    painter.setFont(font);
    
    this->drawTableLine(painter, 0, "Produit", "Quantite", "Unite (H.T.)", "Prix H.T.");
    for (int i = 0; i < NUM_LIGNES_DANS_FACTURE; ++i) {
        this->drawTableLine(painter, i + 1, _model->cellule(i, 1), 
                            _model->cellule(i, 2), 
                            _model->cellule(i, 3), 
                            _model->cellule(i, 4));
        
    }
}

void FactureView::drawTableLine(QPainter & painter, int n, const QString & p, const QString & q, const QString & u, const QString & m) {
    QRect bounds = painter.window();
    QFont font(painter.font());
    int w = bounds.width();
    int h = bounds.height();
    
    int top = int(0.2 * h);
    int left = int(0.05 * w);
    int right = int(0.95 * w);
    int cwidth = int(0.15 * w);
    int s3 = right - cwidth;
    int s2 = s3 - cwidth;
    int s1 = s2 - cwidth;
    int lheight = int(0.04 * h);
    
    int y = top + lheight + int((lheight * n) / 1.5);
    
    painter.drawText(int(left + 0.01 * w), int(y - lheight / 3), p);
    painter.drawText(int(s1 + 0.01 * w), int(y - lheight / 3), q);
    painter.drawText(int(s2 + 0.01 * w), int(y - lheight / 3), u);
    painter.drawText(int(s3 + 0.01 * w), int(y - lheight / 3), m);
}

void FactureView::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    this->drawFacture(painter);
}
