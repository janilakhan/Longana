/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<iostream>
#include<utility>
#include<vector>
#include "Layout.h"
#include "Hand.h"
#include "Stock.h"

using namespace std;

class Player
{
public:
	// The Constructor and Destructor of the class
	Player();
	~Player();
	
	// A virtual function where all the plays will be made
	virtual void play(Layout * board, Stock * boneyard) { cout << "BASE" << endl; };

	// A virtual function which will allow the Computer and Human to choose a tile to place on the board
	virtual void chooseTile(Layout * board, Stock * boneyard) { cout << "BASE" << endl; };

	// A virtul function which will aloow both the Computer and Human to pass
	virtual void passTurn(Stock * boneyard) { cout << "BASE" << endl; };

	// Add a Tile to the right side of the board
	void addToRight(Layout * board, Stock * boneyard, vector<pair<int,int>> * v, pair<int, int> & t);

	// Add a tile to the left side of the board
	void addToLeft(Layout * board, Stock * boneyard, vector<pair<int,int>> * v, pair<int, int> & t);

	// Check if a tile that is chosen can be placed on the right side of the board 
	bool isTileLegalRight(pair<int, int> & t, pair<int, int> & s);

	// Check if a tile that is chosen can be placed on the left side of the board
	bool isTileLegalLeft(pair<int, int> & t, pair<int, int> & s);
	
	// Check if a tile is is double
	bool isDouble(pair<int,int> & t);

	// Count the pips of a tile
	int countTilePips(pair<int, int> & r);

	// Returns a pointer to the Human Hand
	vector<pair<int, int>> * getHumanHand() { return humanHand; };

	// Returns a pointer to the Computer Hand
	vector<pair<int, int>> * getComputerHand() { return computerHand; };

protected:
	// Symbolic Constant to draw a tile 
	const int draw = 1;

	// Vectors of pairs that hold the hand of a user
	vector<pair<int, int>>* humanHand;
	vector<pair<int, int>>* computerHand;
	
	// A pointer to the hand class
	Hand * userHand;
};

