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
#include<iterator>
#include<algorithm>
#include<stdio.h>     
#include<stdlib.h>     
#include<time.h>  

using namespace std;

class Stock
{
public:
	// The constructor will create the stock and shuffle when the tile are finished being made
	Stock();
	~Stock();

	// Constructor if the round is started from within a file, this will hold the rest of the boneyard
	Stock(vector<pair<int, int>>*x) { stockSet = x; };

	// Draw tiles for a user's hand
	void drawTiles( vector<pair<int,int>> *w, int num);

	// Tells how many tiles are left in the boneyard
	void getSize() { cout << "There are " << stockSet->size() << " tiles left in the boneyard." << endl; };

	// Returns a pointer to the boneyard
	vector<pair<int, int>>* getStock() { return stockSet; };

private:
	// A vector of pairs will hold the tiles in the boneyard
	vector<pair<int,int>> *stockSet;

	// Search the stock to make sure the same value os not being made
	bool searchStock(int m, int n);
};

