#ifndef CODEVALIDATOR_H
#define CODEVALIDATOR_H

#include <qvalidator.h>

class CodeValidator : public QRegExpValidator {
  
 public:

  CodeValidator(QObject * parent, const char * name = 0);

  QValidator::State validate(QString & input, int & pos);

};



#endif /* CODEVALIDATOR_H */
