/*
 * testPolynomial.cpp
 *
 *  Created on: May 21, 2015
 *      Author: zeil
 */

#include "polynomial.h"

#include <string>
#include <vector>
#include <sstream>

#include <gtest/gtest.h>

namespace {

using namespace std;

// The fixture for testing class MailingList.
class PolynomialTests : public ::testing::Test {
public:
	Polynomial zero;
	std::vector<double> fortyTwo;  // 42
	std::vector<double> parabola;  // 3x^2 - 2 x + 1
	std::vector<double> degreeTen; // x^10 - x^5 + 1

	virtual void SetUp() {
		zero = Polynomial();
		fortyTwo.clear();
		fortyTwo.push_back(42.0);
		parabola.clear();
		parabola.push_back(1.0);
		parabola.push_back(-2.0);
		parabola.push_back(3.0);
		degreeTen.clear();
		degreeTen.resize(11, 0.0);
		degreeTen[0] = 1.0;
		degreeTen[5] = -1;
		degreeTen[10] = 1.0;
	}

	virtual void TearDown() {
	}


	int numberOfTerms (const Polynomial& p) const
	{
		return p.getNumberOfNonzeroTerms();
	}

};

TEST_F (PolynomialTests, defaultConstructor) {
	EXPECT_EQ (-1, zero.getDegree());
	EXPECT_DOUBLE_EQ (0.0, zero.getCoeff(1));
	EXPECT_DOUBLE_EQ (0.0, zero.getCoeff(-1));
	EXPECT_DOUBLE_EQ (0.0, zero.evaluate(100.0));
	EXPECT_EQ (0, numberOfTerms(zero));
}

TEST_F (PolynomialTests, arrayConstructor) {
	double* c = new double[parabola.size()];
	copy (parabola.begin(), parabola.end(), c);
	Polynomial p (parabola.size(), c);
	EXPECT_EQ (2, p.getDegree());
	for (int i = 0; i <= p.getDegree(); ++i)
		EXPECT_DOUBLE_EQ (c[i], p.getCoeff(i));
	EXPECT_DOUBLE_EQ (9.0, p.evaluate(2.0));
	EXPECT_DOUBLE_EQ (2.0, p.evaluate(1.0));
}

TEST_F (PolynomialTests, arrayConstructor2) {
	double* c = new double[parabola.size()+1];
	copy (parabola.begin(), parabola.end(), c);
	c[parabola.size()] = 0.0;
	Polynomial p (parabola.size()+1, c);
	EXPECT_EQ (2, p.getDegree());  // polynomials should be normalized
	EXPECT_EQ (3, numberOfTerms(p));
	for (int i = 0; i <= p.getDegree(); ++i)
		EXPECT_DOUBLE_EQ (c[i], p.getCoeff(i));
	EXPECT_DOUBLE_EQ (9.0, p.evaluate(2.0));
	EXPECT_DOUBLE_EQ (2.0, p.evaluate(1.0));
	delete [] c;
}

TEST_F (PolynomialTests, vectorConstructor) {
	Polynomial p (parabola);
	EXPECT_EQ (2, p.getDegree());
	for (int i = 0; i <= p.getDegree(); ++i)
		EXPECT_DOUBLE_EQ (parabola[i], p.getCoeff(i));
	EXPECT_DOUBLE_EQ (9.0, p.evaluate(2.0));
	EXPECT_DOUBLE_EQ (2.0, p.evaluate(1.0));
}

TEST_F (PolynomialTests, vectorConstructor2) {
	vector<double> c = degreeTen;
	c.push_back(0.0);
	c.push_back(0.0);

	Polynomial p (c);
	EXPECT_EQ (10, p.getDegree());
	EXPECT_EQ (3, numberOfTerms(p));

	for (int i = 0; i <= p.getDegree(); ++i)
		EXPECT_DOUBLE_EQ (c[i], p.getCoeff(i));
	EXPECT_DOUBLE_EQ (1024.0 - 32.0 + 1.0, p.evaluate(2.0));
	EXPECT_DOUBLE_EQ (1.0, p.evaluate(1.0));
}



TEST_F (PolynomialTests, addition) {
	Polynomial p2 (parabola);
	Polynomial p10 (degreeTen);
	EXPECT_EQ (p2, p2 + zero);
	EXPECT_EQ (p10, zero + p10);
	Polynomial p_2_10 = p2 + p10;
	EXPECT_EQ (10, p_2_10.getDegree());
	for (int i = 0; i <= 10; ++i)
	{
		EXPECT_DOUBLE_EQ(p2.getCoeff(i) + p10.getCoeff(i), p_2_10.getCoeff(i));
	}
	EXPECT_FALSE(p_2_10 == p10);
	EXPECT_FALSE(p_2_10 == p2);

	Polynomial p42 (fortyTwo);
	EXPECT_EQ (0, (p42+p42).getDegree());
	EXPECT_EQ (p42, (p42+zero));

}


TEST_F (PolynomialTests, addition2) {
	Polynomial p10 (degreeTen);
	vector<double> c (11, 0.0);
	c[10] = -p10.getCoeff(10);
	Polynomial p(c);

	Polynomial sum = p + p10;

	EXPECT_EQ (5, sum.getDegree());
	EXPECT_EQ (-32.0 + 1, sum.evaluate(2.0));

	for (int i = 0; i <= 10; ++i)
	{
		c[i] = -p10.getCoeff(i);
	}
	p = Polynomial(c);
	sum = p10 + p;
	EXPECT_EQ (zero, sum);
	EXPECT_EQ(-1, sum.getDegree());
	EXPECT_EQ (0, numberOfTerms(sum));
}


TEST_F (PolynomialTests, multiplication) {
	Polynomial p2 (parabola);
	Polynomial p10 (degreeTen);

	Polynomial p = p2 * 1.0;
	EXPECT_EQ (p2, p);

	p = p10 * 1.0;
	EXPECT_EQ (p10, p);

	p = -2.0 * p10;
	for (int i = 0; i <= 10; ++i)
	{
		EXPECT_DOUBLE_EQ(-2.0 * degreeTen[i], p.getCoeff(i));
	}
	EXPECT_EQ (numberOfTerms(p10), numberOfTerms(p));
}

TEST_F (PolynomialTests, multiplication2) {
	Polynomial p2 (parabola);

	Polynomial p = p2 * 0.0;
	EXPECT_EQ (zero, p);

	EXPECT_EQ (-1, p.getDegree());

	p = zero * 10.0;
	EXPECT_EQ (zero, p);

	EXPECT_EQ (-1, p.getDegree());

}



TEST_F (PolynomialTests, input) {
	Polynomial p2 (parabola);
	string p2s = "3 1 -2 3";
	istringstream p2in (p2s);
	Polynomial p;
	p2in >> p;
	EXPECT_EQ (p2, p);

	Polynomial p10 (degreeTen);
	ostringstream p10out;
	p10out << 11 << " ";
	for (int i = 0; i <= 10; ++i)
		p10out << degreeTen[i] << ' ';
	istringstream p10in (p10out.str());
	p10in >> p;
	EXPECT_EQ (p10, p);

	p2s = "3 0 0 0";
	istringstream zin (p2s);
	zin >> p;
	EXPECT_EQ (zero, p);
	EXPECT_EQ (0, numberOfTerms(p));
}

TEST_F (PolynomialTests, output) {
	Polynomial p2 (parabola);
	ostringstream p2out;
	p2out << p2 << endl;
	EXPECT_EQ ("1 + -2 x + 3 x^2\n", p2out.str());

	Polynomial p10 (degreeTen);
	ostringstream p10out;
	p10out << p10;
	string p10s = p10out.str();
	EXPECT_NE(string::npos, p10s.find("x^5"));
	EXPECT_NE(string::npos, p10s.find("x^10"));
	EXPECT_EQ(string::npos, p10s.find("x^2"));

	Polynomial p42 (fortyTwo);
	ostringstream p42out;
	p42out << p42;
	string p42s = p42out.str();
	EXPECT_NE(string::npos, p42s.find("42"));
	EXPECT_EQ(string::npos, p42s.find("x"));

	ostringstream p0out;
	p0out << zero;
	EXPECT_EQ("0", p0out.str());
}


}  // namespace

