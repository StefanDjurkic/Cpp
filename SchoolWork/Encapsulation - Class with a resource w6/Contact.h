// File: Contact.h
// Date: 3/11/2018
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com

#ifndef _CONTACT_H_
#define _CONTACT_H__

namespace sict
{
	class Contact
	{
	protected:
		char coName[20]; /*Our contacts name*/
		long long* xphoneNumbers; /*The phone number*/
		int xnoOfPhoneNumbers; /*The amount of phone numbers*/
		int xoutputNum;/*The number to be outputed*/
		char str[256]; 
		
	public:
		// default constructor 
		Contact();
		// constructor with 3 parameters
		Contact(const char*, long long*, int);
		// destructor
		~Contact();
		// empty query 
		bool isEmpty() const;
		long long length(long long len);
		// display query 
		void display();
		// set empty function
		void setEmpty();
		// operator functions
		Contact& operator+=(long long other) ;
		Contact(const Contact& other);
		Contact& operator=(const Contact& other);
	};
}
#endif 
