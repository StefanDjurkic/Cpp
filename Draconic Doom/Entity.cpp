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
FileName: Entity.cpp
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#include <random>
#include "HelperFunctions.h"
#include "TempHelpers.h"
#include "Entity.h"
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace Helper_Functions;
using namespace Temp_Helpers;
namespace Draconic_Doom
{
	// 0 argument default constructor
	Entity::Entity()
	{
		level = 0;
		name = "";
		job = "";
		species = "";
		health =  0;
		intelligence = 0;
		strength = 0;
		attack = 0;
		defense = 0;
		magicDefense = 0;
		agility = 0;
		charisma = 0;
		magicUser = 0;
	}
	
	// Displays the stats of an entity
	void Entity::EntityInfo()
	{
		string mUser = "Magic user: false";
		if (magicUser != 0) { mUser = "Magic user: true"; };
		cout << "A " << job << " " << species << " named: " << name << endl;
		cout << "Health: " << health << " || " << mUser << endl;
		cout << "Strength: " << strength << " || " << "Intelligence: " << intelligence << endl;
		cout << "Defense: " << defense << " || " << "Magic Defense: " << magicDefense << endl;
		cout << "Agility: " << agility << " || " << "Charisma: " << charisma << endl << endl;
	}

	// Using the setInfo function we change the class char
	void Entity::SetJob(string nameVect, vector <int> statVect)
	{
		SetClassName(nameVect);
		SetStats(statVect);
		magicUser = statVect[7];
	}

	/*Function that sets the jobname to a provided string*/
	void Entity::SetClassName(string jName)
	{
		job = jName;
	}

	// Using the setInfo function we change the species char 
	void Entity::SetSpecies(string nameVect, vector<int> statVect)
	{
		SetSpeciesName(nameVect);
		SetStats(statVect);
	}
	
	/*Function that sets the species name to a provided string*/
	void Entity::SetSpeciesName(string sName)
	{
		species = sName;
	}

	// Using the setInfo function we change the name char 
	void Entity::SetName(string str)
	{
		name = str;
	}

	/*Simply add desired stats to the base stats, used for leveling, buffs, or setting class/species stats for the player*/ 
	void Entity::SetStats(vector<int> vect)
	{	/*Considering turning stats into a vector or map but this meets our needs at the moment*/
		health += vect[0];
		strength += vect[1];
		intelligence += vect[2];
		defense += vect[3];
		magicDefense += vect[4];
		agility += vect[5];
		charisma += vect[6];
	}

	/*Function that adds to the entities level*/
	void Entity::SetLevel(int lvl)
	{
		level += lvl;
	}

	/*Bool that returns a true or false health is greater than 0, meaning the Entity is still alive*/ 
	bool Entity::HpCheck() const
	{
		return (health > 0) ? true : false;
	}

	/*This function returns */
	int Entity::Damage()
	{
		int attacks = 0; /*Initialize attacks to zero*/
		/*If we exceed 5 through our random number function the attack misses, we set attack to 0 and alert the player with a message*/
		if (RandomGen(0, 10) > 5) { cout << name << " Misses!" << endl; attacks = 0; } 
		else
		{/*If we don't exceed 5 through our random number function the attack succeeds, we set attack to the greatest of agi, str, or int*/
			attacks = GreatestNum(agility, strength, intelligence);
			cout << name << " deals " << attacks << " damage!" << endl; /*Display damage amount*/
		}
		return attacks; /*Return the attack value*/
	}	

	/*Function which returns the entity health*/
	int Entity::HpReturn()
	{
	 return health; 
	}

	/*Overloaded operator -, used to deduct attack (int parameter) from health*/
	void Entity::operator-(int hAttack)
	{
		health -= hAttack; /*deduct attack (int parameter) from health*/
		cout << health << "HP remains" << endl; /*Let the player know how much health is left*/
	}
}