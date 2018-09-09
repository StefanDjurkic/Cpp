/******************************************************************************************\
This file is part of SUPER DRAGON.

SUPER DRAGON is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SUPER DRAGON is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SUPER DRAGON.  If not, see <https://www.gnu.org/licenses/>.

/******************************************************************************************/

/******************************************************************************************\
SUPER DRAGON, Version 0.0.1
FileName: GameLoop.cpp
Purpose: Handles the game loop and main point of entry
Author:  Stefan Djurkic
Contact: <https://StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for the index or more information on this program
/******************************************************************************************/

//headers
#include <iostream>
#include "Creator.h"
//
using namespace Draconic_Doom;
//Game Loop
int main()
{
	// Create a creator object
	Creator c;
	// show intro banner
	ShowBanner(0);
	// run the loop
	c.DraconicDoomLoop(0);
	std::getchar();
	return 0;
}
