// File: Product.h
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018
#ifndef _PRODUCT_
#define _PRODUCT_
#include <fstream>
#include "ErrorState.h"
#include "iProduct.h"
namespace AMA
{

	// Pre-defined constants:
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Product : public iProduct
	{
		// Private data members:

		// A character that indicates the type of the product – for use in the file record
		char prodType;

		// A character array that holds the product’s sku (stock keeping unit) – the maximum
		// number of characters excluding the null byte is defined by the namespace constant.
		char prodSKU[max_sku_length];

		// A character array that describes the product’s unit

		char prodUnit[max_unit_length];

		// A pointer that holds the address of a C-style string in dynamic memory containing the name of the product.
		char* myName;

		// An integer that holds the quantity of the product currently on hand; that is, the number of units currently on hand.
		int prodQuantity;

		// An integer that holds the quantity of the product needed
		int prodNeeded;

		// A double that holds the price of a single unit of the product before any taxes
		double priceBeforeTax;

		// the taxable variable holds the status of wether or not an object will have taxes applied to it
		bool taxable;

		// An ErrorState object that holds the error state of the Product object.
		ErrorState errO;

	protected:

		// protected functions

		// This function receives the address of a C-style null-terminated string that holds the name of the product. stores the name in dynamically allocated memory
		// replaces any name previously stored If the incoming parameter holds the nullptr address, this function removes the name of the product, if any, from memory.
		void name(const char* addr);

		// This query returns the address of the C-style string that holds the name of the product. If the product has no name, this query returns nullptr.
		const char* name() const;

		// This query returns the price of a single item of the product plus any tax that applies to the product.
		double cost() const;

		// This query returns the address of the C-style string that holds the sku of the product. 
		const char* sku() const;

		// This query returns the address of the C-style string that holds the unit of the product. 
		const char* unit() const;

		// This query returns true if the ErrorState object is clear; false otherwise.
		bool isClear() const;

	    // This function receives the address of a C-style null-terminated string holding an error message and stores that message in the ErrorState object. 
		// in my case it also returns the message so I have made the function bool instead of void, I sure as heck could have made another function to do that
		// but this is more efficient...all in one. Million dollar function
		bool message(const char* message);

		// This query returns the taxable status of the product. 
		bool taxed() const;

		// This query returns the price of a single item of the product. 
		double price() const;

	public:

		// zero one constructor
		// This constructor optionally receives a character that identifies the product type. The default value is ‘N’. This function 
		// stores the character receives in an instance variable sets the current object to a safe recognizable empty state.
		Product(char type = 'N');

		// Seven argument constructor assigns variables to the object
		Product(const char* sknum, const char* named, const char* unit, int qHave = 0, bool status = true, double price = 0.0, int qNeed = 0);

		// This destructor function deallocates any memory that has been dynamically allocated.
		~Product();

		// Copy Constructor 
		// This constructor receives an unmodifiable reference to a Product object and copies the object referenced to the current object. 
		Product(const Product& other);

		// This operator receives an unmodifiable reference to a Product object and replaces the current object with a copy of the object referenced. 
		Product& operator=(const Product& other);

		// This query receives the address of an unmodifiable C-style null-terminated string and returns true if the string is identical to the sku of the current object; false otherwise.
		bool operator==(const char* addr) const;

		// This query that returns the total cost of all items of the product on hand, taxes included.
		double total_cost() const;

		// This modifier that receives an integer holding the number of units of the Product that are on hand. This function resets the number of units that are on hand to the number received.
		void quantity(int prodHave);

		// This query returns true if the object is in a safe empty state; false otherwise.
		bool isEmpty() const;
		
		// This query that returns the number of units of the product that are needed.
		int qtyNeeded() const;

	    // This query returns the number of units of the product that are on hand.
		int quantity() const;

		// This query receives the address of a C-style null-terminated string holding a product sku and returns true if the sku of the current object is greater than the string stored at the received address (according to how the string comparison functions define ‘greater than’); false otherwise.
		bool operator>(const char* productSKU) const;

		//This modifier receives an integer identifying the number of units to be added to the Product and returns the updated number of units on hand. If the integer received is positive-valued, this function adds it to the quantity on hand. If the integer is negative-valued or zero, this function does nothing and returns the quantity on hand (without modification).
		int operator+=(int numz);

		// This query receives a reference to an fstream object and an optional bool and returns a reference to the fstream object. This function 
		//	inserts into the fstream object the character that identifies the product type as the first field in the record.
		//	inserts into the fstream object the data for the current object in comma separated fields.
		//	if the bool parameter is true, inserts a newline at the end of the record.
		std::fstream& store(std::fstream& file, bool newLine = true) const;

		// This modifier receives a reference to an fstream object and returns a reference to that fstream object. This function 
		// extracts the fields for a single record from the fstream object
		// creates a temporary object from the extracted field data
		// copy assigns the temporary object to the current object.
		std::fstream& load(std::fstream& file);

		// This query receives a reference to an ostream object and a bool and returns a reference to the ostream object. This function inserts the data fields for the current object into the ostream object in the following order and separates them by a vertical bar character (‘|’). 
		// If the bool parameter is true, the output is on a single line with the field widths as shown below in parentheses:
		std::ostream& write(std::ostream& os, bool linear) const;

		// This function extracts the data fields for the current object in the following order, line by line. This function stops extracting data once it has encountered an error
		std::istream& read(std::istream& is);

		// This query receives an unmodifiable reference to a Product object and returns true if the name of the current object is 
		// greater than the name of the referenced Product object (according to how the string comparison functions define ‘greater than’); false otherwise.
		bool operator>(const iProduct& other) const;
		
		
	};
	// This helper receives a reference to an ostream object and an unmodifiable reference to a Product object and returns a reference to the ostream object. 
	std::ostream& operator<<(std::ostream&, const iProduct&);
	// This helper receives a reference to an istream object and a reference to a Product object and returns a reference to the istream object.
	std::istream& operator>>(std::istream&, iProduct&);
	// This helper receives a reference to a double and an unmodifiable reference to a Product object and returns a double
	double operator+=(double& dbl, const iProduct& other);
}
#endif