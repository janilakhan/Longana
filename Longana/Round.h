/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include "Stock.h"
#include "Hand.h"
#include "LayoutView.h"
#include "Layout.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"


using namespace std;

class Round
{
public:
	// The Constructor and Destructor of the class
	Round(int n);

	// Constructor if the round was saved
	Round(int n, deque<pair<int, int>> * v, vector<pair<int, int>> * w, vector<pair<int,int>> * x, vector<pair<int,int>> * y, bool player, int current, bool pass);

	// Destructor of the class
	~Round();

	// Play a round
	void playRound();

	// Alternate between players
	void alternatePlayer(int player);

	// Check if the round is over
	void isRoundOver(vector<pair<int,int>> * x, vector<pair<int,int>> * w, vector<pair<int,int>> * z);

	//Calculate points for each player
	void roundScore(vector<pair<int,int>> *x, vector<pair<int,int>>*w, vector<pair<int,int>>*z);

	// Display the winner of the round 
	void displayRoundScore(int n, int m);

	// Pointer to the Layout Class
	Layout * getBoard() { return board; };

	// Pointer to the Human class
	Player * getHuman() { return humanPlayer; };

	// Pointer to the Computer class
	Player * getComputer() { return computerPlayer; };

	// Pointer to the Stock class
	Stock * getBoneyard() { return boneyard; };

	// Get the Human Score of the Round 
	const int getHumanRoundScore() { return humanRoundScore; }

	// Get the Computer Score of the Round
	const int getComputerRoundScore() { return computerRoundScore; }

	// Get the value of roundOver
	bool isRoundDone() { return roundOver; };

	// Get the currentPlayer
	int getCurrent() { return currentPlayer; };

private:
	// Symbolic Constants
	const int firstDraw = 8;
	const int draw = 1;	

	// Class Variables that will be needed in this class 
	int num;
	int engine;

	int currentPlayer;
	bool firstPlayer;
	
	bool roundOver;

	int humanRoundScore;
	int computerRoundScore;

	// Stores the layout of the board and the display
	Layout * board;
	LayoutView boardView;

	// Store the Stock
	Stock * boneyard;

	// Hand variable
	Hand * userHand;	
	
	// Stores the human and computer players
	Player * humanPlayer;
	Player * computerPlayer;
	
	// Figure out the engine number
	int engineNumber(int num);

	// Search for the engine
	bool searchEngine(vector<pair<int,int>> *v, int num);

	// Choose who is the first player 
	void findFirstPlayer(vector<pair<int, int>> * v, vector<pair<int, int>> *w);
};

