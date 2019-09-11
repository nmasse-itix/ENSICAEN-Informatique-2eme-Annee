/**
 * #(@)factureimpl.h             ENSICAEN                       2005
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


#ifndef FACTUREIMPL_H
#define FACTUREIMPL_H

#include "facture.h"

#include "facturemodel.h"
class FactureModel;

/**
 * Cette classe dérive de la classe d'interface graphique créée par
 * Qt Designer. Elle implémente les actions liées aux évenements de
 * l'interface graphique.
 */
class FactureImpl : public Facture {
    Q_OBJECT

public:
    FactureImpl(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~FactureImpl();
    /*$PUBLIC_FUNCTIONS$*/

public slots:
    /*$PUBLIC_SLOTS$*/
    virtual void          helpAbout();
    virtual void          fileExit();
    virtual void          filePrint();
    virtual void          fileSaveAs();
    virtual void editClearAll();
    virtual void          fileSave();
    virtual void          fileOpen();
    virtual void          fileNew();

protected:
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    virtual void nomChanged(const QString & s);
    virtual void prenomChanged(const QString & s);
    virtual void adresse1Changed(const QString & s);
    virtual void adresse2Changed(const QString & s);
    virtual void cpChanged(const QString & s);
    virtual void villeChanged(const QString & s);
    virtual void tableChanged(int row, int col);

protected slots:
    /*$PROTECTED_SLOTS$*/

private:
    /**
     * Le modèle du MVC
     */
    FactureModel * _model;
};

#endif

