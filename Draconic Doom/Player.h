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
FileName: Player.h
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#ifndef _Player_H_ 
#define _Player_H_
#include <vector>
#include "TempHelpers.h"
#include "Entity.h"
namespace Draconic_Doom
{
	class Player : public Entity // player is a child of Entity
	{		
	protected:
		int x; // x position
		int y; // y position
	public:
		// default constructor
		Player();
		// Greeting function
		void EntityGreeting(); 
		// choice function
		int bChoice();
		// Save the player strings
		vector<std::string> SaveStrings();
		// Save the players stats
		vector <int> SaveMyStats();
		// return the player x coordinate
		int GetX();
		// return the player y coordinate
		int GetY();
		// set the player position
		void SetPosition(vector<int> pos);
		// load the player and all his values then set them
		void LoadPlayer(std::string File);
		// set all the stats of the player
		void LoadAll(vector<std::string> nameVect, vector<int> statVect);
	};
}
#endif //end of header
