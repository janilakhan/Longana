/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Computer.h"

/* ******************************************************************************
Function Name: Computer

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Computer::Computer()
{
}

/* ******************************************************************************
Function Name: Computer

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Computer::~Computer()
{
}

/* ******************************************************************************
Function Name: play

Purpose: To choose what moves the computer will make

Parameters: 
		board, a pointer to the Layout class
		boneyard, a pointer to the stock class

Return Value: None

Local Variables:
		top, a pair of ints which represent the first tile on the left side of the board
		bottom, a pair of ints which represents the first tile on the right side of the
		board

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Computer::play(Layout * board, Stock * boneyard)
{	
	// Display the Human's Hand
	cout << "Computer Hand:" << endl;
	userHand->displayHand(computerHand);

	cout << endl;

	// Intialize local Variables
	pair<int, int> top = board->returnTopTile();
	pair<int, int> bottom = board->returnBottomTile();

	// Search for possible tiles
	searchForTile(board, top, bottom);
	
	// If the vector is empty pass, if not choose a tile
	if (computerTemp.empty() == true)
	{
		passTurn(board, boneyard);
	}
	else
	{
		chooseTile(board, boneyard);
		computerTemp.clear();
		board->computerPass = false;
	}
}

/* ******************************************************************************
Function Name: chooseTile

Purpose: To choose the best tile to place on the board

Parameters: 
		board, a pointer to the layout class
		boeyard, a pointer to the stock cass

Return Value: None

Local Variables:
		top, a pair of ints which represents the first tile on the left side of the board
		bottom, a pair of ints which represents the first tile on the right side of the
		board
		tempPair, a pair of ints which will hold a temporary values of a tile
		countPips, an integer variable that will hold the sum of a tile
		largestTile, an integer variable that will hold the sum of the greatest sum
		a, an integer varaible used to iterate through a for loop

Algorithm:
		1) Search through the hand for possibles tile
		2) If the temporary vector is empty, tell the user to pass 
		3) Search through the temporary vector for a double, place the tile on the board 
		   (Checks for the left side first)
		4) If a double cannot be placed, search for the tile with the greatest value
		   and tell the user to place the tile on the board (place on the right side
		   unless the human passed and the tile is legal on the left side)

Assistance Received: None
**********************************************************************************/
void Computer::chooseTile(Layout * board, Stock * boneyard)
{
	// Intialize Local Variables
	pair<int, int> top = board->returnTopTile();
	pair<int, int> bottom = board->returnBottomTile();
	
	pair<int, int> tempPair;

	int countPips = 0;
	int largestTile = 0;

	// Check if human passed
	if (board->didHumanPass() == true)
	{
		for (int a = 0; a < (int)computerTemp.size(); a++)
		{
			// check if a double
			if (isDouble(computerTemp[a]) == true)
			{
				tempPair = computerTemp[a];
				break;
			}
			else
			{
				// Search for the tile with the greatest sum
				countPips = countTilePips(computerTemp[a]);
				if (largestTile < countPips)
				{
					largestTile = countPips;
					tempPair = computerTemp[a];
				}
			}			
		}
		
		// Check if the tile can be placed on the right side
		if (isTileLegalLeft(tempPair, top) == true)
		{
			addToLeft(board, boneyard, computerHand, tempPair);
			cout << "The computer placed " << tempPair.first << "-" << tempPair.second << " and place it on the left side." << endl;
		}
		else 
		{
			// Check if the tile can be placed on the left side
			if (isTileLegalRight(tempPair, bottom) == true)
			{
				addToRight(board, boneyard, computerHand, tempPair);
				cout << "The computer placed " << tempPair.first << "-" << tempPair.second << " and place it on the right side." << endl;
			}
		}
	}
	else
	{
		for (int a = 0; a < (int)computerTemp.size(); a++)
		{
			// Check if a double
			if (isDouble(computerTemp[a]) == true)
			{
				tempPair = computerTemp[a];
				break;
			}
			else
			{
				// Search for the tile with the greatest sum
				countPips = countTilePips(computerTemp[a]);
				if (largestTile < countPips)
				{
					largestTile = countPips;
					tempPair = computerTemp[a];
				}
			}
		}

		// If there is a double check if it can be placed on the left side
		if (isDouble(tempPair) == true && isTileLegalLeft(tempPair, top) == true)
		{
			addToLeft(board, boneyard, computerHand, tempPair);
			cout << "The computer placed " << tempPair.first << "-" << tempPair.second << " and put it to the left side." << endl;
		}
		else
		{
			// Check if it can be placed on the right side
			if (isTileLegalRight(tempPair, bottom) == true)
			{
				addToRight(board, boneyard, computerHand, tempPair);
				cout << "The computer placed " << tempPair.first << "-" << tempPair.second << " and put it to the right side." << endl;
			}
		}
		
	}

	cout << endl;
}


/* ******************************************************************************
Function Name: passTurn

Purpose: If the computer cannot place a tile on the board they must pass by drawing a 
tile and seeing if they can play with that tile

Parameters: 
		board, a pointer to the layout class
		boneyard, a pointer to the stock class

Return Value: None

Local Variables:
		bottom, a pair of int which represent the first tile on the right side on the
		baord

Algorithm:
		1) Check if the boneyard is empty, if empty the computerPass is equal to true
		2) If not empty, draw a tile and check if it can be played
		3) Play the tile if it can and set computerPass to false, otherwise computerPass
		   is true

Assistance Received: None
**********************************************************************************/
void Computer::passTurn(Layout * board, Stock * boneyard)
{
	// Check if the boneyard is empty
	if (boneyard->getStock()->empty() == false)
	{
		pair<int, int> bottom = board->returnBottomTile();
		pair<int, int> top = board->returnTopTile();

		// Draw a tile
		boneyard->drawTiles(computerHand, draw);

		// Placed the tile if it legal and set computerPass to false
		if (isDouble(computerHand->back()) == true && isTileLegalLeft(computerHand->back(), top) == true)
		{
			cout << "The computer drawed tile " << computerHand->back().first << "-" << computerHand->back().second << " and placed it on the left." << endl;
			addToLeft(board, boneyard, computerHand, computerHand->back());
			board->computerPass = false;
		}
		else if (isTileLegalRight(computerHand->back(), bottom) == true)
		{
			cout << "The computer drawed tile " << computerHand->back().first << "-" << computerHand->back().second << " and placed it on the right." << endl;
			addToRight(board, boneyard, computerHand, computerHand->back());
			board->computerPass = false;
		}
		else
		{
			// computerPass is set to true
			cout << "The computer drawed a tile "<< computerHand->back().first << "-" << computerHand->back().second <<" and was not able to play so they had to pass." << endl;
			board->computerPass = true;
		}
	}
	else
	{
		// computerPass is set to true
		cout << "The boneyard is empty so the computer can't draw a tile and must pass." << endl;
		board->computerPass = true;
	}

	cout << endl;
}

/* ******************************************************************************
Function Name: searchForTile

Purpose: Search for possibile tile to place on the board

Parameters: 
		board, a pointer to the layout class
		t, a pair of ints that represent the first tile on the left side of the board
		s, a pair of ints that represent the first tile on the right side of the board

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Computer::searchForTile(Layout * board, pair<int, int>& t, pair<int, int>& s)
{
	for (int i = 0; i < (int)computerHand->size(); i++)
	{
		if (isDouble(computerHand->operator[](i)) == true && isTileLegalLeft(computerHand->operator[](i), t) == true)
		{
			computerTemp.push_back(make_pair(computerHand->operator[](i).first, computerHand->operator[](i).second));
		}
		else if (isTileLegalRight(computerHand->operator[](i), s) == true)
		{
			computerTemp.push_back(make_pair(computerHand->operator[](i).first, computerHand->operator[](i).second));
		}
		else
		{
			if (board->didHumanPass() == true && isTileLegalLeft(computerHand->operator[](i), t) == true)
			{
				computerTemp.push_back(make_pair(computerHand->operator[](i).first, computerHand->operator[](i).second));
			}
		}
	}
}
