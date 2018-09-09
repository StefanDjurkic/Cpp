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
FileName: SaveLoad.cpp
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include "SaveLoad.h"
#include "HelperFunctions.h"
using std::vector;
using namespace Helper_Functions;
	namespace Save_Load
	{
		/*This function accepts a filename and a 2dvector then saves the vector to the file*/
		void Save_Load::Save2dVector(const char * file2d, std::vector <std::vector <int> > saveVect2d)
		{
			remove(file2d); // delete the map file if one exists 
			std::ofstream fout(file2d, std::ios::out | std::ios::app);
			std::ifstream fout2d; // create a ifstream object (fin2d: file input 2d vector)	
			fout2d.open(file2d); // open the mapFile
			if (fout2d.is_open()) // if the mapfile is open
			{
				std::ofstream outfile(file2d); // not needed?
				for (int x = 0; x < saveVect2d.size(); x++)
				{
					for (int y = 0; y < saveVect2d.size(); y++)
					{
						fout << saveVect2d[x][y] << " "; // input into the file the vector
					}
					fout << "\n"; // make a new line
				}
				fout2d.close();
			}
		};

		/*Load a 2d vector from a file provided as a parameter and return a 2d vector*/
		vector <vector <int> > Save_Load::Load2dVector(const char * file2d)
		{
			std::ifstream fin2d(file2d); /*Declate an ifstream object and have it open the passed parameter*/
			vector <vector<int> > loadedVector; /*Declare a 2d vector to be returned*/
			if (fin2d) /*If the file is open perform the below*/
			{
			std::string vectorLine; /*Declare a string object named vectorLine */
			int value; /*Variable which is used to pass in a split from the vectorLine object*/
				while (std::getline(fin2d, vectorLine)) /*While we're getting a line into our string object vectorLine */
				{
					loadedVector.push_back(vector<int>());
					std::stringstream split(vectorLine); /*Break down the row into column values*/
					while (split >> value) /*While split is being inputed into value*/
					{
						/*We first address the object with back() which puts us at the last element in the vector, then push_back with value*/
						loadedVector.back().push_back(value); /*pass into our loadedVector the value variable*/
					}
				}
				fin2d.close();
			}
			return loadedVector; /*We return the newly built 2dvector*/
		};
	}