#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <list>
#include <vector>

/**
   This class implements a polynomial of the form
    c0 + c1 x + c2 x^2 + c3 x^3 + ...

   (The order of a polynomial is the largest
   power of x having a non-zero coefficient, or zero if the polynomial
   has all zero coefficients.) Note that adding polynomials
   together or scaling polynomials (multiplying by a constant) could
   reduce the order of the result.

*/
class PolynomialTests;

class Polynomial {
public:
  /**
   * Create a zero polynomial.
   */
  Polynomial ();

  /**
   * Create a polynomial with the given coefficients.
   * E.g.,
   *   double c[3] = {1.0, 2.0, 3.0};
   *   Polynomial p (3, c);
   * creates a polynomial p representing: 1.0 + 2.0*x + 3.0*x^2
   *
   * @param nCoeff number of coefficients in the input array
   * @param coeff  the coefficients of the new polynomial, starting
   *               with power 0.
   */
  Polynomial (int nCoeff, double coeff[]);

  /**
   * Create a polynomial with the given coefficients. If
   * the coeff vector is empty, create a zero polynomial.
   *
   * @param coeff  the coefficients of the new polynomial, with
   *               coeff[0] denoting the term of power 0.
   */
  Polynomial (const std::vector<double>& coeff);


  // Don't need our own Big 3 because none of the data members are pointers
  // Polynomial (const Polynomial&);
  // ~Polynomial();
  // Polynomial& operator= (const Polynomial&);

  /**
   * Compute the value of this polynomial at a given value of x.
   * E.g.,
   *   double c[3] = {1.0, 2.0, 3.0};
   *   Polynomial p (3, c);
   *   cout << p.evaluate(2.0);
   * will print 17.0
   *
   * @param x the value on which this polynomial should be evaluated.
   * @return the value of this polynomial at x
   */
  double evaluate (double x) const;

  /**
   * Get the coefficient of the term with the indicated power.
   * @param power the power of a term
   * @return the corresponding coefficient, or zero if power < 0 or if
   *          power > getDegree()
   */
  double getCoeff(int power) const;

  /**
   *  The degree of a polynomial is the largest exponent of x with a
   *  non-zero coefficient. E.g.,
   *     x^3 + 2x + 1  has degree 3
   *     42            has degree 0   (42 == 42 * x^0)
   *     0             is a special case and is regarded as degree -1
   *
   * @return the degree of this polynomial
   */
  int getDegree() const;

  /**
   * The number of terms that do not have a zero coefficient.
   * @return the number of non-zero terms
   */
  int getNumberOfNonzeroTerms() const
  {
	  return terms.size();
  }

  /**
   * Add a polynomial to this one, returning their sum.
   *
   * @param p another polynomial
   * @return the sum of the two polynomials
   */
  Polynomial operator+ (const Polynomial& p) const;

  /**
   * Multiply this polynomial by a scalar.
   * @param scale the value by which to multiply each term in this polynomial
   * @return the polynomial resulting from this multiplication
   */
  Polynomial operator* (double scale) const;

  /**
   * Compare this polynomial for equality against another.
   *
   * @param p another polynomial
   * @return true iff the polynomials have the same degree and their corresponding
   *           coefficients are equal.
   */
  bool operator== (const Polynomial& p) const;

private:

  /**
   * A representation of a single term of the form
   *   coeff * (x ^ power).
   */
  struct Term {
	  double coeff;
	  int power;

	  Term (double c, int pow)
	  : coeff(c), power(pow)
	  {}

	  bool operator== (const Term& t) const;
  };

  std::list<Term> terms;

  friend std::ostream& operator<< (std::ostream& out, const Polynomial& p);


};

/**
 * Read a polynomial from an istream.
 *   Polynomials are input in the format:
 *    #coefficients c0 c1 ...
 *   where the ci are floating point coefficients of x^i
 *
 *   @param in the stream from which to read the polynomial
 *   @param p the polynomial in which to store the result.
 *   @return the stream in
 */
std::istream& operator>> (std::istream& in, Polynomial& p);

/**
 *  Write a polynomial to an ostream
 *
 *   @param out the stream to which to write the polynomial
 *   @param p the polynomial to write
 *   @return the stream out
 */
std::ostream& operator<< (std::ostream&, const Polynomial&);

/**
 * Note: a member function of the Polynomial class must have a polynomial
 * as the first argument (e.g., poly.operator*(x) <===> poly * x). This
 * function simply allows for the multiplication to be written with the
 * polynomial on the right.
 *
 * @param scale the value to multiply the polynomial by
 * @param p a polynomial
 * @return the product of scale and p
 */
inline
Polynomial operator* (double scale, const Polynomial& p)
{ return p * scale; }


#endif
