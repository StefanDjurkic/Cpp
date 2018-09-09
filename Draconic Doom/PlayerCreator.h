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
FileName: PlayerCreator.h
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#ifndef _PlayerCreator_H_ 
#define _PlayerCreator_H_
#include <map>
#include <vector>
#include "Player.h"
namespace Draconic_Doom
{
	class PlayerCreator
	{
	protected:
		// declare a species stat vector
		 std::vector <std::vector<int> >  speciesStatVect; 
		// declare a species name vector
		 std::vector <std::string>  speciesNameVect;
		 // declare a job stats vector
		 std::vector <std::vector<int> >  classStatVect;
		 // declare a job name vector
		 std::vector <std::string> classNameVect;
		// declare a vector with stat abreviations
		 std::vector <std::string> statNames
		 {
			 "Con", "Str", "Int", "Def", "Mag Def", "Agi", "Char",
		 };
		 // initialize a jobdescripts map of vector strings for job descriptions
		 std::map<std::string, std::vector <std::string> > jobDescripts =
		 {
			 { "Warrior",{
			 "The Warrior is a Strength user with balanced defensive and offensive physical skills"
		 } },

		 { "Barbarian",{
			 "Barbarians are strength users with offensive focused physical skills"
		 } },

		 { "Monk",{
			 "Monks are strength/charisma users with defensive focused skills"
		 } },

		 { "Rogue",{
			 "A rogue is an agility/strength user focused on evasion and poisons"
		 } },

		 { "Ranger",{
			 "Rangers are agility users focused on ranged attacks"
		 } },

		 { "Paladin",{
			 "A paladin is a charisma/strength user focused on self healing and smiting undead"
		 } },

		 { "Druid",{
			 "Druids are charisma/strength users with shapeshifting spells"
		 } },

		 { "Wizard",{
			 "Wizards are intelligence users with a broad range of spells"
		 } },

		 { "Warlock",{
			 "Warlocks are intelligence users focused on offensive magic"
		 } },

		 { "Swordmage",{
			 "Swordmages are strength/intelligence users that use magic to enhance their physical ability"
		 } },
		 };
		 // initialize a species description vector with a map of vector strings
		 std::map<std::string, std::vector <std::string> > speciesDescript =
		 {
			 { "Human",{
			 "Average in most ways, humans are the dominant species in this world and benefit from a good reputation"
		 } },

		 { "Halfling",{
			 "Halflings are distantly related to and half the size of a human,",
			 "they are generally unnoticed due to their simple lives and nimble abilities"
		 } },

		 { "Dwarf",{
			 "A sub-species of humans, dwarves are under 5 feet tall, and live long lives in the mountains",
			 "Dwarves are a hardy group whom tend to stick/consort with their own kind"
		 } },

		 { "Gnome",{
			 "Little is known about how gnomes came to be, though, some say they are a product of dwarves and goblins",
			 "They are intelligent, quick, around 3 feet tall, and somewhat fragile"
		 } },

		 { "Elf",{
			 "Elves are rumored to originate form another realm, they have pointy ears, and live long lives",
			 "They are highly intelligent and can sometimes come off as too blunt for their own good"
		 } },

		 { "Half-Elf",{
			 "Half-Elves are a rare product from human and elf, and at time seen as an abomination",
			 "They tend to be slightly more intelligent and slightly weaker than a human"
		 } },

		 { "Orc",{
			 "Orcs are a hated species in this world. Many claims are made about this species origin",
			 "Some say they are conjured from another realm or created from rotting matter" ,
			 "Orcs are a strong and hardy species, but usually lack intelligence and speed"
		 } },

		 { "Half-Orc",{
			 "Rarely documented, half-orcs are the product of a human and orc" ,
			 "They are a fraction less grotesque than an orc. People are still weary of this species",
			 "Half-Orcs possess less than average intelligence, and above average strength and constitution",
		 } },

		 { "Lizardman",{
			 "Lizardmen are an apparent humanoid evolution from reptiles",
			 "Described by scholars as an easily manipulated and ruthless species",
			 "The species is covered in hard scales and posseses slightly above average physical ability"
		 } },

		 { "Kobold",{
			 "Kobolds are tiny lizard like creatures",
			 "Legend says kobolds were once servants to dragons whom they are said to be related to" ,
			 "Physically speaking kobolds rely on speed rather than brute strength"
		 } },

		 { "Goblin",{
			 "Goblins are about 3 feet tall and said to be created by hobgoblins as a servant species",
			 "They are aggressive, quick, and ruthless" ,
			 "Over millenia a few goblins have attempted to integrate with human society with some success"
		 } },

		 { "Dragonborn",{
			 "Dragonborn are dragon humanoids which are born of dragon eggs" ,
			 "Along with kobolds they once served dragons but now are few and far between in numbers",
			 "This species is hardy, intelligent, and covered in scales which slows its movement somewhat"
		 } },

		 { "Giant",{
			 "As the name implies Giants tower most other species, they measure up to 10-12 feet in height",
			 "Known for their strength this species lacks intelligence and is extremely slow" ,
			 "Their size and appearance usually terrifies normal folk" } },

		 { "Half-Giant",{
			 "Half-giants are the product of humans and giants" ,
			 "Usually a few feet taller than your average human, half-giants tend to favor their giant heritage" ,
			 "Their size and appearance usually terrifies normal folk"
		 } },

		 { "Minotaur",{
			 "A humanoid bull--said to be conjured by warlocks",
			 "This species can often be found guarding dungeons, caves, or labyrinths",
			 "Its brutish apperance brings fear to the hearts of men"
		 } },

		 { "Elephantman",{
			 "It is said that long before humans dominated this world it was the elephantmen that ruled",
			 "While few remain the elephantmen still exist due to their extraordinary lifespans"
		 } },

		 { "Tigerman",{
			 "A ferocious tiger humanoid",
			 "Few men can see one and live to tell the tale"
		 } },
		 };	
	public:
		// default constructor
		PlayerCreator();
		// name the player
		void NamePlayer(Player & obj);
		// show species
		int ShowSpecies();
		// show classes
		int ShowClasses();
		// creates a player
		Player CreatePlayer(Player & obj);
		// 5 argument constructor
		PlayerCreator(std::vector<std::string> speciesName, std::vector<std::vector<int>> speciesStat, std::vector<std::string> className, std::vector<std::vector<int>> classStat);
		// display a job or species vector and its stats in a formated fashion
		std::string DisplayNameStats(int mapType, int txtAmt, bool multiples, int vectPosition, std::vector <std::string> nName, std::vector <std::vector<int> >  statvect);
		// function which handles player input to pick a class or species
		int ClassAndSpecies(int cS);
		// displayes attribute information
		int AttributeInfo();
		// outputs map information
		void OutputInfo(std::map<std::string, std::vector<std::string>> mapType, std::string pattern);
	};
}
#endif 
