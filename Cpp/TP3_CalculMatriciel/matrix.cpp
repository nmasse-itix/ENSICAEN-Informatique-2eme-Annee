/**
 * #(@)matrix.cpp              ENSICAEN                       2005-10-15
 *
 * @author MASSE Nicolas (2005-Groupe4-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe4-MASSE) <thomas.limin@laposte.net>
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

#include "matrix.h"

Matrix::Matrix(unsigned int line_nb, unsigned int col_nb) {
  // store dimensions
  _line_nb = line_nb;
  _col_nb = col_nb;

  // allocate memory
  _columns = new double[line_nb * col_nb];
  _lines = new double*[line_nb];

  // initialise lines' pointers
  for (unsigned int i = 0; i < line_nb; i++) {
    _lines[i] = _columns + (i * col_nb);
  }
}


Matrix::Matrix(const Matrix & m) {
  // retrieve and copy dimension
  _line_nb = m._line_nb;
  _col_nb = m._col_nb;

  // allocate memory
  _columns = new double[_line_nb * _col_nb];
  _lines = new double*[_line_nb];


    // initialise lines' pointers
    for (unsigned int i = 0; i < _line_nb; i++) {
      _lines[i] = _columns + (i * _col_nb);
    }

  // copy the values from m to this
  double * src = m._columns;
  double * dest = _columns;
  for (unsigned int i = _line_nb * _col_nb; i > 0 ; i--) {
    *(dest++) = *(src++);
  }

}


Matrix::~Matrix() {
  // free the two blocks of memory
  delete[] _lines;
  delete[] _columns;
}


Matrix & Matrix::operator=(const Matrix & m) {
  // check inequality
  if (this != &m) {

    // matrix geometry changed flag
    bool reInitLines = false;

    // check number of coefficients
    unsigned int nbCells = (m._col_nb * m._line_nb);
    if ((_col_nb * _line_nb) != nbCells) {
      // number of "cells" has changed : necessary to reallocate memory
      delete[] _columns;
      _columns = new double[_line_nb * _col_nb];
      reInitLines = true;
    }

    // check number of line:
    if (_line_nb != m._line_nb) {
      // number of line has changed : necessary to reallocate memory
      delete[] _lines;
      _lines = new double*[_line_nb];
      reInitLines = true;
    }

    // store new dimensions
    _line_nb = m._line_nb;
    _col_nb = m._col_nb;

    if (reInitLines) {
      // initialise lines' pointers
        for (unsigned int i = 0; i < _line_nb; i++) {
	_lines[i] = _columns + (i * _col_nb);
      }      
    }

    // copy the values from m to this
    double * src = m._columns;
    double * dest = _columns;
    for (unsigned int i = nbCells; i > 0 ; i--) {
      *(dest++) = *(src++);
    }
  }

  return *this;
}

bool Matrix::operator==(const Matrix & m) const {

  // check dimensions
  if ((_line_nb != m._line_nb) || (_col_nb != m._col_nb)) {
    return false;
  }

  // check coefficients values
  double * c1 = m._columns;
  double * c2 = _columns;
  for (unsigned int i = _line_nb * _col_nb; i > 0 ; i--) {
    if (*(c1++) != *(c2++)) {
      return false;
    }
  }

  return true;
  }


bool Matrix::operator!=(const Matrix & m) const {
    return ! (*this == m);
}


Matrix Matrix::operator+(const Matrix & m) const {
    Matrix mat(*this);
    
    mat += m;
    
    return mat;
}

Matrix & Matrix::operator+=(const Matrix & m) {
    assert(m.getColNb() == this->getColNb());
    assert(m.getLineNb() == this->getLineNb());
    
    for (unsigned int r = 1; r <= this->getLineNb(); r++) {
        for (unsigned int c = 1; c <= this->getColNb(); c++) {
            this->setValueAt(r, c, this->getValueAt(r, c) + m.getValueAt(r, c));
        }
    }
    
    return *this;
}

Matrix Matrix::operator-(const Matrix & m) const {
    Matrix mat(*this);
    
    mat -= m;
    
    return mat;
}

Matrix & Matrix::operator-=(const Matrix & m) {
    assert(m.getColNb() == this->getColNb());
    assert(m.getLineNb() == this->getLineNb());
    
    for (unsigned int r = 1; r <= this->getLineNb(); r++) {
        for (unsigned int c = 1; c <= this->getColNb(); c++) {
            this->setValueAt(r, c, this->getValueAt(r, c) - m.getValueAt(r, c));
        }
    }
    
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix tmp(this->getLineNb(), this->getColNb());
    
    for (unsigned int r = 1; r <= this->getLineNb(); r++) {
        for (unsigned int c = 1; c <= this->getColNb(); c++) {
            tmp.setValueAt(r, c, - this->getValueAt(r, c));
        }
    }
    
    return tmp;
}

Matrix Matrix::transpose() const {
    Matrix mat(this->getColNb(), this->getLineNb());
    
    for (unsigned int r = 1; r <= this->getLineNb(); r++) {
        for (unsigned int c = 1; c <= this->getColNb(); c++) {
            mat.setValueAt(c, r, this->getValueAt(r, c));
        }
    }
    
    return mat;
}

Matrix Matrix::invertR() const {
    assert(this->getColNb() == this->getLineNb() && isPowerOfTwo(this->getColNb(), 0));
    
    if (this->getColNb() == 1) {
        Matrix tmp(1, 1);
        tmp.setValueAt(1, 1, 1 / this->getValueAt(1, 1));
        cout << "Résultat temporaire:" << endl << *this << endl << tmp << endl;
        return tmp;
    } else {
        Matrix B = this->getQuarter(1);
        Matrix Ct = this->getQuarter(2);
        Matrix D = this->getQuarter(3);
        Matrix C = this->getQuarter(4);
        
        cout << "quarter B" << endl << B << endl;
        cout << "quarter Ct" << endl << Ct << endl;
        cout << "quarter D" << endl << D << endl;
        cout << "quarter C" << endl << C << endl;
        
        Matrix Bm1 = B.invertR();
        Matrix CBm1T = (C * Bm1).transpose();
        Matrix S = D - C * Bm1 * Ct;  // OK
        Matrix Q3 = S.invertR();
        Matrix & Sm1 = Q3;
        Matrix Sm1CBm1 = (Sm1 * C) * Bm1;
        Matrix Sm1CBm1T = Sm1CBm1.transpose();
        
        Matrix Bm1CTSm1 = (Bm1 * CBm1T) * Sm1;
        Matrix Q2 = -Bm1CTSm1;
        
        Matrix Q4 = - Sm1CBm1;
        
        Matrix Q1 = Bm1 + (CBm1T * Sm1CBm1);
        
        Matrix ret(this->getLineNb(), this->getLineNb());
                
        unsigned int nl1 = Q1.getLineNb();
        unsigned int nc1 = Q1.getColNb();
        for (unsigned int i = 1;  i <= nl1; i ++) {
            for (unsigned int j = 1;  j <= nc1; j ++) {
                ret.setValueAt(i,j, Q1.getValueAt(i, j));
            }
        }
        
        unsigned int nl2 = Q2.getLineNb();
        unsigned int nc2 = Q2.getColNb();
        for (unsigned int i = 1;  i <= nl2; i ++) {
            for (unsigned int j = 1;  j <= nc2; j ++) {
                ret.setValueAt(i, nc1 + j, Q2.getValueAt(i, j));
            }
        }
        
        unsigned int nl3 = Q3.getLineNb();
        unsigned int nc3 = Q3.getColNb();
        for (unsigned int i = 1;  i <= nl3; i ++) {
            for (unsigned int j = 1;  j <= nc3; j ++) {
                ret.setValueAt(nl1 + i, nc1 + j, Q3.getValueAt(i, j));
            }
        }
        
        unsigned int nl4 = Q4.getLineNb();
        unsigned int nc4 = Q4.getColNb();
        for (unsigned int i = 1;  i <= nl4; i ++) {
            for (unsigned int j = 1;  j <= nc4; j ++) {
                ret.setValueAt(nl1 + i, j, Q2.getValueAt(i, j));
            }
        }
        
        cout << "Résultat temporaire:" << endl << *this << endl <<ret << endl;
        
        return ret;
    }
}

Matrix Matrix::invert() const {
  // the Matrix must be a square Matrix
    if (this->getLineNb() != this->getColNb()) {
    // Error, simply return the matrix
        return *this;
    }

  // we provide a positive defined matrix;
    Matrix m(*this);
    Matrix mt = m.transpose();
    Matrix r = mt * m;

    unsigned int size;
    isPowerOfTwo(r.getColNb(), &size);

    Matrix * toBeInverted = &r;
    if (size != toBeInverted->getColNb()) {
    // we must resize the Matrix
        toBeInverted = new Matrix(size, size);
        unsigned int rSize = r.getColNb();
        for (unsigned int i = 1; i <= size; i++) {
            for (unsigned int j = 1; j <= size; j++) {
                double value = 0;

                if (i <= rSize && j <= rSize) {
                    value = r.getValueAt(i, j);
                } else if (i == j) {
                    value = 1;
                }
                toBeInverted->setValueAt(i, j, value);
            }
        }
    }
    
    
    cout << "La matrice qui va être effectivement inversée:" << endl << *toBeInverted << endl;
    
    Matrix invert = toBeInverted->invertR();
    Matrix small(this->getLineNb(), this->getColNb());
    
    // copy the inverted matrix into the source matrix
    int c = this->getColNb();
    int l = this->getLineNb();
  
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= c; j++) {
            small.setValueAt(i, j, invert.getValueAt(i, j));
        }
    }
    
    if (toBeInverted != &r) {
        delete toBeInverted;
    }
    
    return small * mt;
}


Matrix Matrix::getQuarter(int quarter) const {
    unsigned int nbLine = this->getLineNb();
    unsigned int nbCol = this->getColNb();

    Matrix m((nbLine / 2) + (nbLine % 2), (nbCol / 2)  + (nbCol % 2));
    unsigned int lineStart, lineEnd, colStart, colEnd;
    if (quarter == 1) {
    // return up left quarter
        lineStart = 1;
        colStart = 1;
        lineEnd = nbLine / 2;
        colEnd = nbCol / 2;
        if ((nbLine % 2) != 0) {
      // nbLine odd
            lineEnd++;
        }
        if ((nbCol % 2) != 0) {
      // nbCol odd
            colEnd++;
        }
    } else if (quarter == 2) {
    // return up right quarter
        lineStart = 1;
        lineEnd = nbLine / 2;
        colStart = nbCol / 2 + 1;
        colEnd = nbCol;
        if ((nbLine % 2) != 0) {
      // nbLine odd
            lineEnd++;
        }
    } else if (quarter == 3) {
    // return down right quarter
        lineStart = nbLine / 2 + 1;
        lineEnd = nbLine;
        colStart = nbCol / 2 + 1;
        colEnd = nbCol;
    } else if (quarter == 4) {
    // return down left quarter
        lineStart = nbLine / 2 + 1;
        lineEnd = nbLine;
        colStart = 1;
        colEnd = (nbCol /2) + (nbCol %2);
        if ((nbCol % 2) != 0) {
      // nbCol odd
            colEnd++;
        }
    }

    unsigned int im = 1, jm = 1;
    for(unsigned int i = lineStart; i <= lineEnd; i++) {
        for(unsigned int j = colStart; j <= colEnd; j++) {
            m.setValueAt(im, jm, this->getValueAt(i,j));
            jm ++;
        }
        jm = 1;
        im ++;
    }

    return m;
}

Matrix Matrix::operator*(const Matrix & m) const {
    assert(this->getColNb() == m.getLineNb());
    
    Matrix mat(this->getLineNb(), m.getColNb());
    
    for (unsigned int r = 1; r <= mat.getLineNb(); r++) {
        for (unsigned int c = 1; c <= mat.getColNb(); c++) {
            double tmp = 0;
            
            for (unsigned int i = 1; i <= this->getColNb(); i++) {
                //cout << r << " " << c << " " << i << endl;
                tmp += this->getValueAt(r, i) * m.getValueAt(i, c);
            }
            
            mat.setValueAt(r, c, tmp);
        }
    }
    
    return mat;
}


ostream & operator<<(ostream & os, const Matrix & m) {
    unsigned int nbLine = m.getLineNb();
    unsigned int nbCol = m.getColNb();

  // write values, line by line
    for (unsigned int i = 1; i <= nbLine; i++) {
        if (i == 1) {
            os << "[";
        } else {
            os << " ";
        }
        
        for (unsigned int j = 1; j <= nbCol; j++) {
            os << m.getValueAt(i, j) << " ";
        }
        
        if (i == nbLine) {
            os << "]";
        }
        
        os << endl;
    }

    return os;
}


istream & operator>>(istream & is, Matrix ** m) {
  // write number of line and column
    unsigned int nbLine;
    unsigned int nbCol;

    is >> nbLine;
    is >> nbCol;

    *m = new Matrix(nbLine, nbCol);

  // write values, line by line
    for (unsigned int i = 1; i <= nbLine; i++) {
        for (unsigned int j = 1; j <= nbCol; j++) {
            double val;
            
            is >> val;
            (*m)->setValueAt(i, j, val);
        }
    }

    return is;
}

bool isPowerOfTwo(unsigned int n, unsigned int * max) {
    unsigned int shifted = 0x80000000;
    bool power = true;
    int nb = sizeof(shifted) * 8;
    
    // Find a bit
    while ((shifted & n) == 0 && nb != 0) {
        shifted >>= 1;
        nb--;
    }
    
    // Is it the only one ?
    if ((shifted & n) != n) {
        power = false;
        if (max != 0) {
            *max = shifted << 1;
        }
    } else if (max != 0) {
        *max = n;
    }
    
    return power;
}
