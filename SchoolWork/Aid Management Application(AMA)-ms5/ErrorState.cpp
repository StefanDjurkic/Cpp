// File: ErrorState.cpp
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018

#include<iostream>
#include <string>
#include <cstring>
#include "ErrorState.h"

namespace AMA

	{

	ErrorState::ErrorState(const char* errorMessage)
		{		
		if (errorMessage == nullptr)
			{
				errMsg = nullptr;
			}
			else if (errorMessage[0] != '\0')
			{
				this->copyMsg(errorMessage);
			}
		}

		// avoids duplication
		void ErrorState::copyMsg(const char* message)
		{
			int strL = (strlen(message)) + 1;
			errMsg = new char[strL];
			strncpy(errMsg, message, strL);
		}

		// clear
		void ErrorState::clear()
		{
			delete[] errMsg;
			errMsg = nullptr;
		}
		//clear check
		bool ErrorState::isClear() const
		{			
			return (errMsg == nullptr) ? true : false;	
		}
		
		void ErrorState::message(const char* str)
		{
			clear();
			copyMsg(str);
		}

		const char * ErrorState::message() const
		{
			return errMsg;
		}

		std::ostream & operator<<(std::ostream& ostr, const ErrorState& str)
		{						
			if (str.errMsg != nullptr && str.errMsg[0] != '\0')
			{
				ostr << str.errMsg;
			}
			return ostr;		
		}
		// destructor
		ErrorState::~ErrorState()
		{
			clear();
		}
	}