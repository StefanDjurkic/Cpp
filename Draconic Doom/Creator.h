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
FileName: Creator.h
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#ifndef _Creator_H_ 
#define _Creator_H_
#include <vector>
#include <map>
#include "PlayerCreator.h"
#include "Creature.h"
#include "SaveLoad.h"
using std::vector;
using std::string;
namespace Draconic_Doom
{
	class Creator
	{
	protected:

		// 1d vector of strings for job names (here job just means class in the RPG sense, C++ already has classes!)
		const vector <string> jobNames = { "Warrior", "Barbarian", "Monk", "Rogue", "Ranger", "Paladin", "Druid", "Wizard", "Warlock", "Swordmage" };
		
		// 2d vector with ten int vectors, each matching their respective job
		const vector <vector< int> > jobStats
		{
			{
				{ 3,3,0,5,0,2,0, 0 },  // Warrior:   | Con +3 ||| Str +3 ||| Int +0 ||| Def +5 ||| Mag Def +0 ||| Agi +2 ||| Char +0 |
				{ 4,4,-2,0,0,3,-2,0 }, // Barbarian: | Con +4 ||| Str +4 ||| Int -2 ||| Def +0 ||| Mag Def +0 ||| Agi +3 ||| Char -2 |
				{ 2,0,0,3,3,3,2,1 },   // Monk:      | Con +2 ||| Str +0 ||| Int +0 ||| Def +3 ||| Mag Def +3 ||| Agi +3 ||| Char +2 |
				{ 0,1,1,1,1,4,0,0 },   // Rogue:     | Con +0 ||| Str +1 ||| Int +1 ||| Def +1 ||| Mag Def +1 ||| Agi +4 ||| Char +0 |
				{ 1,1,0,0,0,5,1,0 },   // Ranger:    | Con +1 ||| Str +1 ||| Int +0 ||| Def +0 ||| Mag Def +0 ||| Agi +5 ||| Char +1 |
				{ 3,2,0,5,2,0,3,1 },   // Paladin:   | Con +3 ||| Str +2 ||| Int +0 ||| Def +5 ||| Mag Def +2 ||| Agi +0 ||| Char +3 |
				{ 0,2,4,2,2,1,4,1 },   // Druid:     | Con +0 ||| Str +2 ||| Int +4 ||| Def +2 ||| Mag Def +2 ||| Agi +1 ||| Char +4 |
				{ 0,0,6,0,4,0,1,1 },   // Wizard:    | Con +0 ||| Str +0 ||| Int +6 ||| Def +0 ||| Mag Def +4 ||| Agi +0 ||| Char +1 |
				{ 1,1,5,0,1,0,-1,1 },  // Warlock:   | Con +1 ||| Str +1 ||| Int +5 ||| Def +0 ||| Mag Def +1 ||| Agi +0 ||| Char -1 |
				{ 1,3,3,1,1,0,0,1 }	   // Swordmage: | Con +1 ||| Str +3 ||| Int +3 ||| Def +1 ||| Mag Def +1 ||| Agi +0 ||| Char +0 |
			}
		};

		// 1d vector of strings for species names
		const std::vector <std::string> speciesNames
		{
			"Human", "Halfling", "Dwarf", "Gnome", "Elf", "Half-Elf", "Orc", "Half-Orc", "Lizardman", "Kobold",
			"Goblin", "Dragonborn", "Giant", "Half-Giant", "Minotaur", "Elephantman", "Tigerman"
		};
		
		// 2d vector with 17 int vectors, each matching the respective stats of its species
		const vector <vector< int> > speciesStats
		{
			{
		{ 1,1,1,1,1,1,4 },     // Human:      | Con +1 ||| Str +1 ||| Int +1 ||| Def +1 ||| Mag Def +1 ||| Agi +1 ||| Char +4 |
		{ 0,0,1,0,3,4,3 },     // Halfling:   | Con +0 ||| Str +0 ||| Int +1 ||| Def +0 ||| Mag Def +3 ||| Agi +4 ||| Char +3 |
		{ 3,1,0,4,1,-3,2 },    // Dwarf:      | Con +3 ||| Str +1 ||| Int +0 ||| Def +4 ||| Mag Def +1 ||| Agi -3 ||| Char +2 |
		{ -1,0,3,-2,4,3,3 },   // Gnome:      | Con -1 ||| Str +0 ||| Int +3 ||| Def -2 ||| Mag Def +4 ||| Agi +3 ||| Char +3 |
		{ 0,0,4,-3,3,1,0 },    // Elf:        | Con +0 ||| Str +0 ||| Int +4 ||| Def -3 ||| Mag Def +3 ||| Agi +1 ||| Char +0 |
		{ 1,0,2,1,2,1,-1 },    // Half-Elf:   | Con +1 ||| Str +0 ||| Int +2 ||| Def +1 ||| Mag Def +2 ||| Agi +1 ||| Char -1 |
		{ 3,3,-3,3,-2,-4,-6 }, // Orc:        | Con +3 ||| Str +3 ||| Int -3 ||| Def +3 ||| Mag Def -2 ||| Agi -4 ||| Char -6 |
		{ 2,2,-1,2,-1,0,-3 },  // Half-Orc:   | Con +2 ||| Str +2 ||| Int -1 ||| Def +2 ||| Mag Def -1 ||| Agi +0 ||| Char -3 |
		{ 1,1,-2,5,-2,2,-3 },  // LizardMan:  | Con +1 ||| Str +1 ||| Int -2 ||| Def +5 ||| Mag Def -2 ||| Agi +2 ||| Char -3 |
		{ -1,-1,1,-1,3,6,-6 }, // Kobold:     | Con -1 ||| Str -1 ||| Int +1 ||| Def -1 ||| Mag Def +3 ||| Agi +6 ||| Char -6 |
		{ -1,1,0,-1,2,4,-7 },  // Goblin:     | Con -1 ||| Str +1 ||| Int +0 ||| Def -1 ||| Mag Def +2 ||| Agi +4 ||| Char -7 |
		{ 2,1,2,3,0,-2,-2 },   // Dragonborn: | Con +2 ||| Str +1 ||| Int +2 ||| Def +3 ||| Mag Def +0 ||| Agi -2 ||| Char -2 |	 
		{ 5,5,-3,5,-5,-9,-7 }, // Giant:      | Con +5 ||| Str +5 ||| Int -3 ||| Def +5 ||| Mag Def -5 ||| Agi -9 ||| Char -7 |
		{ 3,3,-2,2,-3,-3,-3 }, // Half-Giant: | Con +3 ||| Str +3 ||| Int -2 ||| Def +2 ||| Mag Def -3 ||| Agi -3 ||| Char -3 |
		{ 2,4,-4,2,-5,-1,-8 }, // Minotaur:   | Con +2 ||| Str +4 ||| Int -4 ||| Def +2 ||| Mag Def -5 ||| Agi -1 ||| Char -8 |
		{ 4,2,0,1,1,-4,-4 },   // ElephantMan:| Con +4 ||| Str +2 ||| Int +0 ||| Def +1 ||| Mag Def +1 ||| Agi -4 ||| Char -4 |
		{ 1,2,0,0,0,8,-5 }     // TigerMan:   | Con +1 ||| Str +2 ||| Int +0 ||| Def +0 ||| Mag Def +0 ||| Agi +8 ||| Char -5 |
			}
		};

		/*We declare a 2d vector of ints named DragonMap for later use when we store the game map*/
		vector <vector< int> > DragonMap;

		/*A 1d vector of strings with names for use with a random name generator, this will later be put into a text file*/
		const std::vector <std::string> randomNames
		{
			"Remi", "Jen", "Popo", "Bebis", "Doomdog", "Apoc", "DooDoo", "Kartis", "Charlie", "Gob",
			"Coco", "Shinji", "Jin", "Boon", "Bongkong", "Bella", "Red",
		};
	public:
		/*Creator default constructor*/
		Creator() = default;
		/*Function used to request input from a player and return an integer based on the input (used for battle mechanics)*/
		int BattleChoice();
		/*Function that decides if the player can run away*/
		int Flee();
		/*The games battle engine*/
		Player BattleMechanic(Player a, Creature b);
		/*Create and return a player object*/
		Player CreatePlayerObject(Player & Player1);
		/*Uses this objects functions to create a game loop*/
		void DraconicDoomLoop(int exits);
		/*/*Based on a map vector and the players position, we move in one direction(cardinal direction) through player input and return the vector*/
		vector<int> TraverseDirection(vector<vector<int>> mapVect, Player pp1);
		/*This function returns where the player is on the provided mapVector based on the players position*/
		int TraverseMap(std::vector<std::vector<int>> mapVec, Player pp1);
		/*Based on a returned integer indicating the position on our showbanner (function) index, we create an encounter*/
		Player Encounter(Player pp1, int area);
		/*Create a creature*/
		Creature CreateCreatureObject(Creature & cR1, std::string name, std::string bossName, bool boss);
		/*Create a map provided a map name*/
		vector <int> CreateMap(const char * mapFile);
	};
}
#endif
