/**
* #(@)Matrix.h              ENSICAEN                       2005-10-12
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

/**
 * Objectifs du TP: allocation dynamique, copie et destruction des objets,
 * surcharge d'operateurs, programmation d'une classe concrète, CHoix entre
 * fonctions membres, non-membres, 
 */

/*
 * @version	0.0.1
 *
 * @done:  nothing
 *
 * @todo: all
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cassert>
#include <iostream>

using namespace std;

/**
 * A class wich implements the mathematical concept of Matrix
 */
class Matrix {

public:

    /**
     * Default constructor. The caller has to provide the
     * size of the future matrix.
     *
     * @param line_nb	number of line, default 2
     * @param col_nb	number of column, default 2
     */
    Matrix(unsigned int line_nb = 2, unsigned int col_nb = 2);

    /**
     * Clone constructor
     *
     * @param m	original matrix
     */
    Matrix(const Matrix & m);

    /**
     * Matrix destructor. Free memory that is used to store
     * the coeficient.
     */
    ~Matrix();

    /**
     * Assignment operator.
     *
     * @param m		original matrix
     * @retun		a reference on the matrix' copy
     */
    Matrix & operator=(const Matrix & m);

    /**
     * Equality check operator.
     *
     * @param m		second matrix
     * @retun		true if the matrices are identical, else false
     */
    bool operator==(const Matrix & m) const;

    /**
     * Inequality check operator.
     *
     * @param m		second matrix
     * @retun		true if the matrices are different, else true
     */
    bool operator!=(const Matrix & m) const;

    /**
     * Addition operator.
     * 
     * @param m         second matrix
     * @return          the addition of the two matrix
     */
    Matrix operator+(const Matrix & m) const;

    /**
     * Addition and affectation operator.
     * 
     * @param m         second matrix
     * @return          a reference to this
     */
    Matrix & operator+=(const Matrix & m);

    /**
     * Minus operator.
     * 
     * @param m         second matrix
     * @return          the difference between the two matrix
     */
    Matrix operator-(const Matrix & m) const;

    /**
     * Minus and affectation operator.
     * 
     * @param m         second matrix
     * @return          a reference to this
     */
    Matrix & operator-=(const Matrix & m);

    /**
     * Unary minus operator.
     * 
     * @return          a new matrix
     */
    Matrix operator-() const;
    
    /**
     * Transposes this matrix.
     * 
     * @return          a new transposed matrix.
     */
    Matrix transpose() const;
    
    /**
     * Invert the Matrix. This is the entry point for the recursive
     * inversion process. It init the matrix so it will be inversible
     *
     * @return	a new matrix, inverted
     */
    Matrix invert() const;

    /**
     * Multiply operator.
     * 
     * @param m         the second matrix.
     * @return          the result.
     */
    Matrix operator*(const Matrix & m) const;
    
    /**
     * Return a pointer linked to the previous element of the first element
     * of the row, so that the notation m[row][col] works (with row in [1,n]
     * and col in [1,n].
     * 
     * @param row       the row number (between 1 and _line_nb).
     * @return          a pointer to the row.
     */
    inline double * operator[](unsigned int row) {
        assert(row > 0 && row <= this->getLineNb());
        
        return _lines[row - 1] - 1;
    }
    
    /**
     * Number of lines getter
     *
     * @return	the number of lines
     */
    inline unsigned int getLineNb() const {
        return _line_nb;
    }

    /**
     * Number of columns getter
     *
     * @return	the number of comumns
     */
    inline unsigned int getColNb() const {
        return _col_nb;
    }
    
    /**
     * Matrix values getter.
     * 
     * @param r     the row number [1,n]
     * @param c     the col number [1,n]
     * @return      the value.
     */
    inline double getValueAt(unsigned int r, unsigned int c) const {
        assert(r > 0 && r <= _line_nb);
        assert(c > 0 && c <= _col_nb);
        return _lines[r - 1][c - 1];
    }
    
    /**
     * Matrix values setter.
     * 
     * @param r     the row number [1,n]
     * @param c     the col number [1,n]
     * @param v     the value.
     */
    inline void setValueAt(unsigned int r, unsigned int c, double v) {
        assert(r > 0 && r <= _line_nb);
        assert(c > 0 && c <= _col_nb);
        _lines[r - 1][c - 1] = v;
    }
    
    /**
     * Create a Matrix which is a copy of a quarter of the current Matrix
     * The returned quarter is:
     *
     * 1 => up left
     * 2 => up right
     * 3 => down right
     * 4 => down left
     *
     * @param quarter   the quarter to return
     * @return          a new Matrix
     */
    Matrix getQuarter(int quarter) const;


private:
    /**
     * Inverts this matrix (recursive)
     * 
     * @return          a new inverted matrix.
     */
    Matrix invertR() const;
    
    /**
     * The number of line of the matrix
     */
    unsigned int _line_nb;

    /**
     * The number of line of the matrix
     */
    unsigned int _col_nb;

    /**
     * An array of pointers, each allowing access to a column
     */
    double ** _lines;

    /**
     * Memory area in wich columns are stored
     */
    double * _columns;

};

/**
 * Write a Matrix to output stream. Following format is used:
 * line_number column number values (line by line)
 *
 * @param os            the output stream
 * @param m             the matrix to write out
 * @return              the output stream
 */
ostream & operator<<(ostream & os, const Matrix & m);

/**
 * Get a Matrix from input stream. Following format is used:
 * line_number column number values (line by line)
 *
 * @param is            the input stream
 * @param m             a pointer on a Matrix pointer. the param is used
 *                      to write out the pointer to the new Matrix
 * @return              the input stream
 */
istream & operator>>(istream & is, Matrix ** m);

/**
 * Tests if n is a power of two. 
 * 
 * @param n             the number to test.
 * @param max           a pointer to store the power of two upper or equal to n
 * @return              true or false.
 */
bool isPowerOfTwo(unsigned int n, unsigned int * max);

#endif /* define __MATRIX_H__ */
