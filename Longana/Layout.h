/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<deque>
#include<vector>
#include<utility>
#include<iostream>

using namespace std;

class Layout
{
public:
	
	// Variables that will determine if a user passed or not
	bool humanPass;
	bool computerPass;	
	
	// The Constructor of the class
	Layout();

	// Constructor if the round is started from within a file, this will set the board
	Layout(deque<pair<int, int>> * v) { board = v; };
	
	// Destructor of the class
	~Layout();

	// Places the engine to the board
	void placeEngine(vector<pair<int, int>> * v, int engine);

	// Swap the pips of the tile
	void swapPips(pair<int,int> * x);

	// Places a tile on the left side of the board
	void placeTileLeft(pair<int, int>&t) { board->push_front(t); };

	// Places a tile on the right side of the board
	void placeTileRight(pair<int, int> & t) { board->push_back(t); };

	// Returns a boolean value determining if the computer passed or not
	bool didComputerPass();

	// Returns a boolean value determining if the human passed or not
	bool didHumanPass();

	// Returns a pointer to the board
	deque<pair<int, int>>* getBoard() { return board; };

	// Returns the first tile on the left side of the board
	pair<int, int> returnTopTile() { return board->front(); };

	// Returns the first tile on the right side of the board
	pair<int, int> returnBottomTile() { return board->back(); };	

private:
	// A deque that holds the tiles that were placed on the board
	deque<pair<int,int>>* board;
};

