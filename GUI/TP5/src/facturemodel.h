/**
 * #(@)facturemodel.h             ENSICAEN                       2005
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
 * @version     0.0.1
 *
 * @done        -
 *
 * @todo        -
 */

#ifndef FACTUREMODEL_H
#define FACTUREMODEL_H

#include <qobject.h>
#include <qstring.h>
#include <qtable.h>

#include "factureimpl.h"
class FactureImpl;

#define NUM_LIGNES_DANS_FACTURE 15

/**
 * Le modèle du MVC.
 * 
 * @author Nicolas MASSÉ <nicolas27.masse@laposte.net>
 */
class FactureModel : public QObject {
    Q_OBJECT

signals:
    /**
     * Emit lorsque le modèle à changé.
     */
    void factureChanged();

public:
    FactureModel(FactureImpl * facture, QObject * parent = 0, const char * name = 0);

    ~FactureModel();

    const QString & nom() const;
    const QString & prenom() const;
    const QString & adresse1() const;
    const QString & adresse2() const;
    const QString & codePostal() const;
    const QString & ville() const;
    const QString & cellule(int row, int col) const;

public slots:
    void setNom(const QString& theValue);
    void setPrenom(const QString& theValue);
    void setAdresse1(const QString& theValue);
    void setAdresse2(const QString& theValue);
    void setCodePostal(const QString& theValue);
    void setVille(const QString& theValue);
    void celluleChangee(int row, int col);

private:
    void notify();
    
    QString _nom;
    QString _prenom;
    QString _adresse1;
    QString _adresse2;
    QString _codePostal;
    QString _ville;
    FactureImpl * _ui;
    QString _table[NUM_LIGNES_DANS_FACTURE][5];
};

#endif
