/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Stock.h"

/* ******************************************************************************
Function Name: Stock

Purpose: To create the tiles that would be known as the boneyard and shuffle them
a certain number of times.

Parameters: None

Return Value: None

Local Variables:
		x, an integer that would hold the first value of the tile
		y, an integer that would hold the second value of the tile
		counter, an integer that holds the number of times the random shuffle function
		would be called to shuffle the tiles 

Algorithm:
		1) Intializes the stockSet
		2) Intialize the random seed
		3) Search through the stockset to see if a tile is already created, if not 
		   add the tile to the stockSet
		4) Shuffle the stockSet a random number of times 

Assistance Received: Jordan Richards
**********************************************************************************/
Stock::Stock()
{
	// Intitalize the stockSet
	stockSet = new vector<pair<int, int>>;

	// initialize random Seed
	srand((unsigned int)time(0));

	int x, y;

	// Add tiles to the stockSet
	for (x = 0; x <= 6; x++)
	{
		for (y = 0; y <= 6; y++)
		{
			// Before adding the tile, must check if a tile is already intialized
			if (searchStock(x, y) == false)
			{
				stockSet->push_back(make_pair(x, y));
			}
		}
	}

	// The counter is initialized by the number of times the stockSet should be shuffled
	int counter = rand() % 5 + 1;

	// Shuffle the stockSet
	for (int i = 0; i < counter; i++)
	{
		random_shuffle(stockSet->begin(), stockSet->end());
	}
}

/* ******************************************************************************
Function Name: Stock

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Stock::~Stock()
{
	stockSet->clear();
}

/* ******************************************************************************
Function Name: searchStock

Purpose: To search through the stockSet to see if a similar tile is already created

Parameters: 
		m, an integer that holds the second value of the temporary tile
		n, an integer that holds the first value of the temporary tile

Return Value: A boolean value, if true then the stockSet has the tile, false otherwise

Local Variables:
		temp <int,int>, a pair of ints which will hold a temporary value
		it, an iterator that will search through the vector for a specific tile

Algorithm:
		1) Intializes the temp
		2) Iterate through the vector and use the find function to find the specific tile
		   If the tile is found return true, otherwise return false

Assistance Received: None
**********************************************************************************/
bool Stock::searchStock(int m, int n)
{
	// Intialize temp to the values from the parameter 
	pair<int, int> temp = make_pair(n, m);

	// Search through the vector for the tile
	vector<pair<int, int>>::iterator it = find(stockSet->begin(), stockSet->end(), temp);

	if (it != stockSet->end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ******************************************************************************
Function Name: drawTiles

Purpose: To copy a certain number of times from the stockSet to another vector and
then erase the those values from the stockSet 

Parameters: 
		w, a pointer to a vector of pairs that holds a user's hand
		num, an interger that holds the number of tiles that would be copy and erased

Return Value: None

Local Variables: None

Algorithm:
		1) Copy the cretain number of pairs from the stockSet to w
		2) Erase the certain number of pairs from the stockSet

Assistance Received: None
**********************************************************************************/
void Stock::drawTiles(vector<pair<int,int>> *w, int num)
{
	copy(stockSet->begin(), stockSet->begin()+ num, back_inserter(*w));
	stockSet->erase(stockSet->begin(), stockSet->begin() + num);
}