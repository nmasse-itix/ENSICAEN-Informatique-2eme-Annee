/** 
 * #(@)HollowMatrix.cpp                  ENSICAEN                       2006
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
 * Implements a hollow matrix.
 */

#include "HollowMatrix.h"

#include <iomanip>

using namespace std;

/*
 * @version	2006
 *
 * @done	-
 *
 * @todo	-
 */


double HollowMatrix::operator()(int r, int c) const {
	pair<int, int> p = make_pair<int, int>(r, c);
	double ret = 0;
	
	/* 
	 * Here, we do not use the operator [] because it inserts a default
	 * value in the map if the key cannot be found.
	 *
	 * The function find() does not modify the object.
	 */
	ArrayOf2DPoints::const_iterator i = this->find(p);
	
	if (i != this->end()) {
		ret = i->second;
	}
	
	return ret;
}


void HollowMatrix::setValue(int r, int c, double v) {
	pair<int, int> p = make_pair<int, int>(r, c);
	
	if (v != 0) {
		(*this)[p] = v;
	} else {
		this->erase(p);
	}
}


int HollowMatrix::width(void) const {
	int max = 0;
	
	for (ArrayOf2DPoints::const_iterator i = this->begin(); 
			i != this->end(); ++i) {
		
		/* i->first is the key, i->first.second is the col number */
		int col = i->first.second;

		if (col > max) {
			max = col;
		}
	}

	return max;
}

int HollowMatrix::height(void) const {
	int max = 0;
	
	for (ArrayOf2DPoints::const_iterator i = this->begin(); 
			i != this->end(); ++i) {
		
		/* i->first is the key, i->first.first is the row number */
		int row = i->first.first;

		if (row > max) {
			max = row;
		}
	}

	return max;
}

ostream & operator<<(ostream & st, const HollowMatrix & m) {
	int h = m.height();
	int w = m.width();

	/* backup stream options */
	ios_base::fmtflags old_options = st.flags();

	/* left alignment */
	st.setf(ios_base::left, ios_base::adjustfield);
	
	st << "[";
	for (int r = 1; r <= h; r++) {
		if (r == 1) {
			st << "[";
		} else {
			st << " [";
		}
		
		for (int c = 1; c <= w; c++) {
			/* the next field is 8 chars wide */
			st << setw(8);
			
			st << m(r, c);
		}
		
		st << "]";
		
		if (r != h) {
			st << endl;
		}
	}
	
	st << "]" << endl;

	/* restore stream options */
	st.flags(old_options);
	
	return st;
}

