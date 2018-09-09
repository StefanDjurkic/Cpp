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
FileName: Creature.cpp
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#include <string>
#include <iostream> 
#include "Entity.h"
#include "Creature.h"
namespace Draconic_Doom
{
	// Default constructor for Creature object
	Creature::Creature()
	{
	}

	// Greeting function for the creature
	void Creature::EntityGreeting()
	{
		EntityInfo();
	}

	// Set the creatures job and name
	void Creature::SetCreature(int difficulty, std::string cName, std::string cJob )
	{
		name = cName;
		job = cJob;
	}

}