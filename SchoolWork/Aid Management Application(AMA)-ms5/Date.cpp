// File name: Date.cpp
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018
#include <iomanip>
#include <iostream>
#include "Date.h"

namespace AMA
{
	// provided equation to compare values
	int Date::compValue()const
	{
		return YY * 372 + MM * 31 + DD;
	}

	// returns the error code
	void Date::errCode(int errorCode)
	{
		_readErrorCode = errorCode;
	}

	// checks if the year month or day is an error and then stores that in errCode function/_readErrorCode
	void Date::errState(int year, int month, int day)
	{
		if (year < min_year || year > max_year)
		{
			errCode(YEAR_ERROR);
		}
		else if (month < 1 || month > 12) {
			errCode(MON_ERROR);
		}
		else if (day < 1 || day > mdays(month, year))
		{
			errCode(DAY_ERROR);
		}
		else
		{
			errCode(NO_ERROR);
		}
	}

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	// Default constructor
	Date::Date()
	{
		setEmpty();
		errCode(NO_ERROR);
	}

	Date::Date(int year, int month, int day)
	{

		errState(year, month, day);

		if (bad() == true)
		{
			YY = year;
			MM = month;
			DD = day;
		}
		else
		{
			setEmpty();
			errCode(NO_ERROR);

		}

	}

	// set empty function
	void Date::setEmpty()
	{
		YY = 0;
		MM = 0;
		DD = 0;
	}

	// Returns error code value
	int Date::errCode() const
	{
		return _readErrorCode;
	}


	bool Date::bad() const
	{
		if (this->_readErrorCode == NO_ERROR)
		{
			return true;
		}
		return false;
	}

	// Operators
	bool Date::operator==(const Date& date) const
	{
		return (compValue() == date.compValue());
	}

	bool Date::operator!=(const Date& date) const
	{
		return (compValue() != date.compValue());
	}

	bool Date::operator<(const Date& date) const
	{
		return (compValue() < date.compValue());
	}

	bool Date::operator>(const Date& date) const
	{
		return (compValue() > date.compValue());
	}

	bool Date::operator<=(const Date& date) const
	{
		return (compValue() <= date.compValue());
	}

	bool Date::operator>=(const Date& date) const
	{
		return (compValue() >= date.compValue());
	}

	// Read/write functions
	std::istream& Date::read(std::istream& istr) {



		istr >> YY;
		if (istr.get() != '/')
		{
			_readErrorCode = CIN_FAILED;
			return istr;
		}
		istr >> MM;
		if (istr.get() != '/')
		{
			_readErrorCode = CIN_FAILED;
			return istr;
		}
		istr >> DD;
		errState(YY, MM, DD);
		if (_readErrorCode != NO_ERROR)
		{
			setEmpty();
		}
		return istr;


	}

	std::ostream& Date::write(std::ostream& ostr)const
	{

		ostr << YY << "/";

		if (MM > -1 && MM < 10)
		{
			ostr << "0" << MM << "/";
		}
		else
		{
			ostr << MM << "/";
		}

		if (DD < 10 && DD > -10)
		{
			ostr << "0" << DD;
		}
		else
		{
			ostr << DD;
		}

		return ostr;
	}

	// Helper functions (istream & ostream)
	std::ostream& operator<<(std::ostream& ostr, const Date& date)
	{
		return date.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Date& date)
	{
		return date.read(istr);
	}


}