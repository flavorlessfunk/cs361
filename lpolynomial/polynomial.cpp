#include "polynomial.h"
#include <algorithm>

using namespace std;


Polynomial::Polynomial ()
{
}

Polynomial::Polynomial (int nCoeff, double coeff[])
{
	for (int i = 0; i < nCoeff; ++i)
	{
		const double& c = coeff[i];
		if (c != 0.0)
			terms.push_back (Term(c, i));
	}
}

Polynomial::Polynomial (const vector<double>& coeff)
{
	for (vector<double>::size_type i = 0; i < coeff.size(); ++i)
	{
		const double& c = coeff[i];
		if (c != 0.0)
			terms.push_back (Term(c, i));
	}
}




double Polynomial::evaluate (double x) const
{
	double sum = 0.0;
	int k = getDegree();
	auto pos = terms.rbegin();
	while (pos != terms.rend())
	{
		if (k > pos->power) {
			sum *= x;
		} else {
			sum = x * sum + pos->coeff;
			++pos;
		}
		--k;
	}
	while (k >= 0) {
		sum *= x;
		--k;
	}
	return sum;
}

int Polynomial::getDegree() const
{
	if (terms.empty())
		return -1;
	else
		return terms.back().power;
}

double Polynomial::getCoeff(int power) const
{
	for (const Term& t: terms) {
		if (t.power == power)
			return t.coeff;
		else if (t.power > power)
			return 0.0;
	}
	return 0.0;
}

Polynomial Polynomial::operator+ (const Polynomial& p) const
{
	Polynomial result;
	auto pos1 = terms.begin();
	auto pos2 = p.terms.begin();
	while (pos1 != terms.end() && pos2 != p.terms.end())
	{
		if (pos1->power < pos2->power)
		{
			result.terms.push_back(*pos1);
			++pos1;
		}
		else if (pos1->power > pos2->power)
		{
			result.terms.push_back(*pos2);
			++pos2;
		}
		else // (pos1->power == pos2->power)
		{
			double sum = pos1->coeff + pos2->coeff;
			if (sum != 0.0)
				result.terms.push_back(Term(sum, pos1->power));
			++pos1;
			++pos2;
		}
	}
	while (pos1 != terms.end())
	{
		result.terms.push_back(*pos1);
		++pos1;
	}
	while (pos2 != p.terms.end())
	{
		result.terms.push_back(*pos2);
		++pos2;
	}
	return result;
}


Polynomial Polynomial::operator* (double scale) const
{
	if (terms.empty() || scale == 0.0)
		return Polynomial();

	Polynomial result (*this);
	for (Term& term: result.terms)
	{
		term.coeff *= scale;
	}
	return result;
}


bool Polynomial::Term::operator== (const Term& t) const
{
	return (power == t.power) && (coeff == t.coeff);
}


bool Polynomial::operator== (const Polynomial& p) const
{
	if (getDegree() != p.getDegree())
		return false;

	return equal (terms.begin(), terms.end(), p.terms.begin());
}


std::istream& operator>> (std::istream& in, Polynomial& p)
{
	int r;
	in >> r;
	vector<double> coefficients;
	coefficients.resize(r);
	for (int i = 0; i < r; ++i)
		in >> coefficients[i];
	p = Polynomial(coefficients);
	return in;
}


std::ostream& operator<< (std::ostream& out, const Polynomial& p)
{
	if (p.getDegree() < 0)
	{
		out << "0";
	}
	else
	{
		bool first_printed = true;
		for (const Polynomial::Term& t: p.terms)
		{
			double c = t.coeff;
			if (!first_printed)
			{
				out << " + ";
			}
			first_printed = false;
			out << c;
			if (t.power > 0)
			{
				out << " x";
				if (t.power > 1)
				{
					out << "^" << t.power;
				}
			}
		}
	}
	return out;
}



