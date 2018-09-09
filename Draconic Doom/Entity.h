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
FileName: Entity.h
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#ifndef _Entity_H_ 
#define _Entity_H_
#include <vector>
namespace Draconic_Doom
{
	class Entity
	{
	protected:
		/*  Variables  */
		std::string name; // Name of the entity
		std::string species; // The species of the entity
		std::string job; // the job/class of the entity
		int level; // the level of the entity
		int health; // Value which indicates how close the character is to death
		int strength; // Physical damage attribute
		int intelligence; // MAgic damage attribute
		int defense; // A mitigation stat
		int magicDefense; // A mitigation stat for magic
		int agility; // Value which dictates turn order
		int charisma; // modifier value for spells and trading
		int magicUser; // checks if the user is a magicuser or not
		int attack; // Value which is applied against an opposing characters health and defense
	public:
       	/*  Constructors */
		//
		//Default constructor
		Entity(); //B2_h /		
		// Provides the player with information about a character such as stats
		virtual void EntityInfo(); 
		// Sets the entity job
		virtual void SetJob(std::string nameVect, std::vector<int> statVect);
		// Set the entity job name
		virtual void SetClassName(std::string jName);
		// set the species
		virtual void SetSpecies(std::string nameVect, std::vector<int> statVect);
		// set the species name
		virtual void SetSpeciesName(std::string sName);
		// set the entity name
		virtual void SetName(std::string str);
		// set entity stats
		virtual void SetStats(std::vector<int> vect);
		// set entity level
		virtual void SetLevel(int lvl);
		// Checks the characters HP for a value less than or equal to zero
		virtual bool HpCheck() const; 
		// returns a calculated damage integer
		virtual int Damage();
		// returns hp
		virtual int HpReturn();
		// overloaded operator that subtracts attack from hp
		virtual void operator-(int hAttack);
	};	
}
#endif //end of header
