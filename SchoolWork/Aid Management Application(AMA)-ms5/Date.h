// File name: Date.h
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018
#ifndef __244_DATE_H__
#define __244_DATE_H__

#include <iostream>

namespace AMA
{
	// Macros
	const int NO_ERROR = 0;   //--No error - the date is valid
	const int CIN_FAILED = 1; //--istream failed on information entry
	const int YEAR_ERROR = 2; //--Year value is invalid
	const int MON_ERROR = 3; //--Month value is invalid
	const int DAY_ERROR = 4; //--Day value is invalid
	const int min_year = 2000;
	const int max_year = 2030;

	class Date
	{
		// private member variables
		int mdays(int month, int year)const;
		int YY;
		int MM;
		int DD;
		int _readErrorCode;
		// private member functions and setters
		int compValue() const;

		void errCode(int errorCode);

		// The error state function which the client can reference to determine if the object holds a valid date, and if not, which part of the date is in error
		void errState(int year, int month, int day);
	public:

		// default and 3 argument constructor
		Date();
		Date(int year, int month, int day);

		// Operators
		bool operator==(const Date& date)const;
		bool operator!=(const Date& date)const;
		bool operator<(const Date& date)const;
		bool operator>(const Date& date)const;
		bool operator<=(const Date& date)const;
		bool operator>=(const Date& date)const;

		// Queries and modifier

		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;

		// set empty function needed for me I tried going without it but it gets messy
		void setEmpty();

		// returns the error state as an error code value
		int errCode()const;

		// Returns true if the error state is != NO_ERROR. 
		bool bad()const;

	};
	// operator << and >> prototypes for ostream and istream
	std::ostream& operator<<(std::ostream& ostr, const Date& D);
	std::istream& operator>>(std::istream& istr, Date& D);
}
#endif
