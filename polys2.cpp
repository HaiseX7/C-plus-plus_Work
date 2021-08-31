/*
  File: polys.cpp
  Created by: Wade Goodell
  Creation Date: 12/1/2018
  Synopsis: This program takes in polynomials and manipulates them and 
  provides different kinds of information to them.
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include<cstdlib>

using namespace std;

class Term
{
private:
  int coeff;
	int exp;

public:
	int getCoeff() const;
	int getExp() const;
	void setCoeff(const int coefficient);
	void setExp(const int exponent);
	
	double eval(const double x) const;
	Term derivative() const;
	Term multiply(const Term & term) const;
	
	void displayFirst() const;
	void displayNext() const;

};

class Poly
{
private:
	vector<Term> terms;		// Terms are in decreasing order of degree

public:
	// member functions
	Term getTerm(const int index) const;
	int degree() const;		// highest degree
	int termCount() const;	// number of terms
		
	void addTerm(const int coeff, const int exp);
	void scale(const int fact);

	double eval(const double x) const;		// evaluate polynomial with value x
	Poly derivative() const;				// derivative
	
	void display(const string & label) const;
	void displayMultiply(const Poly & poly, const string & label) const;

};

void display_banner();
Poly read_poly(const int label);
void display_stats(const Poly & poly, const string & label);
void evaluate_poly(const Poly & poly);
void goodbye_banner();

int main()
{
  Poly poly1, poly2;
	int scale;
	
	display_banner();
	
	poly1 = read_poly(1);
	cout << endl;
	display_stats(poly1, "You entered polynomial #1");

	poly2 = read_poly(2);
	cout << endl;
	display_stats(poly2, "You entered polynomial #2");

	cout << "Multiplication terms - " << endl << endl;;
	poly1.displayMultiply(poly2, "Poly #1 * Poly #2");
	poly2.displayMultiply(poly1, "Poly #2 * Poly #1");
	
	cout << endl;
	
	evaluate_poly(poly1);
	cout << endl;
	
	if (poly1.termCount() > 0) {
		cout << "Enter a scale factor to apply to polynomial #1: ";
		cin >> scale;
		poly1.scale(scale);
		display_stats(poly1, "The polynomial after scaling");
	}

	goodbye_banner(); 
	
	return 0;
}
		 
// CLASS TERM MEMBER FUNCTIONS
int Term::getCoeff() const // gets the coefficient
{
	return coeff;
}
int Term::getExp() const // gets the exponent
{
	return exp;
}
void Term::setCoeff(const int coefficient) // sets the coefficient 
{
	coeff = coefficient;
}
void Term::setExp(const int exponent) // sets the exponent
{
	exp = exponent;
}
double Term::eval(const double x) const // evaluates the result
{
	int coeff = getCoeff();
	int exp = getExp();
	double eval = coeff * pow(x, exp);
	return eval;
}
Term Term::derivative() const // function for derivation
{
	int coeff = getCoeff();
	int exp = getExp();
	Term derivterm;
	if(exp == 0)
	{
		coeff = 0;
	}
	else if (exp == 1)
	{
		coeff = coeff;
		exp = 0;
	}
	else
	{
		coeff = coeff * exp;
		exp = exp - 1;
	}
	derivterm.setExp(exp);
	derivterm.setCoeff(coeff);

	return derivterm;
}
Term Term::multiply(const Term & term) const // function for multiplication
{
	Term multiple;
	multiple.setExp(getExp() + term.getExp());
	multiple.setCoeff(getCoeff() * term.getCoeff());

	return multiple;
}
void Term::displayFirst() const // function for display
{
	int coeff = getCoeff();
	int exp = getExp();

	cout << coeff;

	if(exp == 0)
	{
		cout << "";
	}
	else if (exp == 1)
	{
		cout << "x";
	}
	else
	{
		cout << "x^" << exp;
	}
}
void Term::displayNext() const // function fro displaying the next
{
	int coeff = getCoeff();
	int exp = getExp();

	if(coeff > 0)
	{
		cout << " + " << coeff;
	}
	else if (coeff < 0)
	{
		cout << " - " << abs(coeff);
	}

	if(exp == 0)
	{
		cout << "";
	}
	else if (exp == 1)
	{
		cout << "x";
	}
	else
	{
		cout << "x^" << exp;
	}
}
// CLASS POLY MEMBER FUNCTIONS
Term Poly::getTerm(const int index) const // function that gets the term
{
	return terms.at(index);
}
int Poly::degree() const // function for the degree
{
	return terms.at(0).getExp();
}
int Poly::termCount() const // function for the term count
{
	return terms.size();
}
void Poly::addTerm(const int coeff, const int exp) // function for the add term
{
	Term newterm;
	newterm.setExp(exp);
	newterm.setCoeff(coeff);
	terms.push_back(newterm);
}
void Poly::scale(const int fact) // function that scales the polynomial 
{
	for(int i = 0; i < terms.size(); i++)
	{
		int term_coeff = terms.at(i).getCoeff();
		cout << term_coeff;
		terms.at(i).setCoeff(term_coeff * fact);
	}
}
double Poly::eval(const double x) const // function that evaluates
{
	double sum(0);
	for(int i = 0; i < terms.size(); i++)
	{
		sum += terms.at(i).eval(x);
	}
	return sum;
}
Poly Poly::derivative() const // function for the derivative
{
	Poly derivpoly;
	Term derivterm;
	for(int i = 0; i < terms.size(); i++)
	{
		derivterm = terms.at(i).derivative();
		derivpoly.addTerm(derivterm.getCoeff(), derivterm.getExp());
	}
	return derivpoly;
}
void Poly::display(const string & label) const // function for the display
{
	cout << label << endl;
	
	for(int i = 0; i<terms.size(); i++)
	{
		if(i == 0)
		{
			terms.at(i).displayFirst();
		}
		else
		{
			terms.at(i).displayNext();

		}
	}
	cout << endl;
}
void Poly::displayMultiply(const Poly & poly, const string & label) const 
// function for displaying the multiplication
{
	cout << endl << label << endl;
	for(int i = 0; i<terms.size(); i++)
	{
		Term value = terms.at(i);
		for(int j = 0; j < poly.termCount(); j++)
		{
				Term multiplied = value.multiply(poly.getTerm(j));
				int coeff = multiplied.getCoeff();
				int exp = multiplied.getExp();
				if(i == 0 && j == 0)
				{
					if(exp == 0)
					{
						cout << coeff;
					}
					else if(exp == 1)
					{
						cout << coeff << "x";
					}
					else 
					{
						cout << coeff << "x^" << exp;
					}
				}
				else
				{
					if(coeff < 0)
					{
						cout << " - " << abs(coeff);
					}
					else
					{
						cout << " + " << coeff;
					}
					if(exp == 0)
					{
					}
					else if(exp == 1)
					{
						cout << "x";
					}
					else 
					{
						cout << "x^" << exp;
					}
				}
		}
	}
}
// NON-MEMBER FUNCTIONS
void display_banner() // function for displaying the banner
{
	cout << endl << "Welcome to fun with polynomials!" << endl;
	cout << "You will enter two polynomials." << endl;
	cout << "Please follow all instructions below." << endl;
}
Poly read_poly(const int label) // function for reading the polynomial
{
	int coeff, exp, prevexp = 999;
	Poly newpoly;
	bool valid = true;
	bool end = false;

	cout << endl << "Enter poly #" << label << ": " << endl;

	while(valid and !end)
	{
		cin >> coeff >> exp;
		if(exp < 0 || prevexp < exp)
		{
			cout << "Invalid Term. Bye!" << endl;
			exit(EXIT_FAILURE);
		}
		newpoly.addTerm(coeff, exp);
		if(coeff && exp == 0 || exp == 0)
		{
		end = true;
		}
		prevexp = exp;
	}
	return newpoly;
}
void display_stats(const Poly & poly, const string & label) // displays the stats
{
	poly.display(label);
	cout << "The polynomial has degree " << poly.degree() << endl;
	cout << "The polynomial has " << poly.termCount() << " term(s)" << endl;
	cout << endl << "The derivative of the polynomial is:" << endl;
	
	Poly dpoly;
	dpoly = poly.derivative();
	dpoly.display("Derivative of the polynomial is: ");

}
void evaluate_poly(const Poly & poly) // evaluates the polynomial
{	
	int times_eval(0);
	double value(0);
	bool invalid = false;

	do
	{
		cout << "How many times would you like to evaluate polynomial #1? ";
		cin >> times_eval;
	}while(times_eval < 0);

	for(int i = 0; i < times_eval; i++)
	{
		cout << "Enter the value to evaluate: ";
		cin >> value;
		poly.display("The polynomial is:");
		cout << "When x = " << value << " the polynomial evaluates to " << poly.eval(value) << endl << endl;
	}
}
void goodbye_banner() // function for the goodbye banner
{
	cout << endl;
	cout << "Thanks for using Polynomial Functions." << endl;
	cout << "Please visit again!" << endl;
	cout << "Bye for now." << endl;
}