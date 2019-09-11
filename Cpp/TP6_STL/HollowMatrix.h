/** 
 * #(@)HollowMatrix.h             ENSICAEN                       2006
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

/**
 * Defines a hollow matrix.
 */

#ifndef HOLLOW_MATRIX_H
#define HOLLOW_MATRIX_H

#include <iostream>
#include <map>
#include <string>

/*
 * @version	2006
 *
 * @done	-
 *
 * @todo	-
 */

typedef std::map<std::pair<int, int>, double> ArrayOf2DPoints;

class HollowMatrix : public ArrayOf2DPoints {
public:
	/**
	 * Returns the number at row r and col c. By default, all values in
	 * this matrix are zero.
	 *
	 * @param r	the row number, starting at 1
	 * @param c	the col number, starting at 1
	 * @return	the value, 0 if not defined
	 */
	double operator()(int r, int c) const;

	/**
	 * Defines the number at row r and col c. If v is equal to zero, the 
	 * number is removed from this matrix.
	 * 
	 * @param r	the row number, starting at 1
	 * @param c	the col number, starting at 1
	 * @param v	the value
	 */
	void setValue(int r, int c, double v);

	/**
	 * Returns the number of columns in this matrix.
	 *
	 * @return the number of columns in this matrix
	 */
	int width(void) const;
	
	/**
	 * Returns the number of rows in this matrix.
	 *
	 * @return the number of rows in this matrix
	 */
	int height(void) const;
private:
	
};

std::ostream & operator<<(std::ostream & st, const HollowMatrix & m);

#endif /* HOLLOW_MATRIX_H */
 
