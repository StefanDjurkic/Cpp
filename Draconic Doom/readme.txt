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
FileName: readme
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
/******************************************************************************************/

**This game is a C++ text adventure as well as a passion project of mine, and it is currently in alpha.**

Section A: 
Some essential information if you need to understand the code:

1. The Creator.cpp/.h module is what brings all the functions together and creates the mechanics and game loop

2. This game compares the interaction between a player object and a creature object whom both inherit from an Entity object (Entity.cpp/.h)

3. TempHelpers.h is a file with templated functions used to assist many other functions in the game (much like HelperFunctions.cpp/./h does)

4. The player object is setup/created through another object called PlayerCreator, which is called by our Creator module

5. Currently our areas and species files use indices to tell the function the size it needs to loop through, which is something we should change
--------------------------------------------------------------------------------------------------------------------------------

Section B:
How the game works so far and explaining the game loop:

1. Assuming we are starting a new game, a player is created based on input and predefined vectors.

2. We create (and save to file) a map and set the players position on that map based on a random range. We also create a "BloodSpire" on the map which houses a Dragon boss.

3. We load from the file we just created a map to be used by the game

4. The actual loop begins, our first step is to ask the player in which direction they want to go and then update his position

5. Given player position in relation to our map an encounter is generated

6. A list of monsters are loaded in from file to be battled by the player until their hp reaches zero

7. The player chooses to attack or flee from however many monsters have been loaded in, the final monster is always a boss

8. If the player is still alive we save their information, else if the player has died we delete the map, player save, and then end the game/program

9. Should the program have ended whilst the player was still alive, if the program is restarted the player and map are loaded and creation is skipped
--------------------------------------------------------------------------------------------------------------------------------

Section C:
TODO LIST: 9/9/2018
This list contains the next steps for the project:
1. Revamp our save/load system to be more efficient
2. Skill system
3. Inventory system
4. Enhance battle system taking in consideration of skills and items
5. Main menu
6. Create interaction between the player and a location (towns,cities, etc...)
7. Flesh out the final boss and his BloodSpire location
8. Update the list as we go
--------------------------------------------------------------------------------------------------------------------------------
