/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1, Longana Game                        *
* Class : Organization of Programming Language             *
* Date : 10-17-2017                                        *
************************************************************/

#pragma once

#include<vector>
#include<utility> 
#include"Player.h"
#include"Layout.h"
#include"Hand.h"

using namespace std;

class Computer :public Player{
public:
	// The Constructor of the class
	Computer();

	// Constructor if the round is started from within a file, this will set the computerHand
	Computer(vector<pair<int, int>> * v) { computerHand = v; };
	
	// Destructor of the class
	~Computer();

	// This function will choose what action the computer plays
	void play(Layout * board, Stock * boneyard);

	// Chooses the best tile to play
	void chooseTile(Layout * board, Stock * boneyard);

	// Passes a turn if there is no possible tile to play
	void passTurn(Layout * board, Stock * boneyard);

private:
	// A vector of pairs that will hold the possible tiles to play
	vector<pair<int, int>> computerTemp;

	// Search for the possible tile the computer can play
	void searchForTile(Layout * board, pair<int, int> &t, pair<int, int> &s);
};