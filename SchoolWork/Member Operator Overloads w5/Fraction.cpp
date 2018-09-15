// Workshop 5: operator overloading
// File: Fraction.cpp
// Name: Stefan Djurkic
// Date: 2/25/2018
/////////////////////////////////////////////

#include <iostream>
#include "Fraction.h"

/*continue the namespace*/ 
namespace sict
{
	// default constructor
	Fraction::Fraction()
	{
		numerator = -1;
		denominator = -1;
	}

	// two-argument constructor
	Fraction::Fraction(int num, int denom)
	{
		if (num > -1 && denom > 0)
		{
			numerator = num;
			denominator = denom;
			reduce();
		}
		else
		{
			numerator = -1;
			denominator = -1;
		}
	}

	// max query
	int Fraction::max() const
	{
		if (denominator > numerator)
		{
			return denominator;
		}
		else
		{
			return numerator;
		}
	}

	// min query
	int Fraction::min() const
	{
		if (denominator < numerator)
		{
			return denominator;
		}
		else
		{
			return numerator;
		}
	}
	
	// gcd returns the greatest common divisor of num and denom
	int Fraction::gcd() const
	{
		int mn = min();  // min of numerator and denominator
		int mx = max();  // max of numerator and denominator
		int g_c_d = 1;
		bool found = false;
		for (int x = mn; !found && x > 0; --x) // from mn decrement until divisor found
		{ 
			if (mx % x == 0 && mn % x == 0)
			{
				found = true;
				g_c_d = x;
			}
		}
		return g_c_d;
	}

	// reduce modifier
	void Fraction::reduce()
	{
		int result = gcd();
		numerator /= result;
		denominator /= result;
	}
	
	// display query
	void Fraction::display() const
	{
		if (isEmpty())
		{
			std::cout << "no fraction stored";
		}

		if (denominator > 0 && numerator > -1) 
		{
			if (denominator == 1) 
			{
				std::cout << numerator;
			}
			else 
			{
				std::cout << numerator << "/" << denominator;
			}
		}
	}

	// isEmpty query
	bool Fraction::isEmpty() const
	{

		if (numerator == -1 || denominator == -1)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	// Overloaded + operator
	Fraction operator+(const Fraction& rhs, const Fraction& lhs)
	{
		Fraction operation;

		if (lhs.isEmpty() || operation.isEmpty()) 
		{
			operation.denominator = -1;
		}

		if (!lhs.isEmpty() && !rhs.isEmpty()) 
		{
			operation.numerator = (lhs.numerator*rhs.denominator) + (rhs.numerator*lhs.denominator);
			operation.denominator = lhs.denominator * rhs.denominator;
			operation.reduce();
		}
		return operation;
	}

	// Overloaded += operator
	Fraction Fraction::operator+=(const Fraction& rhs) 
	{

		if (isEmpty() || rhs.isEmpty())
		{
			Fraction();
		}

		if (!isEmpty() && !rhs.isEmpty()) 
		{
			this->numerator = (numerator * rhs.denominator) + (rhs.numerator*denominator);
			this->denominator = denominator * rhs.denominator;
			this->reduce();
		}

		return *this;
	}

	// Overloaded * operator
	Fraction Fraction::operator*(const Fraction& rhs) 
	{
		Fraction operation;

		if (isEmpty() || rhs.isEmpty()) 
		{
			Fraction();
		}

		if (!isEmpty() && !rhs.isEmpty()) 
		{
			operation.numerator = (numerator * rhs.numerator);
			operation.denominator = (denominator * rhs.denominator);
		}

		return operation;
	}

	// Friend overloaded == operator
	bool operator== (const Fraction& rhs, const Fraction& lhs) 
	{
		bool result = false;

		if (lhs.isEmpty() || rhs.isEmpty()) 
		{
			result = false;
		}
		if (!lhs.isEmpty() && !rhs.isEmpty()) 
		{
			if (lhs.numerator*rhs.denominator == rhs.numerator*lhs.denominator) 
			{
				result = true;
			}
		}
		return result;
	}

	// Friend overloaded != operator
	bool operator!= (const Fraction& rhs, const Fraction& lhs) 
	{
		bool result = false;

		if (lhs.isEmpty() || rhs.isEmpty()) 
		{
			result = false;
		}

		if (!lhs.isEmpty() && !rhs.isEmpty()) 
		{
			result = !(lhs == rhs);
		}
		return result;
	}
}

