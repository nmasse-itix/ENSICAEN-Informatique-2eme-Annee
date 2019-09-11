
#include "CodeValidator.h"


CodeValidator::CodeValidator(QObject * parent, const char * name)
  : QRegExpValidator(QRegExp("\\d{1,10}[A-Za-z]"), parent, name) {
};

QValidator::State CodeValidator::validate(QString & input, int & pos) {
  QValidator::State st = QRegExpValidator::validate(input, pos);

  if (st != QValidator::Invalid) {
    unsigned int sl = input.length();
    
  }

  return st;

}
