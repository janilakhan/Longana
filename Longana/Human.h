/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<vector>
#include<utility>
#include "Player.h"
#include "Hand.h"
#include "Layout.h"


using namespace std;

class Human : public Player {
public:
	// The Constructor of the class
	Human();

	// Constructor if the round is started from within a file, this will set the humanHand
	Human(vector<pair<int, int>> * w) { humanHand = w; };
	
	// Destructor of the class
	~Human();

	// This function will conduct the human's decisions
	void play(Layout * board, Stock * boneyard);

	// Allows the user to choose a tile from their hand
	void chooseTile(Layout * board, Stock * boneyard);

	// Allows the user to pass their turn
	void passTurn(Layout * board, Stock * boneyard);

	// Choose where to place a tile
	void chooseLocation(Layout * board, Stock * boneyard, pair<int,int> & t);

	// Helps the user make a decision of what to do
	void askForHelp(Layout * board);

private:
	// A vector of pairs which will tiles that the human can play
	vector<pair<int, int>> humanTemp;

	// Searches for possible tiles to play
	void searchForTile(Layout*board, pair<int, int>& t, pair<int, int> & s);
};