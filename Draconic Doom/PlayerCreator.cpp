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
FileName: PlayerCreator.cpp
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#include <iterator>
#include "TempHelpers.h"
#include "PlayerCreator.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using namespace Constants;
using namespace Helper_Functions;
using namespace Temp_Helpers;
namespace Draconic_Doom
{
	/*Default constructor*/
	PlayerCreator::PlayerCreator()
	{
	}

	/*Four argument constructor which takes in vectors to be used in character creation*/
	PlayerCreator::PlayerCreator(const vector <string> speciesName,  const vector <vector<int> > speciesStat, const vector <string> className, const vector <vector<int> >  classStat)
	{
	speciesStatVect = speciesStat;
	speciesNameVect = speciesName;
	classStatVect = classStat;
	classNameVect = className;
	}

	// Used to display a vector which contains stats for a job or species
	string PlayerCreator::DisplayNameStats(int mapType, int txtAmt, bool multiples, int vectPosition,  vector <string> nName,  vector <vector<int> >  statvect)
	{
		string statMsg = "(1) Tell me about attributes \n"; // setup a string to output a message
		string negCheck = ""; // initialize a string to display a negative
		int whiteSpace = 0; /*initialize an integer to create some white space*/
		int nameLen = 0; // initialize namelen to 0 
		int vecSize = statvect.size(); // set vectsize to our initial statvect size
	    int originalPos = vectPosition; // We initialize and store in vecSize the vector size of statVect, and we store the original value of vectorPosition in originalPos
		if (multiples == false) { vecSize = vectPosition + 1; statMsg = ""; }; // if multiples is false we are told to display one portion of the vector so we set vecSize to the vectPosition + 1
		cout << statMsg;//output the statmsg string
		// if maptype == 1 we use the output info function to display species vector
		if (mapType == 1) {OutputInfo(speciesDescript, nName[vectPosition]); }
		// if maptype == 2 we output job vector and its stats
		if (mapType == 2) { OutputInfo(jobDescripts, nName[vectPosition]); }
		// 
		for (vectPosition; vectPosition < vecSize; vectPosition++)
		{
			cout << "(" << vectPosition + 2 << ") "; // create a menu number with the right position
			nameLen = labs(txtAmt - nName[vectPosition].length()); // get subtract text amount by the string length
			cout << nName[vectPosition] << " stats: "; // display the name followed by stats: string
			/*if vectposition is greater than 9 we set whitespace to 1 which will deduct from namelen below*/
			if ((vectPosition + 2) > 9) { whiteSpace = 1; }; 
			for (int x = 0; x < nameLen - whiteSpace; x++) 
			{ 
				cout << " "; // create spacing based on namelen
			} 
			for (int j = 0; j < statNames.size(); ++j)
			{
				if (statvect[vectPosition][j] >= 0) { negCheck = "+"; } // if the value is not negative we append a + sign
				else { negCheck = ""; }; //else if negative leave the string alone as a negative sign will be displayed regardless
				cout << statNames[j] << ":" << negCheck << statvect[vectPosition][j] << " || "; // out the stats name and value
			}
			cout << endl; // create a newline
		}
		return nName[originalPos]; // return our vector with its original position
		};

	// create a name for the player
	void PlayerCreator::NamePlayer(Player & obj)
	{
		char str[32]; // intialize str length to 32
		int check = 0; // initialize check variable to 0
		while (check == 0) // while our check variable is 0
		{
			cout << "What should people call me?" << endl; // output message
			cout << "Name: "; // output message
			cin.get(str, 32, '\n'); //catch input into str
			cin.ignore(2000, '\n'); // ignore new lines
			check = Confirmation(str); // we use confirmation to ensure the player is sure of his pick and return to check
		}
		cout << "Alright I'm '" << str << "'!" << endl; // confirmation output
		obj.SetName(str); // set the objects name to the string
	}

	// ShowSpecies() function gives the player basic information about species stats
	int PlayerCreator::ShowSpecies()
	{
		MakeBorder(111, " ", "-", "Pick your species", 1); // create a border message 
		// create a border message
		MakeBorder(111, " ", "-", "The type of species you pick affects your attributes, each attribute plays in how you interact with the world", 2);
		// display the species vector through displaynamestats
		std::string trivialString = DisplayNameStats(0, 14, true, 0, speciesNameVect, speciesStatVect);
		cout << " **Press a corresponding numerical key to pick a species for your character, press 1 for some information on stats**" << endl;
		return CinCheck(); // return an integer through cincheck
	}
	//showclasses shows information to the player about jobs available to him
	int PlayerCreator::ShowClasses()
	{
		MakeBorder(111, " ", "-", "Pick your Class", 1);
		MakeBorder(111, " ", "-", "Each class has a specific set of spells, though, all classes can learn various spells and attack moves", 2);
		std::string trivialString = DisplayNameStats(0, 15, true, 0, classNameVect, classStatVect); // display job vectors
		cout << " **Press a corresponding numerical key to pick a class for your character, press 1 for some information on stats**" << endl;
		return CinCheck(); // return an integer through cincheck
	}

	// create a player
	Player PlayerCreator::CreatePlayer(Player & obj)
	{
		int satisfied; // declare a satisfied variable for a do while loop
		do {
			NamePlayer(obj); // name the player through namePlayer function
			int pJob = ClassAndSpecies(1); // set into pjob the result of job choice
			// set the job to our vectors based on pjob position
			obj.SetJob(classNameVect[pJob], TransformVector2d(pJob, classStatVect));
			int pSpecies = ClassAndSpecies(0); // return a species index
			obj.SetSpecies(speciesNameVect[pSpecies], TransformVector2d(pSpecies, speciesStatVect));
			obj.EntityInfo(); // display info for the player
			satisfied = Confirmation("the above"); // request confirmation from the player
		} while (satisfied == 0); // while satisfied is zero loop
		return obj; // return the modified object
	}

	/*Sets the players class and species through the cS parameter, 0 for classes and 1 for species */
	int PlayerCreator::ClassAndSpecies(int cS)
	{
		string myChoice = " "; /*Initialize myChoice string object to some empty space*/ 
		int picks = 0; /*variable which dictates the switch from species or class, initialized to zero*/ 
		int pOrigin = 0;  /*Since we input into picks, this variable stores some original value of picks (since picks undergoes changes) */ 
		while (picks != exitFunction) /*While picks does not equate to exitFunction(which equates to 66) perform the following*/
		{
			picks = 0; /*Reset picks to zero*/
			while (picks == 0 || picks == 1) /*Since picks is reset to zero we run this loop at least once*/
			{
				/*we equate picks to the return value of either showclasses or showspecies functions depending on cS parameter */
				if (picks == 0) { picks = (cS != 0) ? ShowClasses() : ShowSpecies(); };
				if (picks == 1) { AttributeInfo(); picks = 0; }; /*if picks 1 was chosen that means we want to display some info and reset this loop, picks = 0*/
			}
			/*If the previous loop was exited without issue let pOrigin equate to picks subtracted by 2, we do this to correspond with the menu that doesn't line up with our index  */
			pOrigin = picks-2; 
			/*Below we have two if statements corresponding to the cS parameter*/
			if (cS == 0 && picks <= speciesStatVect.size()+1) /*This condition ensures we do not attempt to input into a vector a position out of bounds*/
				{
				/**/
					if ((picks = Confirmation(myChoice = DisplayNameStats(1, 8, false, pOrigin, speciesNameVect, speciesStatVect))) == exitFunction) {return pOrigin; };
				} 
			if (cS == 1 && picks <= classStatVect.size()+1) /*This condition ensures we do not attempt to input into a vector a position out of bounds*/
				{
					if ((picks = Confirmation(myChoice = DisplayNameStats(2, 8, false, pOrigin, classNameVect, classStatVect))) == exitFunction) { return pOrigin; };
				}
		}  // While picks != exitFunction we loop the switch
	}


	// AttributeInfo() function gives the player basic information about attributes, returns nothing
	int PlayerCreator::AttributeInfo()
	{
		MakeBorder(114, " ", "-", "Constitution affects your hit points (Con)", 1);
		MakeBorder(114, " ", "-", "Strength affects how much you can carry and your physical damage (Str)", 0);
		MakeBorder(114, " ", "-", "Intelligence affects your magical damage (Int)", 0);
		MakeBorder(114, " ", "-", "Defense and Magic Defense reduce the amount of damage you take from their respective damage types (Def, Mag Def)", 0);
		MakeBorder(114, " ", "-", "Agility affects turn order and certain weapons (Agi)", 0);
		MakeBorder(114, " ", "-", "Charisma affects certain spells, trade value, and how people view your character (Char)", 0);
		MakeBorder(114, " ", "-", "*Note* If your charisma is below 3, doing good deeds will improve it up to 3", -1);
		cout << "\nPlease press enter to continue\n";
		getchar();
		getchar();
		return 0;
	}
	// output a map of vector strings to be displayed
	void PlayerCreator::OutputInfo(std::map<string, std::vector<string>> mapType, string pattern)
	{
		for (const auto& pair : mapType) //auto loop
		{
			for (std::size_t i = 0; i < pair.second.size(); ++i) 
			{
				// if the first position of the vector matches our pattern
				if (pair.first == pattern) 
				{
					std::cout << pair.second[i] << std::endl; // display the messages within the vector
				}
			}
		}	
	}
} //