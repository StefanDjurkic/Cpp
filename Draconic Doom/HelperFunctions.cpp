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
FileName: HelperFunctions.cpp
Author:  Stefan Djurkic
Contact: <https://www.StefanDjurkic.com> || stefandjurkic@gmail.com
Copyright 2018 Stefan Djurkic
See readme for more information on this program
/******************************************************************************************/
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "Constants.h"
#include "HelperFunctions.h"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using namespace Constants;
namespace Helper_Functions
{
	/*We recieve a string related to something the player might want confirmation about usually around choices and request input for confirmation*/
	int Confirmation(string spec)
	{
		string confirm; /*Declare a string object confirm*/
		while (confirm != "Y" && confirm != "y" && confirm != "N"  && confirm != "n") /*while confirm is not yes or no loop*/
		{
			cout << "You chose " << spec << ". Do you accept?" << endl; /*display our inputed string*/
			cout << "Press the 'y' key to confirm or the 'n' key to restart: "; /*inform the user about what key to press*/
			cin >> confirm; /*request input*/
			cin.ignore(2000, '\n'); /*ignore extra lines*/
		}
		cout << endl; /*create a new line for appearances sake*/
		if (confirm == "N" || confirm == "n") /*if confirm is no we return 0*/
		{
			return 0;
		}
		return exitFunction; /*if confirm was yes then we return exitfunction 66 indicating that the user is accepting of his choice*/
	}

	/*We use this function to make a basic border with some specified string*/
	void MakeBorder(int txtLength, const char * spacing)
	{
		cout << "|"; // Border opening

					 // For the specified length (txtLength) we cout the character (spacing)
		for (int i = 0; i < txtLength; i++)
		{
			cout << spacing;
		}
		cout << "|" << endl; // Border closing
	}
	
	/*This overloaded makeborder function creates some text surrounded by a border*/
	void MakeBorder(int txtLength, const char * innerSpacing, const char * outerSpacing, const char * phrase, int lineAmt)
	{
		int originTxt = txtLength; // We keep the original txtLength as it will be modified

		// If line amount is greater or equal to one we call the overloaded function MakeBorder with two arguments to print a border
		if (lineAmt >= 1)
		{
			MakeBorder(originTxt, outerSpacing); // "outerSpacing" variable here dictates what border we want to appear
		}
		cout << "|"; // Border opening
		int testPhrase = strlen(phrase); // We measure the length of our phrase here and store it in int testPhrase
		txtLength -= testPhrase; // We find how much space we desire by subtracting the length of testPhrase
		testPhrase = txtLength / 2; // testPhrase is divided by two since we want some space before and after our phrase input

									// Much like the two argument MakeBorder function we cout the specified spacing (innerSpacing) for an amount txtLength
		for (int i = 0; i < txtLength; i++)
		{
			// If i is equivalent to testPhrase (which means we have reached the halfway point of our txtLength) we cout the phrase
			if (i == testPhrase)
			{
				cout << phrase;
			}
			cout << innerSpacing;
		}
		cout << "|" << endl; // End of the border and start of a newline

		// Below we check if lineAmt is greater than one to print an aditional border, if lineAmt is -1 we only print a border here and not at the start of the function
		if (lineAmt > 1 || lineAmt == -1)
		{
			MakeBorder(originTxt, outerSpacing);
		}
	}
	
	/*This function takes in two integer paramaters as a range and returns a random value within the range*/
	int RandomGen(int range1, int range2)
	{
		std::random_device rd; /*declare our random generator rd for our seed*/
		std::mt19937 gen(rd()); /*seeded mersenne twister engine with rd variable*/
		std::uniform_int_distribution<> uniDis(range1, range2); /*create a distrubution based on our ranges*/
		int rValue = uniDis(gen); /*initialize our rValue for return to our declared dist*/
		return rValue; /*return our value*/
	}

	std::string RandomGen(std::vector<std::string> nameVect)
	{
		int rValue = RandomGen(0, nameVect.size() - 1);
		return nameVect[rValue];
	}

	/*Cin check ensures the player inputs some integer without causing problems for the output */
	int CinCheck()
	{
		int rPick = 0; /*initialize rpick to 0*/
		cin >> rPick; /*we request input into rpick*/
		/*while and if we are failing to input correctly or the player has attempted to input value 66 we loop the following*/
		while (cin.fail() || rPick == exitFunction) 
		{
			cin.clear(); /*clear input*/
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); /*ignore excess*/
			rPick = 0; /*reset rPick to zero to be returned which should indicate that something has failed to another routine*/
		}
		return rPick; /*return our value*/
	}

	// this function shows formated text based on the position of the player and returns the corresponding string
	std::string ShowBanner(int storyPoint)
	{
		std::string areaResult = "Village"; // set some default value just incase
		// this is our game title we will likely place this in some other function later on
		if (storyPoint == 0) 
		{
			/*We use makeborder function to create some ascii art*/
			MakeBorder(80, " ", "=","      ___   ___   ___   ___   ___   ___   ___   ___   ", 1);
			MakeBorder(80, " ", "", "     ( D ) ( R ) ( A ) ( C ) ( O ) ( N ) ( I ) ( C )  ", 0);
			MakeBorder(80, " ", "-","    \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/", 0);
			MakeBorder(80, " ", "=","      ___   ___   ___   ___    ", 0);
			MakeBorder(80, " ", "", "     ( D ) ( O ) ( O ) ( M )   ", 0);
			MakeBorder(80, " ", "-"," \\_/   \\_/   \\_/   \\_/", -1);		
			MakeBorder(80, " ", "=", "Draconic Foreordination    ", -1);
			areaResult = "Title"; /*string to be returned*/
		}
		// so we check the storypoint integer and based on these index display some ascii art
		if (storyPoint == 1) {
			MakeBorder(80, " ", "=", ".::         .::      .::  .::                                ", 1);
			MakeBorder(80, " ", "", " .::       .::   .:  .::  .::                                ", 0);
			MakeBorder(80, " ", "", "  .::     .::        .::  .::    .::        .::       .::    ", 0);
			MakeBorder(80, " ", "", "   .::   .::    .::  .::  .::  .::  .::   .::  .::  .:   .:: ", 0);
			MakeBorder(80, " ", "", "    .:: .::     .::  .::  .:: .::   .::  .::   .:: .::::: .::", 0);
			MakeBorder(80, " ", "", "     .::::      .::  .::  .:: .::   .::   .::  .:: .:        ", 0);
			MakeBorder(80, " ", "", "      .::       .:: .::: .:::   .:: .:::      .::    .::::   ", 0);
			MakeBorder(80, " ", "=", "                                           .::               ", -1);
			areaResult = "Village";
		}
		if (storyPoint == 2) {
			MakeBorder(80, " ", "=", "    .::                         .::    .::           ", 1);
			MakeBorder(80, " ", "", " .::   .::                      .::    .::           ", 0);
			MakeBorder(80, " ", "", ".::           .::      .::::  .:.: .:  .::    .::    ", 0);
			MakeBorder(80, " ", "", ".::         .::  .::  .::       .::    .::  .:   .:: ", 0);
			MakeBorder(80, " ", "", ".::        .::   .::    .:::    .::    .:: .::::: .::", 0);
			MakeBorder(80, " ", "", " .::   .:: .::   .::      .::   .::    .:: .:        ", 0);
			MakeBorder(80, " ", "=", "   .::::     .:: .::: .:: .::    .::  .:::   .::::   ", -1);
			areaResult = "Castle";
		}
		if (storyPoint == 3) {
			MakeBorder(80, " ", "=", "    .::          .::            ", 1);
			MakeBorder(80, " ", "", " .::   .::  .:   .::            ", 0);
			MakeBorder(80, " ", "", ".::            .:.: .: .::   .::", 0);
			MakeBorder(80, " ", "", ".::        .::   .::    .:: .:: ", 0);
			MakeBorder(80, " ", "", ".::        .::   .::      .:::  ", 0);
			MakeBorder(80, " ", "", " .::   .:: .::   .::       .::  ", 0);
			MakeBorder(80, " ", "=", "   .::::   .::    .::     .::   ", 0);
			MakeBorder(80, " ", "=", "                        .::     ", -1);
			areaResult = "City";
		}
		if (storyPoint == 4) {
			MakeBorder(80, " ", "=", ".:::::                                                                 ", 1);
			MakeBorder(80, " ", "", ".::   .::                                                               ", 0);
			MakeBorder(80, " ", "", ".::    .:: .::  .:: .:: .::      .::       .::        .::     .:: .::   ", 0);
			MakeBorder(80, " ", "", ".::    .:: .::  .::  .::  .::  .::  .::  .:   .::   .::  .::   .::  .:: ", 0);
			MakeBorder(80, " ", "", ".::    .:: .::  .::  .::  .:: .::   .:: .::::: .:: .::    .::  .::  .:: ", 0);
			MakeBorder(80, " ", "", ".::   .::  .::  .::  .::  .::  .::  .:: .:          .::  .::   .::  .:: ", 0);
			MakeBorder(80, " ", "", ".:::::       .::.:: .:::  .::      .::    .::::       .::     .:::  .::", 0);
			MakeBorder(80, " ", "=", "                                .::                                    ", -1);
			areaResult = "Dungeon";
		}
		if (storyPoint == 5) {
			MakeBorder(80, " ", "=", "    .::                                     ", 1);
			MakeBorder(80, " ", "", " .::   .::                                  ", 0);
			MakeBorder(80, " ", "", ".::           .::     .::     .::    .::    ", 0);
			MakeBorder(80, " ", "", ".::         .::  .::   .::   .::   .:   .:: ", 0);
			MakeBorder(80, " ", "", ".::        .::   .::    .:: .::   .::::: .::", 0);
			MakeBorder(80, " ", "", " .::   .:: .::   .::     .:.::    .:        ", 0);
			MakeBorder(80, " ", "=", "   .::::     .:: .:::     .::       .::::   ", -1);
			areaResult = "Cave";
		}
		if (storyPoint == 6) {
			MakeBorder(80, " ", "=", ".::::::::                                        .::  ", 1);
			MakeBorder(80, " ", "", ".::                                              .::  ", 0);
			MakeBorder(80, " ", "", ".::          .::     .: .:::    .::      .:::: .:.: .:", 0);
			MakeBorder(80, " ", "", ".::::::    .::  .::   .::     .:   .::  .::      .::  ", 0);
			MakeBorder(80, " ", "", ".::       .::    .::  .::    .::::: .::   .:::   .::  ", 0);
			MakeBorder(80, " ", "", ".::        .::  .::   .::    .:             .::  .::  ", 0);
			MakeBorder(80, " ", "=", ".::          .::     .:::      .::::    .:: .::   .:: ", -1);
			areaResult = "Forest";
		}
		if (storyPoint == 7) {
			MakeBorder(80, " ", "=", ".::     .::      .::  .::", 1);
			MakeBorder(80, " ", "", ".::     .::  .:  .::  .::", 0);
			MakeBorder(80, " ", "", ".::     .::      .::  .::", 0);
			MakeBorder(80, " ", "", ".:::::::.:: .::  .::  .::", 0);
			MakeBorder(80, " ", "", ".::     .:: .::  .::  .::", 0);
			MakeBorder(80, " ", "", ".::     .:: .::  .::  .::", 0);
			MakeBorder(80, " ", "=", ".::     .:: .:: .::: .:::", -1);
			areaResult = "Hill";
		}
		if (storyPoint == 8) {
			MakeBorder(80, " ", "=", ".::       .::                                 .::                           ", 1);
			MakeBorder(80, " ", "", ".: .::   .:::                                 .::               .:          ", 0);
			MakeBorder(80, " ", "", ".:: .:: . .::    .::     .::  .:: .:: .::   .:.: .:    .::         .:: .::  ", 0);
			MakeBorder(80, " ", "", ".::  .::  .::  .::  .::  .::  .::  .::  .::   .::    .::  .::  .::  .::  .::", 0);
			MakeBorder(80, " ", "", ".::   .:  .:: .::    .:: .::  .::  .::  .::   .::   .::   .::  .::  .::  .::", 0);
			MakeBorder(80, " ", "", ".::       .::  .::  .::  .::  .::  .::  .::   .::   .::   .::  .::  .::  .::", 0);
			MakeBorder(80, " ", "=", ".::       .::    .::       .::.:: .:::  .::    .::    .:: .::: .:: .:::  .::", -1);
			areaResult = "Mountain";
		}
		if (storyPoint == 9) {
			MakeBorder(80, " ", "=", ".:::::::                                      ", 1);
			MakeBorder(80, " ", "", ".::    .::    .:                              ", 0);
			MakeBorder(80, " ", "", ".::    .::       .::     .::    .::    .: .:::", 0);
			MakeBorder(80, " ", "", ".: .::       .::  .::   .::   .:   .::  .::   ", 0);
			MakeBorder(80, " ", "", ".::  .::     .::   .:: .::   .::::: .:: .::   ", 0);
			MakeBorder(80, " ", "", ".::    .::   .::    .:.::    .:         .::   ", 0);
			MakeBorder(80, " ", "=", ".::      .:: .::     .::       .::::   .:::   ", -1);
			areaResult = "River";
		}
		if (storyPoint == 10) {
			MakeBorder(80, " ", "=", "    .::                                    .::  ", 1);
			MakeBorder(80, " ", "", " .::   .::                                 .::  ", 0);
			MakeBorder(80, " ", "", ".::           .::        .::      .::::  .:.: .:", 0);
			MakeBorder(80, " ", "", ".::         .::  .::   .::  .::  .::       .::  ", 0);
			MakeBorder(80, " ", "", ".::        .::    .:: .::   .::    .:::    .::  ", 0);
			MakeBorder(80, " ", "", " .::   .::  .::  .::  .::   .::      .::   .::  ", 0);
			MakeBorder(80, " ", "=", "   .::::      .::       .:: .::: .:: .::    .:: ", -1);
			areaResult = "Coast";
		}
		if (storyPoint == 11) {
			MakeBorder(80, " ", "=", ".:::::::    .::                         ", 1);
			MakeBorder(80, " ", "", ".::    .::  .::             .:          ", 0);
			MakeBorder(80, " ", "", ".::    .::  .::    .::         .:: .::  ", 0);
			MakeBorder(80, " ", "", ".:::::::    .::  .::  .::  .::  .::  .::", 0);
			MakeBorder(80, " ", "", ".::         .:: .::   .::  .::  .::  .::", 0);
			MakeBorder(80, " ", "", ".::         .:: .::   .::  .::  .::  .::", 0);
			MakeBorder(80, " ", "=", ".::        .:::  .:: .:::  .:: .:::  .::", -1);
			areaResult = "Plain";
		}
		if (storyPoint == 12) {
			MakeBorder(80, " ", "=", " .:: ::                                  ", 1);
			MakeBorder(80, " ", "", ".::    .::           .:                   ", 0);
			MakeBorder(80, " ", "", " .::       .: .::       .: .:::    .::    ", 0);
			MakeBorder(80, " ", "", "   .::     .:  .::  .::  .::     .:   .:: ", 0);
			MakeBorder(80, " ", "", "      .::  .:   .:: .::  .::    .::::: .::", 0);
			MakeBorder(80, " ", "", ".::    .:: .:: .::  .::  .::    .:        ", 0);
			MakeBorder(80, " ", "=", "  .:: ::   .::      .:: .:::      .::::   ", 0);
			MakeBorder(80, " ", "=", "           .::                            ", -1);

			areaResult = "Spire";
		}
		if (storyPoint == 13) {
			MakeBorder(80, " ", "=", " ____  __    _____  _____  ____     ___  ____  ____  ____  ____ ", 1);
			MakeBorder(80, " ", "", "(  _ \\(  )  (  _  )(  _  )(  _ \\   / __)(  _ \\(_  _)(  _ \\( ___)", 0);
			MakeBorder(80, " ", "", " ) _ < )(__  )(_)(  )(_)(  )(_) )  \\__ \\ )___/ _)(_  )   / )__) ", 0);
			MakeBorder(80, " ", "=", "(____/(____)(_____)(_____)(____/   (___/(__)  (____)(_)\\_)(____)", -1);
			areaResult = "BloodSpire";
		}
		return areaResult; // return a string based on index
	}
}

