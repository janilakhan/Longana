/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Hand.h"

/********************************************************************************
Function Name: Hand

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Hand::Hand()
{
}

/********************************************************************************
Function Name: Hand

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Hand::~Hand()
{
}

/********************************************************************************
Function Name: searchHand

Purpose: To search through a vector for a specific pair

Parameters: 
		w, a pointer to a vector of pairs which holds tiles within a user's hand
		t, a pair of ints which holds the value of the tile

Return Value: 
		boolean value, true if the pair is found within the hand, otherwise false

Local Variables:
		it, an iterator that goes through the vector it is passed

Algorithm:
		1) Search through the vector for a specific pair using the find function
		   returns true if found, false otherwise

Assistance Received: Jordan Richard
**********************************************************************************/
bool Hand::searchHand(vector<pair<int,int>> *v, pair<int, int> &t)
{
	// Iterate through the vector and seach for the tile
	vector<pair<int, int>>::iterator it = find(v->begin(), v->end(), t);

	if (it != v->end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ******************************************************************************
Function Name: displayHand

Purpose: Print out the tiles a user has within their hand 

Parameters: 
		v, a pointer to a vector of pairs which holds the tiles

Return Value: None

Local Variables:
		i, an integer that is used to iterate through a for loop 

Algorithm:
		1) Go through the vector and print out the values of the tiles 

Assistance Received: None
**********************************************************************************/
void Hand::displayHand(vector<pair<int,int>>* v)
{
	int i;
	for (i = 0; i < (int)v->size(); i++)
	{
		cout << v->operator[](i).first << "-" << v->operator[](i).second << " ";
	}

	cout << endl;
}

/* ******************************************************************************
Function Name: countHand

Purpose: Count each tile within a user's hand and add up the sum 

Parameters: 
		v, a pointer to a vector of pairs which holds the tiles

Return Value: the sum of all the tiles within a user's hand 

Local Variables:
		a, an integer that is used to iterate through a for loop
		count, an integer that will hold the sum of a tile
		sum, an integer that will hold the sum of all the tiles within a vector

Algorithm:
		1) Add up all the values within a tile
		2) Add that value to the sum

Assistance Received: None
**********************************************************************************/
int Hand::countHand(vector<pair<int,int>>* v)
{
	int a;
	int count = 0;
	int sum = 0;

	// Iterate through the vector and add up all the tiles
	for (a = 0; a < (int)v->size(); a++)
	{
		count = v->operator[](a).first + v->operator[](a).second;
		sum = sum + count;
	}

	return sum;
}
