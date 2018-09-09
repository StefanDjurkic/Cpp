// File name: Perishable.cpp
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include "Perishable.h"

using namespace std;

namespace AMA
{
	Perishable::Perishable() : Product('P') { }

	std::fstream & Perishable::store(std::fstream & file, bool addNewLine) const
	{
		Product::store(file, false);
		file << ',';
		expireObj.write(file);
		if (addNewLine == true) {
			file << std::endl;
		}
		return file;
	}

	std::fstream & Perishable::load(std::fstream & file)
	{
		Product::load(file);
		expireObj.read(file);
		file.ignore();
		return file;
	}

	// This query receives a reference to an ostream object and a bool flag and returns a
	// reference to the modified ostream object
	std::ostream & Perishable::write(std::ostream & ostr, bool linear) const
	{	
		Product::write(ostr, linear);
		// if not empty and tester comparator equals zero proceed
			if (!isEmpty() && isClear())
			{
				if (linear)
				{
					ostr << setfill(' ') << left;
					expireObj.write(ostr);
					
				}
				else
				{
				ostr << std::endl;
				ostr << " Expiry date: ";
				expireObj.write(ostr);

				}
			}

		return ostr;
	}

	std::istream & Perishable::read(std::istream & istr)
	{
		Product::read(istr);
		// create a temporary date object
		Date tempdate;

		if (isClear() == true) 
		{		
			// output format
			std::cout << " Expiry date (YYYY/MM/DD): ";
			
			// input into tempdate
			istr >> tempdate;

			// if there's an error code then display them else set comparator to zero and put expireObj into tempdate 
			if (tempdate.bad() == false)
			{
				if (tempdate.errCode() == 1) 
				{
					message("Invalid Date Entry");
					istr.setstate(ios::failbit);	
				}

				if (tempdate.errCode() == 2) 
				{
					message("Invalid Year in Date Entry");
					istr.setstate(ios::failbit);
				}

				if (tempdate.errCode() == 3) 
				{
					message("Invalid Month in Date Entry");
					istr.setstate(ios::failbit);
				}

				if (tempdate.errCode() == 4) 
				{
					message("Invalid Day in Date Entry");
					istr.setstate(ios::failbit);
				}
			}
			else
			{
				expireObj = tempdate;
			}			
		} 
		
		return istr;
	}

	const Date& Perishable::expiry() const 
	{
		return expireObj;
	}

}