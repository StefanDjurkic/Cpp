// File: ErrorState.h
// Name: Stefan Djurkic
// Email: stefandjurkic@gmail.com
// Date:  04/02/2018

#ifndef _ERRORSTATE_

#define _ERRORSTATE_

#include <iostream>

namespace AMA 
{
	class ErrorState
	{
		char* errMsg;
	
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;
		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message()const;
		void copyMsg(const char* message);
		friend std::ostream& operator<<(std::ostream& ostr, const ErrorState&);
	
	};

}
#endif
