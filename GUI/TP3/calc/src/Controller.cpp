/* -*- c-basic-offset: 3 -*-
 * Controller.cpp                          GREYC Image 2004-3-12
 *
 * @author Sebastien Fourey <fourey@greyc.ismra.fr>
 *
 * GREYC Image - ENSICAEN
 * 6, Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 */
#include "Controller.h"



Controller::Controller() {
  text = "0";
  operation = 0;
  newNumber = true;
}

bool
Controller::command(ButtonID n)
{
  switch (n) { 
  case Button_0:
  case Button_1:
  case Button_2:
  case Button_3:
  case Button_4:
  case Button_5:
  case Button_6:
  case Button_7:
  case Button_8:
  case Button_9:
     return addChar('0' + static_cast<char>( n ));
     
  case Button_Dot:
     return addChar('.');
     
  case Button_Plus:
  case Button_Minus:
  case Button_Multiply:
  case Button_Divide:
     if (!newNumber) achieveEqual();
     memory = text.toDouble();
     operation = n;
     newNumber = true;
     return true;

  case Button_C:
     text = "0";
     newNumber = true;
     operation = 0;
     return true;

  case Button_Equal:
     return achieveEqual();
  }
  return false;
}

bool
Controller::achieveEqual()
{
   double operande = 0;
   double result = 0;
   if (!operation) return false;

   operande = text.toDouble();

   switch (operation) { 
   case Button_Plus:
      result = memory + operande;
      break;
   case Button_Minus:
      result = memory - operande;
      break;
   case Button_Divide:
      result = memory / operande;
      break;
   case Button_Multiply:
      result = memory * operande;
      break;
   }   
   
   text = QString("%1").arg(result,0,'f');
   newNumber = true;
   operation = 0;
   return true;
}

bool
Controller::addChar(char c)
{

   if (c == '.' && text.contains('.') ) return false;
   
   if ( text == "0" && c == '0') return false ;
   
   if ( ((text == "0") || newNumber) && c != '0' && c != '.') {
      text = c;
      newNumber = false;
      return true;
   }
   
   if (newNumber) {
      text = "";
   }
   text += c;
   newNumber = false;
   return true;
}

QString
Controller::getText() const {
   return text;
}
