/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<iostream>
#include<string>
#include "Round.h"
#include "SaveFile.h"

using namespace std;

class Tournament
{
public:
	// The Constructor and Destructor of the class
	Tournament();
	~Tournament();

	// Creates a new game or finds a save game
	void tournamentGame();

	// Check if the tournament is over
	void isTournamentOver(int m, int n, int s);

	// Display the Score for the tournmanet
	void displayTournamentScores(int m, int n);

	// Display the tournament winner
	void tournamentWinner(int m, int n, int s);
	
private:
	// the variable to holds the points to end the tournament
	int tournamentPoints;
	
	// the number of the round
	int roundnumber;
	
	// holds the points of the player
	int humanOverallScore;
	int computerOverallScore;

	// Checks if the tournament is over
	bool tournamentOver;

	// Name of the file
	string fileName;
	
	// Pointer to the SaveFile class
	SaveFile * file;

	// Gets the decision of the user of what game they would like to play
	char getTournamentChoice();

	// Ask the user for the tournament points
	int askPoints();

	// Input the file name where the round will be saved
	string getFileName();

	// Input a file name of the round that was saved
	string inputFileName();
};

