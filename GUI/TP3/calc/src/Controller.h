/* -*- c-basic-offset: 3 -*-
 * Controller.h                          GREYC Image 2004-3-12
 *
 * @author Sebastien Fourey <fourey@greyc.ismra.fr>
 *
 * GREYC Image - ENSICAEN
 * 6, Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <qstring.h>
#include <stdio.h>
#include <iostream>
using namespace std;

enum ButtonID  { Button_0 = 0, 
		 Button_1,
		 Button_2,
		 Button_3,
		 Button_4,
		 Button_5,
		 Button_6,
		 Button_7,
		 Button_8,
		 Button_9,
		 Button_Dot,
		 Button_Plus,
		 Button_Minus,
		 Button_Divide,
		 Button_Multiply,
		 Button_Equal,
		 Button_C };
		   
class Controller  {
 public:
   Controller();

   /** 
    * Effectue une operation.
    * 
    * @param c Le code de l'operation. (ButtonID)
    * @return true si le texte a ete modifie, false sinon.
    */
   bool command(ButtonID c);
   
   /** 
    * Permet de consulter le texte courant de l'affichage.
    *
    * @return Le texte courant de l'affichage.
    */
   QString getText() const;

 private:
   
   /** 
    * Ajoute un caractere a l'affichage.
    *
    * @param c Le caractere a ajouter. 
    * @return true si l'affichage a ete modifie, false sinon (par exemple
    *         si c est un pointet que le texte en contient deja un). 
    */
   bool addChar(char c);

   /** 
    * Effectue une operation en attente de la seconde operande.
    *
    * @return true si une operation etait effectivement en attente, 
    *         false sinon.
    */
   bool achieveEqual();
   
   QString text;		/* Le texte de l'affichage */
   double memory;		/* La premiere operande d'une operation en attente */
   char operation;		/* Code d'une operation en attente */
   bool newNumber;		/* Drapeau marquant le debut de la saisie d'un nouveau nombre */
};

#endif
