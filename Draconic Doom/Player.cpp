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
FileName: Player.cpp
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#include <iostream> 
#include <string>
#include "Player.h"
using std::cin;
using std::cout;
using std::endl;
using namespace Temp_Helpers;
namespace Draconic_Doom
{
	// Default constructor for player
	Player::Player() : Entity()
	{
		x = 2;
		y = 2;
	}

	// Player greeting *
	void Player::EntityGreeting()
	{
	}

	// return a choice *
	int Player::bChoice()
	{
		return 0;
	}
	
	// Return a vector of the players strings to be saved by another function
	vector <std::string> Player::SaveStrings()
	{
		vector <std::string> myStrings; // declare a string vector
		myStrings.push_back(name); // add into the string vector our name
		myStrings.push_back(species); // add to vector the species name
		myStrings.push_back(job); // add into vector the job name 
		return myStrings; // return the vector
	}

	// Return a stat vector of all player integers
	vector <int> Player::SaveMyStats()
	{
		vector <int> myStats; // create the 1d int vector
		myStats.push_back(health); //From here to the return value we push back all our player stast
		myStats.push_back(strength);
		myStats.push_back(intelligence);
		myStats.push_back(defense);
		myStats.push_back(magicDefense);
		myStats.push_back(agility);
		myStats.push_back(charisma);
		myStats.push_back(magicUser);
		myStats.push_back(level);
		myStats.push_back(x);
		myStats.push_back(y);
		return myStats; // return our vector
	}

	// Get the players x coordinates
	int Player::GetX()
	{
		return x;
	}

	// Get the players y coordinates
	int Player::GetY()
	{
		return y;
	}

	// Set the players y and x coordinates to a vector
	void Player::SetPosition(vector <int> pos)
	{
		x = pos[0];
		y = pos[1];
	}

	// Load the player
	void Player::LoadPlayer(std::string File)
	{
		cout << "LOADING" << endl; // debug
		std::ifstream file(File); // create the ifstream obj file
		std::string named; // declare a string object called named
		int target; // integer value to store payers integers
		vector <std::string> playerNames; // vector of strings for the players string values
		vector <int> playerStats;// vector of ints for the players stats
		//int size = 0; // initialize size to zero not needed?
		if (file.is_open()) // check if the file is open
		{
			for (int i = 0; i < 11; i++) 
			{
				file >> target; //input into target some integer
				playerStats.push_back(target); // add into vector target variable
			}
			file.ignore(1000, '\n'); // skip a line
			for (int j = 0; j < 3; j++)
			{
				file >> named; // input into named some string
				playerNames.push_back(named); // add into playernames named variables
			}
			file.close(); // close the file since we are done with it
		}
		int statSize = playerStats.size(); // get the playerStats size now that we have it filled
		vector <int> position; // create a vector for player position
		position.push_back(playerStats[statSize-2]); // add in the second to last vector position of player stats
		position.push_back(playerStats[statSize-1]); // add in the final vector position of playerstats
		SetPosition(position); // set position to our vector we just created
		LoadAll(playerNames, playerStats); // set stats to our string and int vectors
	}

	// function that takes in two vectors and sets the players stats with them
	void Player::LoadAll(vector <std::string> nameVect, vector <int> statVect)
	{
		SetName(nameVect[0]); // set our name to the first position
		SetSpeciesName(nameVect[1]); // set our speciesname to the second position
		SetClassName(nameVect[2]); // set our job nae to the third position
		SetStats(statVect); // set stats to the stat vector
		SetLevel(statVect[8]); // set leve to the eigth position
	}
}