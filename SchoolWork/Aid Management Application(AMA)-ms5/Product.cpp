// File: Product.cpp
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include "Product.h"
using namespace std;

namespace AMA
{
	void Product::name(const char * addr)
	{
		// if incoming variable is a nullptr delete name of prod from memory
		if (addr == nullptr)
		{
			myName = nullptr;
			delete[] myName;	
		}
		else // else if it's not a nullptr then go ahead and assign it to memory
		{
			myName = new char[strlen(addr)];
			strcpy(myName, addr);
		}
	}

	// return myName variable, if it has no name then return a nullptr
	const char * Product::name() const
	{
		if (myName[0] == '\0')
		{
			return nullptr;
		}
		else
		{
			return myName;
		}
	}

	// zero one argument constructor--assigns prodtype to either a default or a provided char, sets the object to a safe empty state
	Product::Product(char type)
	{
		prodType = type;
		prodSKU[0] = '\0';
		prodUnit[0] = '\0';
		myName = nullptr;
		prodQuantity = 0;
		prodNeeded = 0;
		priceBeforeTax = 0.0;
		taxable = true;
	}
	
	// seven argument constructor assigns provided variables and creates an object
	Product::Product(const char* sknum, const char* named, const char* unit, int qHave, bool status, double price, int qNeed)
	{
		name(named);
		strcpy(prodSKU, sknum);
		strcpy(prodUnit, unit);
		prodQuantity = qHave;
		prodNeeded = qNeed;
		priceBeforeTax = price;
		taxable = taxable;
	}

	// current object equates other prod obj
	Product::Product(const Product & other)
	{
		(*this) = other;
	}

	// assignment copy operator
	Product & Product::operator=(const Product & other)
	{
		// if other obj is already equivalent to current obj then just return it
		if (&other == this)
		{
			return *this;
		}
		// copy assign all the variables
		strncpy(this->prodSKU, other.prodSKU, max_sku_length);
		strncpy(this->prodUnit, other.prodUnit, max_unit_length);
		this->myName = nullptr;
		name(other.myName);
		this->prodQuantity = other.prodQuantity;
		this->prodNeeded = other.prodNeeded;
		this->priceBeforeTax = other.priceBeforeTax;
		this->taxable = other.taxable;
		return *this;
	}

	// this destructor sets myName to nullptr then deletes it once out of scope
	Product::~Product()
	{
		myName = nullptr;
		delete[] myName;
	}

	// This query receives a reference to an fstream object and an optional bool and returns a
	// reference to the modified fstream object.This function stores a single file record for the current object
	std::fstream & Product::store(std::fstream & file, bool newLine) const
	{
		//check if the file is actually open, then input variables according to the ',' delimiter
		if (file.is_open())
		{
			file << prodType << ',' << prodSKU << ',' << myName << ',' << prodUnit << ',' << taxable << "," << priceBeforeTax << "," << prodQuantity << "," << prodNeeded;
		}
		if (newLine) // if bool newline then create a newline endl
		{
			file << std::endl;
		}
		return file; // return the file
	}

	// This modifier receives a reference to an fstream object and returns a reference to that
	// fstream object.This function extracts the data fields for a single file record from the fstream object.
	std::fstream & Product::load(std::fstream & file)
	{
		// temp variables
		char skus[max_sku_length];
		char productName[max_name_length];
		char units[max_unit_length];
		int quant = 0;
		int quantityNeeded = 0;
		double prices = 0.0;
		char taxables;

		// get line to extract variables from file 
		file.getline(skus, max_sku_length, ',');
		file.getline(productName, 20, ',');
		file.getline(units, max_unit_length, ',');
		file >> taxables; // cant seem to get the variable to go in taxable right so just grabbing 1 since that is == true
		if (taxables == '1')
		{
			taxable = true;
		}
		else // else taxable must be false
		{
			taxable = false;
		}
		
		file.ignore(); // ignore delimiter
		file >> prices; // file inserts into temp var
		file.ignore();
		file >> quant;
		file.ignore();
		file >> quantityNeeded;
		file.ignore();

		// copy assign
		strcpy(prodSKU, skus);
		strcpy(prodUnit, units);
		name(productName);
		this->priceBeforeTax = prices;
		this->prodQuantity = quant;
		this->prodNeeded = quantityNeeded;
		
		return file; 
	}

	// This query receives a reference to an ostream object and a bool flag and returns a
	// reference to the modified ostream object.The flag identifies the output format.
	std::ostream & Product::write(std::ostream & os, bool linear) const
	{
		// if errO obj is clear proceed
		if (errO.isClear()) 
		{
			// if linear check
			if (linear) 
			{	
				// first we set a fill character which is a space, align the fill left then alternate the processess switching between right/left when appropriate
				// display variables with the right width
				os << setfill(' ') << left << setw(7) << prodSKU << "|" << setfill(' ') << left << setw(20) << name() << "|";
				os << setfill(' ') << right << setw(7) << fixed << setprecision(2) << cost() << "|" << setfill(' ') << right << setw(4) << prodQuantity << "|";
				os << setfill(' ') << left << setw(10) << prodUnit << "|" << setfill(' ') << right << setw(4) << prodNeeded << "|";
			}

			else //if bool linear == false
			{
			// return sku,name, and price
			os << " Sku: " << sku() << std::endl << " Name (no spaces): " << name() << std::endl << " Price: " << price() << std::endl;
				
				// if taxable then display the result of cost() function
				if (taxed()) 
				{
				os << " Price after tax: " << cost() << std::endl;
				}
				// else there is no tax so display N/A
				else 
				
				{
				os << " Price after tax:  N/A" << std::endl;
				}
			//return prod quantity, produnit and prodneeded	
			os << " Quantity on Hand: " << prodQuantity << " " << prodUnit << std::endl << " Quantity needed: " << prodNeeded;
			
			}
		}
		else // else if there is an error, display it
		{
			os << errO.message();
		}
		return os; //return ostream obj
	}

	// This modifier receives a reference to an istream object and returns a reference to the
	//	modified istream object.This function populates the current object with the data extracted from the istream object
	std::istream & Product::read(std::istream & is)
	{
		//temp variables
		char skus[max_sku_length + 1];
		char* productName;
		char units[max_unit_length + 1];
		int quant;
		int quantityNeeded;
		double prices;
		char taxables;
		bool taxation;
		int exit = 0; // exit variable for a do while loop below
		productName = new char[max_name_length];
	
		do // this do while loop exits upon an error message this is done by setting exit to 1 and then breaking
		{	
		errO.clear(); // clear the errO obj because we're checking for new errors
		
		//inputs into temp variables
		cout << " Sku: ";
		is >> skus; 
		
		cout << " Name (no spaces): ";
		is >> productName;
		
		cout << " Unit: ";
		is >> units;
		
		cout << " Taxed? (y/n): ";
		is >> taxables;
		
		// checking for taxables equating to one of the correct chars, if they aren't equatable then set an error message and failbit state, exit the loop
		if (taxables != 'Y' && taxables != 'N' && taxables != 'y' && taxables != 'n')
		{
			errO.message("Only (Y)es or (N)o are acceptable");
			is.setstate(std::ios::failbit);
			exit += 1; // loop exits
			break;
		}

		cout << " Price: ";
		is >> prices;
		
		// if input fails then set the right message for price
		if (is.fail()) 
		{
			errO.message("Invalid Price Entry");
			is.setstate(std::ios::failbit);
			exit += 1; // loop exits
			break;
		}

			cout << " Quantity on hand: ";
			is >> quant;
		

		// if input fails then set the right message for qty
		if (is.fail()) 
		{
			errO.message("Invalid Quantity Entry");
			is.setstate(std::ios::failbit);
			exit += 1; // loop exits
			break;
		}

			cout << " Quantity needed: ";
			is >> quantityNeeded;

		// if input fails then set the right message for qtyneeded
		if (is.fail()) 
		{
			errO.message("Invalid Quantity Needed Entry");
			exit += 1; // loop exits
			break;
		}
		
		if (taxables == 'y' || taxables == 'Y')
		{
		taxation = true; // if taxables input equates to yes then taxation is true and is inputed into taxable down below
		}
		else // else taxation must be false so set it as such to be inputed into taxable
		{
		taxation = false; 
		}
			// copy assign temp variables to this obj
			strncpy(this->prodSKU, skus, max_sku_length);
			strncpy(this->prodUnit, units, max_unit_length);
			name(productName);
			this->prodQuantity = quant;
			this->prodNeeded = quantityNeeded;
			this->priceBeforeTax = prices;
			this->taxable = taxation;
		// exit out of the loop
		exit += 1;
		break;

		} while (exit == 0); // do while condition	
		std::cin.ignore();
		productName = nullptr; // prodName to nullptr
		delete[] productName; // delete the productName from memory
		return is; // return istream obj
	
	}

	// This query receives the address of an unmodifiable C-style null-terminated string and
	// returns true if the string is identical to the sku of the current object; false otherwise.
	bool Product::operator==(const char * addr) const
	{
		if (strcmp(prodSKU, addr) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// returns the cost times the amount of product on hand, if taxable we use cost() function else we use price() function, eitherway I cast these to a double
	double Product::total_cost() const
	{
		if (taxable == true) 
		{

			return static_cast<double>(prodQuantity * cost());
		}
		else
		{
			return static_cast<double>(prodQuantity * price());
		}
	}

	// This query returns the number of units of the product that are on hand.
	void Product::quantity(int prodHave)
	{
		prodQuantity = prodHave;
	}

	// This query returns true if the object is in a safe empty state; false otherwise.
	bool Product::isEmpty() const
	{
		if (prodUnit == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// returns the amount of product needed
	int Product::qtyNeeded() const
	{
		return prodNeeded;
	}

	// returns the amount on hand
	int Product::quantity() const
	{
		return prodQuantity;
	}

	// This query receives the address of a C-style null-terminated string
	// holding a product sku and returns true if the sku of the current object is greater than the string stored at the received address 
	bool Product::operator>(const char * productSKU) const
	{
		if (strcmp(productSKU, prodSKU) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// This modifier receives an integer identifying the number of units to be added to the Product and returns the updated number of units on hand. 
	// If the integer received is positive-valued, this function adds it to the quantity on hand. If the integer is negative-valued or zero, this function does nothing and returns the quantity on hand (without modification).
	int Product::operator+=(int numz)
	{
		if (numz > 0)
		{
			prodQuantity += numz;
			return prodQuantity;
		} 
		else // must be negative or zero valued
		{   
			return prodQuantity;
		}
	}

	// adds a double to the total cost (using the total_cost() function) then returns that double
	double operator+=(double &dbl, const iProduct &prod) 
	{
		dbl += prod.total_cost();
		return dbl;
	}

	// A function which returns the price of the object depending on the taxable status
	double Product::cost() const
	{
		if (taxable == true)
		{
			double val = priceBeforeTax + priceBeforeTax * tax_rate;
			return val;
		}
		else
		{
			return priceBeforeTax;
		}
	}

	// Returns the products SKU
	const char* Product::sku() const
	{
		return prodSKU;
	}

	// Returns the products unit variable
	const char * Product::unit() const
	{
		return prodUnit;
	}

	// Returns taxable variable which is either true or false, the taxable variable is defaulted to true in the seven argument constructor
	// the taxable variable holds the status of wether or not an object will have taxes applied to it
	bool Product::taxed() const
	{
		return taxable;
	}
	
	// returns PriceBeforeTax variable, incidentally as the variable says this price is without tax and generally called for such situations
	double Product::price() const
	{
		return priceBeforeTax;
	}

	// insertion operator
	std::ostream& operator<<(std::ostream& ostr, const iProduct& mf) 
	{
		return mf.write(ostr, true);
	}

	// extraction operator
	std::istream& operator>>(std::istream& istr, iProduct& mf) 
	{
		return mf.read(istr);
	}

	// This query receives an unmodifiable reference to a Product object and returns true if the name of the current object is greater than the name of the referenced Product object 
	// (according to how the string comparison functions define ‘greater than’); false otherwise.
	bool Product::operator>(const iProduct &other) const
	{
		if (strcmp(this->myName, other.name()) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// A fuction which allows Perishable.cpp to check if the errO object is clear through its isClear function
	bool Product::isClear() const
	{
		return errO.isClear();

	}

	// A fuction which allows Perishable.cpp to use the errO object. Sets the message then returns it promptly
	bool Product::message(const char* message)
	{
		errO.message(message);
		return errO.message();
	}

} 
//Product.cpp end