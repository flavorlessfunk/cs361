#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>

#include "polynomial.h"

using namespace std;

int main (int argc, char** argv)
{
  cout << "Enter a polynomial.\nHow many coefficients will be in the first polynomial? " << flush;
  int nCoeff1;
  cin >> nCoeff1;

  cout << "\nEnter the coefficients, in order of increasing power of x:\n  " << flush;

  double coeff1 [nCoeff1];
  for (int i = 0; i < nCoeff1; ++i)
    cin >> coeff1[i];

  Polynomial p1 (nCoeff1, coeff1);

  double x;
  cout << "\nEnter a value at which to evaluate the polynomial: " << flush;
  cin >> x;

  cout << p1 << "\n  at x=" << x << " evaluates to " << setprecision(3) << p1.evaluate(x)
       << endl;


  cout << "\nEnter a second polynomial, in the same format\n(# of coefficients, then each coefficient in order of increasing power of x).\n  " << flush;
  Polynomial p2;
  cin >> p2;

  if (p1 == p2)
  {
	  cout << "Those polynomials are equal." << endl;
  }
  else
  {
	  cout << "Those polynomials are not equal." << endl;
  }

  double scale;
  cout << "\nEnter a scaling factor (a floating point number): " << flush;
  cin >> scale;

  {
    Polynomial p3 = p1 * scale;

    cout << "\n\n(" << p1 << ") * "
	 << scale 
	 << "  = " << p3 << endl;
  }

  {
    Polynomial p4 = p1 + p2;

    cout << "\n\n" << p1 << "\n   +\n"
	 << " (" << p2 << ")\n"
       << "  = " << p4 << endl;
  }

  {
    Polynomial p5 = p1 + scale * p2;

    cout << "\n\n" << p1 << "\n   +\n"
	 << scale << " * (" << p2 << ")\n"
	 << "  = " << p5 << endl;

    cout << "\nThis polynomial has degree " << p5.getDegree()
	 << " and, at x=" << x << ", evaluates to " << setprecision(3) << p5.evaluate(x)
	 << endl;
  }

  return 0;
}

