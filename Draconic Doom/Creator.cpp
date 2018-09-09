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
FileName: Creator.cpp
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#include "TempHelpers.h"
#include "HelperFunctions.h"
#include "Creator.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using namespace Constants;
using namespace Helper_Functions;
using namespace Temp_Helpers;
using namespace Save_Load;
namespace Draconic_Doom
{
	/*We pass in a player object and modify it using the PlayerCreator object once inside, here we pass in predefined vectors from which the player will choose*/
	Player Creator::CreatePlayerObject(Player & Player1)
	{	
		PlayerCreator pCreate(speciesNames,speciesStats,jobNames,jobStats); /*Pass the vectors into the PlayerCreator 4 argument constructor*/
		Player1 = pCreate.CreatePlayer(Player1); /*We ask the player to make choices based on the above vectors and create an object based on those choices*/
		return Player1; /*We return the player with the new parameters*/
	}

	/*This is our game loop, this function makes use of every module directly or indirectly to create and manipulate the game world*/
	void Creator::DraconicDoomLoop(int exits)
	{
		/*Initializing Variables*/
		int exit = 0; // exit variable
		const char * gameMap = "SdMap.txt"; /*Declare the games map file*/
		const char * playerSave = "PlayerSave.txt";  /*Declare the players save file*/
		Player p1; /*Create the default player object*/
		vector <vector<int> > mapVector; /*Declare the map vector which holds the coordinates for the game*/
		std::ifstream fin2d(playerSave); /*Create an ifstream object fin2d pointing to the player save file*/
		
		/*Determine player information*/
		if (fin2d)  /*If the player save file exists, then we know we can simply load the data otherwise we start from scratch*/
		{
		/*Loading the game*/
		mapVector = Load2dVector(gameMap);
		p1.LoadPlayer(playerSave);
		cout << "Welcome back, Here is where you left off" << endl; /*Let the player know the game has loaded*/
		p1.EntityInfo(); /*Display player info*/
		}
		else 
		{
		/*First time set up*/
		p1 = CreatePlayerObject(p1); // Player setup happens here through the CreatePlayerObject function
		p1.SetPosition(CreateMap(gameMap)); /*We create a map and at the same time set the players position vector to a random position within that map*/
		mapVector = Load2dVector(gameMap); // We load the mapfile into a vector 
		}
		fin2d.close(); // close that damn file!
		/*Enter the game loop*/
		while (exit == 0) /*If this condition is not met then we end the game*/
		{
			p1.SetPosition(TraverseDirection(mapVector,p1)); /*We set the player position through TraverseDirection function based on players current position and the map*/
			p1 = Encounter(p1,TraverseMap(mapVector, p1)); /*Begin an encounter based on the players position*/	
			if (p1.HpReturn() <= 0) { remove(playerSave); remove(gameMap); exit = 1; }/*If the player has died delete save files and exit the loop*/
			else
			{
				Save1dVector(playerSave, p1.SaveMyStats(), 1); /*Save the players stats, and delete any existing savefile*/
				Save1dVector(playerSave, p1.SaveStrings(), 0); /*Save the players string attributes(name,class,species)*/
			}
		}
		cout << "GAME OVER" << endl; /*Display a game over indicator*/
	}

	/*Based on a map vector and the players position, we move in one direction(cardinal direction) through player input and return the vector*/
	vector <int> Creator::TraverseDirection(vector <vector<int> > mapVect, Player pp1)
	{
		int x = pp1.GetX(); /*Return the players x position and store into int x*/
		int y = pp1.GetY();  /*Return the players y position and store into int y*/
		vector <int> vectorMove(2); /* we declare a vector to be returned of size 2 */
		int dest = 0; /*variable standing for destination inputed by the user below*/ 
		while (dest == 0) /*while destination is zero we loop (for which it is defaulted to)*/ 
		{	
			vectorMove[0] = x; /*store into this vectors 0 position the players current x, ensures vectorMove returns to an initial position*/ 
			vectorMove[1] = y; /*store into this vectors 1 position the players current y*/ 
			while (dest < 1 || dest > 4) /*if destination exceeds our parameters we loop until an input corresponds*/ 
			{
				cout << "Please pick a destination, (1)-North, (2)-South, (3)-East, (4)-West" << endl << endl; /*output parameters to user*/ 
				dest = CinCheck(); /*get an input from the cincheck function (ensures the user doesn't exit early or cause an overflow)*/ 
			}
			/*per cardinal direction, we get a confirmation from the player with the confirmation function as to their pick (1-4)*/ 
			if (dest == 1) { vectorMove[0] += 1; dest = Confirmation("North");  };
			if (dest == 2) { vectorMove[0] -= 1; dest = Confirmation("South");  };
			if (dest == 3) { vectorMove[1] += 1; dest = Confirmation("East");   };
			if (dest == 4) { vectorMove[1] -= 1; dest = Confirmation("West"); };
			if ((vectorMove[0] >= 10 || vectorMove[0] <= 0) || (vectorMove[1] >=10 || vectorMove[1] <= 0)) /*Here we check if the player has gone out of bounds*/
			{ 
				if (dest != 0) /*If dest is already 0 we don't have to equate it to zero or submit a message about bounds*/
				{
					/*Let the player know he exceeded the bounds and set dest to zero so re-enter the loop*/
					dest = 0; 
					cout << "*** Edge of the map. I should go elsewhere ***" << endl << endl;
				}
			}; 
		} /*if either cincheck or confirmation returned a zero we loop back around*/ 		
		return vectorMove; /*return the vector to update the players position*/ 
	}

	/*This function returns where the player is on the provided mapVector based on the players position*/
	int Creator::TraverseMap(std::vector <std::vector <int> > mapVec, Player pp1)
	{
		int x = pp1.GetX(); /*Return the players x position and store into int x*/
		int y = pp1.GetY(); /*Return the players y position and store into int y*/
		return mapVec[x][y];/*Return the map vector based on players position*/
	}

	/*Based on a returned integer indicating the position on our showbanner (function) index, we create an encounter (restricted to a battle for now)*/
	Player Creator::Encounter(Player pp1, int area)
	{
		string myArea = ShowBanner(area); // myArea equates to the area the player is currently in
		string test = LoadString("areas.txt", myArea); //we store into test the areas monsters to be fought
		vector <string> Enemy = LoadEncounter("species.txt", test);	// based on test retrieve a random encounter based on the area and test
		int eSize = Enemy.size(); //we store the vector size to be used in a forloop 
		bool cBoss = false; // is the first fight a boss?
		int i = 0;
		while (i < eSize - 1 && pp1.HpReturn() > 0) /*We loop for the enemy.size()-1 and as long as the player is alive*/
		{	
			if (i == eSize - 2) { cBoss = true; } // if i is equivalent to the final vector position then we have a boss
			Creature cR; // we create a defaulted creature
			cR = CreateCreatureObject(cR, Enemy[i + 1], Enemy[0], cBoss); //we pass a creature, first creature index, and the class for which a boss would use as well as the boss bool
			cout << "You are fighting: " << endl;
			cR.EntityInfo(); // display this creatures information
			pp1 = BattleMechanic(pp1, cR); // we create the battle
			i++;
		}
		return pp1; //we return the player
	}

	/*Modify a creature object, we pass in a name and a job name as well as a bool which indicates if the creature is a boss*/
	Creature Creator::CreateCreatureObject(Creature & cR1, string sName, string jName, bool boss)
	{
		int randomSpecies = RandomGen(0, 16); /*Declare a random species index using our random number function*/
		int randomClass = RandomGen(0, 9); /*Declare a random class index using our random number function*/
		string creatureJob = jobNames[randomClass]; /*Set a string based on our class vector */
		if (boss == true) { creatureJob = jName; }; // Is this creature a boss type? If so set it to the jName string passed in to change it to the bosses job
		cR1.SetName(randomNames[RandomGen(0,5)]); // give this creature a random name based on our name vector
		cR1.SetJob(creatureJob, TransformVector2d(randomClass,jobStats)); /*Set the creatures job*/
		cR1.SetSpecies(sName, TransformVector2d(randomSpecies, speciesStats)); /*Set the creatures species*/
		return cR1; /*Return the modified creature*/
	}

	/*Create a 2d vector map, save it into a txt file and return a random position vector within this map to be used by a player*/
	vector <int> Creator::CreateMap(const char * mapFile)
	{
		int x = RandomGen(1, 9); /*set our x variable (for position) to a random number 1-9, since our map borders are 0 and 10*/
		int y = RandomGen(1, 9); /*set our y variable (for position) to a random number 1-9*/
		std::vector <std::vector <int> > tempVect(11, std::vector <int>(11, 0)); /*Declare a vector of vectors and initialize it to zero*/
		vector <int> initialPosition(2,2); /*Declare a vector of 2 and fill if with 2's, we pick this number to move away from the map outer bounds just as a precaution*/
			for (int i = 0; i < 11; i++)  /*We loop through the size of our tempVect*/
			{
				for (int j = 0; j < 11; j++) /*Inner loop to the size of tempvect*/
				{
					if (i == 0 || i == 10) { tempVect[i][j] = -1; } /*If we happen to be on 0 or 10 (map outer bounds), we set the area to -1*/
					else
					{
						tempVect[i][j] = RandomGen(1, 12); /*else if the position is within bounds we input a random number 1-12 based on showbanner index*/
					}
					tempVect[i][0] = -1; /*Specifically for the left side we set the element to -1*/
					tempVect[i][10] = -1; /*Specifically for the right side we set the element to -1*/
				}
			}
			tempVect[x][y] = 13; // we generate the blood spire (position 13 in the story index)
			while (x == (initialPosition[0] = RandomGen(1, 9))) { x = RandomGen(1, 9); }; /*We set the x of the player to be a random number 1-9 so long as it doesnt == x (blood spire location)*/
			while (y == (initialPosition[1] = RandomGen(1, 9))) { y = RandomGen(1, 9); }; /*We set the y of the player to be a random number 1-9 so long as it doesnt == y */
			DragonMap = tempVect; /*Our predefined vector equates to tempVect*/
			Save2dVector(mapFile, DragonMap); /*We save our mapfile*/
			return initialPosition; /*We return initialPosition vector to the player for his positional coordinates*/
	}

	/*Returns an integer based on player input*/
	int Creator::BattleChoice()
	{
		int options = 0; // initialize options variable to zero, it holds player choice
		int returnOpt = 0; /*initialize the return value to zero*/
		while (options != exitFunction) // while options doesnt equate to an exit value 66
		{
			cout << "Pick an option" << endl; // output message
			cout << "(1) Attack, (2) Skill, (3) Check Items, (4) Check my stats, (5) Flee" << endl; // let the player know of his options
			options = CinCheck(); // options equals cincheck()
			// based on 1,2,3 request confirmation
			if (options == 1)
			{
				returnOpt = options; /*store into returnOpt the options original value for later use*/
				/*we equate options to the return value of confirmation which returns 0 for no in which case we loop or exitfunction 66 for yes which lets us exit */
				options = Confirmation("to attack"); 
			}
			else
				if (options == 2)
				{
					returnOpt = options;
					options = Confirmation("to use a skill");
				}
				else
					if (options == 3)
					{
						returnOpt = options;
						options = Confirmation("to check your items");
					}
					else
						if (options == 4)
						{
							returnOpt = options;
							options = Confirmation("to check your stats");
						}
						else
							if (options == 5)
							{
								returnOpt = options;
								options = Confirmation("to flee");
							}
							else
							{
								options = 0;
							}
		}
		return returnOpt;
	}

	/*Function which allows the player to flee based on chance*/
	int Creator::Flee()
	{
		int cmp = RandomGen(0, 10); // initialize cmp for comparison to a random number between 0,10
		if (cmp > 5) { return 1; }; /*If cmp is above 5 we return one indicating a success*/
		return 0; /*otherwise we return 0 indicating a failure*/
	}

	Player Creator::BattleMechanic(Player a, Creature b)
	{
		int comp = 0; /*initialize to zero comp variable which is used to check if the player can flee*/
		int round = 1; /*initilize round to 1 to keep track of how many rounds have passed*/
		int myChoice = 0; /*initialize a mychoice variable to 0 for player input and switch*/
		do
		{
			cout << "Turn number: " << round << ". Your enemy has: " << b.HpReturn() << " HP left" << endl; /*Display turn number and enemy HP*/
			if (a.HpReturn() > 0)
			{
				myChoice = BattleChoice(); /*input into myChoice an integer based on player choice via battlechoice function*/
			}
			else
			{
				myChoice = 6; /*go to option 6 and let the player know he is dead*/
			}
			
			switch (myChoice) /*Run functions based on myChoice variable*/
			{
			case 1:
				/*Basic attack*/
				if (a.HpReturn() > 0)
				{
					b - a.Damage(); /*Player (a) attacks b*/
				}
				if (b.HpReturn() > 0)
				{
					a - b.Damage(); /*b attacks a*/
				}
				round++;
				break;

			case 2:
				/*Skills*/
				cout << "Which skill should I use?" << endl;
				/*Function goes here*/
				break;

			case 3:
				/*Output a message and output items*/
				cout << "Here are my items:" << endl;
				/*Function goes here*/
				break;
				
			case 4:
				/*Output a message and output stats*/
				cout << "My stats are as follows:" << endl;
				a.EntityInfo();
				break;

			case 5:
				/*Does the player run away?*/
				if ((comp = Flee()) == 1) { cout << "You ran away!"; return a; }
				else
				{
					cout << "You failed to run away!" << endl;
					a - b.Damage();
					round++;
				}
				break;
			case 6:
				cout << "You died" << endl;
				break;
			default:
				break;
			}
		} while (b.HpReturn() > 0 && a.HpReturn() > 0); /*Do this loop as long as either entity hp is above 0*/
		return a; /*Return player object*/
	}
}