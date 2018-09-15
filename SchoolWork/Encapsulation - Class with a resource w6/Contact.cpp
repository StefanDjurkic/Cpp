// File: Contact.cpp
// Date: 3/11/2018
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com

#include <iostream>
#include <cstring>
#include "Contact.h"

namespace sict
{
	// default constructor
	Contact::Contact()
	{
		setEmpty(); /*Call the set empty functions and set this objects values to default values*/
	}

	// function to determine length of a number
	long long Contact::length(long long len)
	{
		if (len < 10000000000)
		{
			return 0;
		}
		else if (len < 100000000000)
		{
			return 11;
		}
		else if (len < 1000000000000)
		{
			return 12;
		}
		else
		{
			return 0;
		}
	}

	// set empty function
	void Contact::setEmpty()
	{
		coName[0] = '\0';
		xphoneNumbers = nullptr;
		xnoOfPhoneNumbers = 0;
	}

	// three argument constructor
	Contact::Contact(const char* name, long long* pNumber, int num)
	{
		setEmpty(); /*Set default values*/
		xphoneNumbers = new long long[xnoOfPhoneNumbers];

		if (name != nullptr && name[0] != '\0')
		{
			xphoneNumbers = pNumber;
			xnoOfPhoneNumbers = num;
			strncpy(coName, name, 19);
		}
	}
	
	// empty check
	bool Contact::isEmpty() const
	{
		bool empty; /*Declare a bool to check for empty*/
		if (coName[0] == '\0')
		{
			empty = true; /*if our name is empty then we set empty to true*/
		}
		else
		{
			empty = false; /*else if our name is empty set our variable to false*/
		}
		return empty; /*return our modified bool*/
	}

	// display
	void Contact::display()
	{
		if (!isEmpty()) /*Make sure our object is not empty*/
		{		
			std::cout << coName << std::endl; /*output the name*/
			long long testL; /*comparator variable for our phone numbers*/
			for (int i = 0; i < xnoOfPhoneNumbers; i++)
			{
				long long testL = length(xphoneNumbers[i]); /*set into comparator our value which is returned by length function(invalid 0, valid 11, or valid 12)*/

				int pl = 0; // plus one when testL == 12 down below which simply adds one to all the checks of i and z

				if (testL == 11 || testL == 12) /*if our number is within parameters*/
				{
					sprintf(str, "%lld", xphoneNumbers[i]);

					std::cout << "(+" << str[0];
					if (testL == 12) { std::cout << str[1]; pl = 1; }
					else { pl = 0; }

					std::cout << ") ";

					for (int z = 1 + pl; z < 11 + pl; z++)
					{
						std::cout << str[z];
						if (z == 3 + pl) { std::cout << " "; }
						if (z == 6 + pl) { std::cout << "-"; }
					}
					std::cout << std::endl;
				}			
			}		
		}
		else /*if length returned 0, the number is invalid and so we output a message*/
		{
			std::cout << "Empty contact!" << std::endl;
			if (coName != nullptr  && coName[0] != '\0')
			{
				std::cout << coName << std::endl;
			}
		}
	}
	
	/*Copy constructor*/
	Contact::Contact(const Contact& other) 
	{
		xphoneNumbers = nullptr;
		*this = other;
	}

	/*Copy assignment constructor*/
	Contact& Contact::operator=(const Contact& other) 
	{	
		if (this != &other)
		{
			strncpy(coName, other.coName, 19);
			xnoOfPhoneNumbers = other.xnoOfPhoneNumbers;
			delete[] xphoneNumbers;

			if (other.xphoneNumbers != nullptr) 
			{
				xphoneNumbers = new long long[xnoOfPhoneNumbers];
				for (int i = 0; i < xnoOfPhoneNumbers; i++) 
				{
					xphoneNumbers[i] = other.xphoneNumbers[i];
				}
			}
			else
			{
				xphoneNumbers = nullptr;
			}
		}
		return *this;
	}

	/*Overloaded += operator*/
	Contact& Contact::operator+=(long long other) 
	{
		xnoOfPhoneNumbers+=1;
		long long* newPhoneNumbers = new long long[xnoOfPhoneNumbers];
		for (int i = 0; i < xnoOfPhoneNumbers - 1; i++)
		{
			newPhoneNumbers[i] = xphoneNumbers[i];
		}
		newPhoneNumbers[xnoOfPhoneNumbers - 1] = other;
		xphoneNumbers = newPhoneNumbers;
		return *this;
	}

	//destructor
	Contact::~Contact() 
	{		
		delete [] xphoneNumbers;
		xphoneNumbers = nullptr;
	}
}