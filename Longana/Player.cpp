/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Player.h"

/* ******************************************************************************
Function Name: Player

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Player::Player()
{
	userHand = new Hand();
	humanHand = new vector<pair<int, int>>;
	computerHand = new vector<pair<int, int>>;
}

/* ******************************************************************************
Function Name: Player

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Player::~Player()
{
	delete userHand;
	humanHand->clear();
	computerHand->clear();
}

/* ******************************************************************************
Function Name: addtoRight

Purpose: Add a tile to the right side of the board

Parameters: 
		board, a pointer to the layout class
		boneyard, a pointer to the stock class
		v, a pointer to a vector of pairs which is a user's hand
		t, a pair of ints which is the tile the user wants to place on the board

Return Value: None

Local Variables:
		bottom, a pair of ints which is the first tile on the right side of the board
		it, an iterator that iterates a vector 

Algorithm: 
		1) Check if the tile can be placed on the right side of the board
		2) If false, send an error message and call the play function
		3) If true, find the tile and place the tile on the board and erase from the
		   hand

Assistance Received: None
**********************************************************************************/
void Player::addToRight(Layout * board, Stock * boneyard, vector<pair<int, int>>* v, pair<int, int>& t)
{
	// intialize bottom to the first tile on the right side of the board
	pair<int, int> bottom = board->returnBottomTile();
		
	// Check if the tile is legal to bottom
	if (isTileLegalRight(t, bottom) == false)
	{
		cout << "This Move Is Not Legal" << endl;
		play(board, boneyard);
	}
	else
	{
		// Find the tile in the hand
		vector<pair<int, int>>::iterator it = find(v->begin(), v->end(), t);
	
		if (it != v->end())
		{
			// Check if it can be swapped
			if (t.second == bottom.second)
			{
				board->swapPips(&t);
			}
			// Add the tile to the right side of the board and erase the tile from the vector
			board->placeTileRight(t);
			v->erase(it);
		}
	}
}

/* ******************************************************************************
Function Name: addToRight

Purpose: Add a tile to the left side of the board

Parameters: 
		board, a pointer to the Layout clas 
		boneyard, a pointer to the stock class
		v, a pointer to a vector of pairs which is a user's hand
		t, a pair of ints whcih is the tile a user want to place on the left side of the board

Return Value: None

Local Variables:
		top, a pair of ints whcih the first tile on the left side of the board
		it, an iterator that iterates through a vector

Algorithm:
		1) Check if a tile can be placed on the left side of the board
		2) If false, send an error message and call the play function
		3) If true, find the tile and placed the tile on the right side of the board, 
		   and erase the tile from the vector

Assistance Received: None
**********************************************************************************/
void Player::addToLeft(Layout * board, Stock * boneyard, vector<pair<int, int>>* v, pair<int, int>& t)
{
	// Intialize top to the first tile on the left side of the board
	pair<int, int> top = board->returnTopTile();
		
	// Check if the tile is able to be played on the left side of the board
	if (isTileLegalLeft(t, top) == false)
	{
		cout << "This Move Is Not Legal" << endl;
		cout << endl;
		play(board, boneyard);
	}
	else
	{
		// Find the tile in the vector
		vector<pair<int, int>>::iterator it = find(v->begin(), v->end(), t);
	
		if (it != v->end())
		{
			// Check if it can be swapped
			if (t.first == top.first)
			{
				board->swapPips(&t);
			}
			// Add the tile to the left side of the board and erase the tile from the vector
			board->placeTileLeft(t);
			v->erase(it);
		}
	}
}

/* ******************************************************************************
Function Name: isTileLegalRight

Purpose: To check if the tile can be placed by another tile

Parameters: 
		t, a pair of ints which value is equal to the first tile 
		s, a pair of ints which value is equal to the second tile

Return Value: A boolean value which represents if the tile can be placed or not 

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool Player::isTileLegalRight(pair<int, int>& t, pair<int, int>& s)
{
	if (t.first == s.second)
	{
		return true;
	}
	else if (t.second == s.second)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ******************************************************************************
Function Name: isTileLegalLeft

Purpose: Check if the tile can be placed by another tile

Parameters: 
		t, a pair of ints which value is equal to the first tile
		s, a pair of ints which value is equal to the second tile

Return Value: A boolean value which represents if a tile can be placed or not

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool Player::isTileLegalLeft(pair<int, int>& t, pair<int, int>& s)
{
	if (t.second == s.first)
	{
		return true;
	}
	else if (t.first == s.first)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ******************************************************************************
Function Name: isDouble

Purpose: To check if a tile has equal pips

Parameters: 
		t, a pair of ints which represents a tile

Return Value: A boolean value which represents if a tile is double or not

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool Player::isDouble(pair<int,int> & t)
{
	if (t.first == t.second)
	{
		return true;
	}
	
	return false;
}

/* ******************************************************************************
Function Name: countTilePips

Purpose: To add up a sum of a tile

Parameters: 
		r, a pair of ints which represent a tile values

Return Value: A sum of the tile 

Local Variables:
		countPips, an integer variable that will represent the sum of a tile

Algorithm:
		1) Add the tile's first and secod value

Assistance Received: None
**********************************************************************************/
int Player::countTilePips(pair<int, int>& r)
{
	int countPips = 0;

	countPips = r.first + r.second;

	return countPips;
}
