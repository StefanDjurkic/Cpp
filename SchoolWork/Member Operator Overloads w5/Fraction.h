// Workshop 5: operator overloading
// File: Fraction.h
// Name: Stefan Djurkic
// Date: 2/25/2018
/////////////////////////////////////////////

#ifndef _FRACTION_H_
#define _FRACTION_H_

// create namespace
namespace sict
{
	// Fraction class
	class Fraction 
	{
	private:
		// instance variables 
		int numerator;
		int denominator;
		// greater than lesser than functions
		int max() const;
		int min() const;
		// reduce function
		void reduce();
		// greatest common divisor function
		int gcd() const;

	public:
		// public member functions
		// default constructor
		Fraction();
		// two arguments constructor
		Fraction(int num, int denom);
		// is empty function
		bool isEmpty() const;
		// display function
		void display() const;
		// + operator overload
		friend Fraction operator+(const Fraction& rhs, const Fraction& lhs);
		// += operator overload
		Fraction operator+=(const Fraction& rhs);
		// * operator overload
		Fraction operator*(const Fraction&);
		// friend == operator overload
		friend bool operator==(const Fraction& rhs, const Fraction& lhs);
		// friend != operator overload
		friend bool operator!=(const Fraction& rhs, const Fraction& lhs);
	};
};
#endif


