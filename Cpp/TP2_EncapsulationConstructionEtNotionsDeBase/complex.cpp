/**
 * #(@)complex.cpp              ENSICAEN                       2005-02-27
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


#include "complex.h"
#include <cmath>

using namespace std;

Complex::~Complex() {
  cout << "---Complex[" << this << "](";
  this->writeTo(cout);
  cout << ")" << endl;
}

Complex::Complex(double re, double im) : _re(re), _im(im) {
  cout << "+++Complex[" << this << "](" << re << ", " << im << ")" << endl;
}

Complex::Complex(const Complex & cpx) {
  cout << "rrrComplex[" << this << "](";
  cpx.writeTo(cout);
  cout << ")" << endl;
  
  this->setRealPart(cpx.getRealPart());
  this->setImaginaryPart(cpx.getImaginaryPart());
}

double Complex::getRealPart() const {
  return _re;
}
  

double Complex::getImaginaryPart() const {
  return _im;
}

void Complex::setRealPart(double re) {
  _re = re;
}

void Complex::setImaginaryPart(double im) {
  _im = im;
}

double Complex::getMagnitude() const {
  double re = this->getRealPart();
  double im = this->getImaginaryPart();
  
  return std::sqrt((re * re) + (im * im));
}

double Complex::getAngle() const {
  double angle = 0;
  double r = this->getRealPart();
  double i = this->getImaginaryPart();
  
  if (r == 0) {
    if (i > 0) {
	    angle = M_PI_2;
    } else if (i < 0) {
	    angle = - M_PI_2;
    } else {
	    angle = FP_NAN;
    }
  } else if (r > 0) {
    angle = std::atan(i / r);
  } else {
    if (i > 0) {
      angle = M_PI - std::atan(i / r);
    } else {
      angle = - M_PI + std::atan(i / r);
    }
  }
  
  return angle;
}

Complex Complex::rotate(Complex & c, double angle) const {
  Complex tmp = (*this) - c;
  Complex tmp2 = tmp * Complex(cos(angle), sin(angle));
  return tmp2 + c;
}

void Complex::writeTo(std::ostream & output) const {
  output << this->getRealPart() << " + i * " << this->getImaginaryPart();
}

Complex Complex::operator+(const Complex & c2) const {
  return sum(*this, c2);
}

Complex Complex::operator-(const Complex & c2) const {
  return ::minus(*this, c2);
}

Complex Complex::operator*(const Complex & c2) const {
  return product(*this, c2);
}

Complex & Complex::operator=(const Complex & c2) {
  cout << "===Complex[" << &c2 << "](";
  c2.writeTo(cout);
  cout << ") >> [" << this << "](";
  this->writeTo(cout);
  cout << ")"<< endl;
  this->setImaginaryPart(c2.getImaginaryPart());
  this->setRealPart(c2.getRealPart());
	
  return *this;
}

void Complex::swapRealAndImaginaryPart() {
  double tmp = this->getImaginaryPart();
  this->setImaginaryPart(this->getRealPart());
  this->setRealPart(tmp);
}

Complex  product(const Complex & cpx1, const Complex & cpx2) {
  double re1 = cpx1.getRealPart();
  double re2 = cpx2.getRealPart();
  double im1 = cpx1.getImaginaryPart();
  double im2 = cpx2.getImaginaryPart();

  return Complex((re1 * re2) - (im1 * im2), (re1 * im2) + (im1 * re2));
}

Complex  sum(const Complex & cpx1, const Complex & cpx2) {
  return Complex(cpx1.getRealPart() + cpx2.getRealPart(),
		     cpx1.getImaginaryPart() + cpx2.getImaginaryPart());
}

Complex  minus(const Complex & cpx1, const Complex & cpx2) {
  return Complex(cpx1.getRealPart() - cpx2.getRealPart(),
		     cpx1.getImaginaryPart() - cpx2.getImaginaryPart());
}

Complex normalize(Complex cpx) {
	cout << "La normalisation a commence" << endl;

	double mag = cpx.getMagnitude();
	double r, i;

	r = cpx.getRealPart() / mag;
	i = cpx.getImaginaryPart() / mag;

	return Complex(r, i);
}

Complex & getMax(Complex & c1, Complex & c2) {
	Complex & max = c2;
	
	if (c1.getMagnitude() > c2.getMagnitude()) {
		max = c1;
	}

	return max;
}

void remplirTableau(int n, Complex * tab) {
	int i;

	for (i = 0; i < n; i++) {
		tab[i] = Complex(i, 0);
	}
}

