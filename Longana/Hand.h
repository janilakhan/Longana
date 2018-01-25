/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<iostream>
#include"string.h"
#include<vector>
#include<utility>
#include "Stock.h"

using namespace std;

class Hand
{
public:
	// Constructor and Destructor of the class
	Hand();
	~Hand();

	// Search through a user's hand for a certain tile
	bool searchHand(vector<pair<int,int>> *v, pair<int,int> &x);

	// Display a user's hand
	void displayHand(vector<pair<int,int>> * v);

	// Count the user's hand for their score
	int countHand(vector<pair<int,int>> *v);
};

