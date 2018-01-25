/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Layout.h"

/* ******************************************************************************
Function Name: Layout

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Layout::Layout()
{
	board = new deque<pair<int, int>>;
	humanPass = false;
	computerPass = false;
}

/* ******************************************************************************
Function Name: Layout

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None 

Assistance Received: None
**********************************************************************************/
Layout::~Layout()
{
	board->clear();
}

/* ******************************************************************************
Function Name: placeEngine

Purpose: To create the tiles that would be known as the boneyard and shuffle them
a certain number of times.

Parameters: 
		v, a pointer to a vector of pairs that holds a user's hand
		engine, an integer that is known as the first tile that should be placed

Return Value: None

Local Variables:
		temp, a pair of ints that is intialized by the engine number 
		it, an iterator that iterates through a vector

Algorithm:
		1) Intialize temp to the value of engine
		2) search through the vector with the find function
		3) If found place the tile and erase it from the vector, else print out an
		   error statement

Assistance Received: None
**********************************************************************************/
void Layout::placeEngine(vector<pair<int, int>>* v, int engine)
{
	// Intialize temp with the engine
	pair<int, int> temp = make_pair(engine, engine);

	// Iterate through the vector and search for the tile
	vector<pair<int, int>>::iterator it = find(v->begin(), v->end(), temp);

	// If found, place the tile on the left and erase it from the vector
	if (it != v->end())
	{
		placeTileLeft(temp);
		v->erase(it);
	}
	else
	{
		cout << "The engine is not in the hand" << endl;
	}
}

/* ******************************************************************************
Function Name: swapPips

Purpose: To swap the value of each side of the tile

Parameters: 
		x, a pair of ints that holds the values of a tile

Return Value: None

Local Variables:
		temp, an integer that will be intialized to the first value of the pair

Algorithm:
		1) Intialize temp to the first value of x
		2) Set the first value of x to equal the second value of x
		3) Set the second value of x to the temp value

Assistance Received: None
**********************************************************************************/
void Layout::swapPips(pair<int, int>* x)
{
	int temp;

	temp = x->first;
	x->first = x->second;
	x->second = temp;
}

/* ******************************************************************************
Function Name: didComputerPass

Purpose: To return a boolean value which will help the Human determine if the 
computer pass

Parameters: None

Return Value: A boolean value that represents if the computer has passed or not

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool Layout::didComputerPass()
{
	if (computerPass == true)
	{
		return true;
	}
	return false;
}

/* ******************************************************************************
Function Name: didHumanPass

Purpose: To return a boolean value which will help the computer determine if the 
human has passed

Parameters: None

Return Value: A boolean value that represents if the human has passed or not

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool Layout::didHumanPass()
{
	if (humanPass == true)
	{
		return true;
	}
	return false;
}
