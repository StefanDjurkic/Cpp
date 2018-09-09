/******************************************************************************************\
This file is part of Draconic Doom.

"Draconic Doom" is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"Draconic Doom" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with "Draconic Doom".  If not, see <https://www.gnu.org/licenses/>.

/******************************************************************************************/

/******************************************************************************************\
"Draconic Doom", Version 0.0.1
FileName: HelperFunctions.h
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#ifndef _HelperFUNCTIONS_H_ 
#define _HelperFUNCTION_H_

namespace Helper_Functions
{	
	//ShowBanner function
	//Displays a banner depending on the location or point in the story to denote a change in scenery
	//Using cout, displays ascii art/text
	std::string ShowBanner(int storyPoint);

	// Function which requests integer input from the user 
	int Confirmation(std::string spec);
	
	// Make border creates a border given given length and char
	void MakeBorder(int txtLength, const char * spacing);
	
	// Overloaded make border function with text input
	void MakeBorder(int txtLength, const char * innerSpacing, const char * outerSpacing, const char * phrase, int lineAmt);
	
	// Random number generator function
	int RandomGen(int range1, int range2);
	
	// Overloaded random number generator that returns a string from a name vector	
	std::string RandomGen(std::vector<std::string> nameVect);
	
	// Ensures the user inputs correct cin
	int CinCheck();
}
#endif //end of header
