// File name: Perishable.h
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018

#ifndef _PERISHABLE_H_
#define _PERISHABLE_H_
#include "Product.h"
#include "Date.h"
namespace AMA 
{

	class Perishable : public Product 
	{
		// creation of a Date object holding expiry date for perishable prod
		Date expireObj;

	public:
		// This constructor passes the file record tag for a perishable product (‘P’) to the base class
		// constructor and sets the current object to a safe empty state.
		Perishable();
		
		// This query returns the expiry date for the perishable product.
		const Date & expiry() const;
		
		// This query receives a reference to an fstream object and an optional bool and returns a
		// reference to the modified fstream object.This function stores a single file record for the current object.
		std::fstream& store(std::fstream& file, bool addNewLine = true) const;

		// This modifier receives a reference to an fstream object and returns a reference to that
		// fstream object.This function extracts the data fields for a single file record from the fstream object.This function
		std::fstream& load(std::fstream& file);

		// This query receives a reference to an ostream object and a bool flag and returns a
		// reference to the modified ostream object.The flag identifies the output format.
		std::ostream& write(std::ostream& os, bool linear)const;
		 
		// his modifier receives a reference to an istream object and returns a reference to the
		// modified istream object.This function populates the current object with the data extracted from the istream object
		std::istream& read(std::istream& istr);

	};
}


#endif 
