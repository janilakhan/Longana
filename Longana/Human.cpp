/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Human.h"

/* ******************************************************************************
Function Name: Human

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Human::Human()
{
}

/* ******************************************************************************
Function Name: Human

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Human::~Human()
{
}

/* ******************************************************************************
Function Name: play

Purpose: Choose wat move the humans want to play

Parameters: 
		board, a pointer to the layout class
		boneyard, a pointer to the stock class

Return Value: None

Local Variables:
		choice, an integer variable that represent what choice the has made

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Human::play(Layout * board, Stock * boneyard)
{
	// Display the Human's Hand
	cout << "Your Hand:" << endl;
	userHand->displayHand(humanHand);

	// Blank Line
	cout << endl;

	int choice;

	cout << "Here are your choices." << endl;
	cout << "1: Choose a Tile" << endl;
	cout << "2: Pass" << endl;
	cout << "3: Help" << endl;
	cin >> choice;

	// Blank Line
	cout << endl;

	switch (choice)
	{
	case 1:
		chooseTile(board, boneyard);
		board->humanPass = false;
		break;
	case 2:
		passTurn(board, boneyard);
		break;
	case 3:
		askForHelp(board);
		play(board, boneyard);
		break;
	default:
		play(board, boneyard);
	}

	// Blank Line
	cout << endl;
}

/* ******************************************************************************
Function Name: chooseTile

Purpose: To choose a tile from a user's hand and placed it to the board

Parameters: 
		board, a pointer to the layout class
		boneyard, a pointer to the stock class

Return Value: None

Local Variables:
		num1, an integer value which will represent the first value the user input
		num2, an integer value which will represent the second value the user input
		temp, a pair of ints which will equal to the values the user input 

Algorithm: 
		1) Input two values and intialize temp
		2) Search through the hand for that tile, if not found give an error message
		3) Check if the tile is a double or if the computer passed, these are the 
		   only conditions that will allow a user place a tile on the right
		4) If not a double and the computer did not pass then the tile is placed on 
		   the left side of the board 

Assistance Received: None
**********************************************************************************/
void Human::chooseTile(Layout * board, Stock * boneyard)
{
	// Intialize Local Variables
	int num1, num2;
	pair<int, int> temp;

	// Input two numbers 
	cout << "Choose a tile from your hand." << endl;

	cout << "Type in the first pip:";
	cin >> num1;

	cout << "Type in the second pip:";
	cin >> num2;

	// Intialize temp with two values from above
	temp = make_pair(num1, num2);

	// Blank Line
	cout << endl;

	// Search the hand for the tile, if false give an error message
	if (userHand->searchHand(humanHand, temp) == false)
	{
		cout << "The tile you have chosen is not in your hand." << endl;
		chooseTile(board, boneyard);
	}
	else
	{
		// Check if it is a double, if true the user can choose which side to place the tile  
		if (isDouble(temp))
		{
			chooseLocation(board, boneyard, temp);
		}
		else
		{
			// Check if the computer passed, it true the user can choose which side to place the tile
			if (board->didComputerPass() == true)
			{
				chooseLocation(board, boneyard, temp);
			}
			else
			{
				// The user can only place the tile on the left
				addToLeft(board, boneyard, humanHand, temp);
			}
		}
	}
}

/* ******************************************************************************
Function Name: passTurn

Purpose: When the user cannot place a tile, the user can call the passTurn and draw
a tile which may be placed

Parameters: 
		board, a pointer to the layout class
		boneyard, a pointer to the stock class

Return Value: None

Local Variables:
		top, a pair of ints which represent the first tile on the left side of the board

Algorithm:
		1) If the boneyard is empty, give a statement and make humanPass equal true
		2) If the boneyard is not empty draw a tile and check if it can be placed
		3) If it can place the tile and set humanPass to false, otherwise set humanPass
		   to false

Assistance Received: None
**********************************************************************************/
void Human::passTurn(Layout * board, Stock * boneyard)
{
	// If the Boneyard is not empty, continue
	if (boneyard->getStock()->empty() == false)
	{
		// Intialize top to the first tile on the left side of the board
		pair<int, int> top = board->returnTopTile();
		pair<int, int> bottom = board->returnBottomTile();
	
		// Human Hand draws a tile
		boneyard->drawTiles(humanHand, draw);

		// Check if the tile can be placed, if true place the tile ans set humanPass to false
		if (isDouble(humanHand->back()) == true && isTileLegalRight(humanHand->back(), bottom) == true)
		{
			cout << "You drawed a tile " << humanHand->back().first << "-" << humanHand->back().second << " and placed it on the right." << endl;
			addToRight(board, boneyard, humanHand, humanHand->back());
			board->humanPass = false;
		}
		else if (isTileLegalLeft(humanHand->back(), top) == true)
		{
			cout << "You have drawed a tile " << humanHand->back().first << "-" << humanHand->back().second << " and placed it on the left." << endl;
			addToLeft(board, boneyard, humanHand, humanHand->back());
			board->humanPass = false;		
		}
		else
		{
			// Otherwise, set humanPass to true
			cout << "You have drawed a tile " << humanHand->back().first << "-" << humanHand->back().second << " but was not able to play so you had to pass." << endl;
			board->humanPass = true;
		}
	}
	else
	{
		cout << "The boneyard is empty so you can't draw a tile and must pass." << endl;
		board->humanPass = true;
	}
	
}

/* ******************************************************************************
Function Name: chooseLocation

Purpose: Choose where to place a tile when a double or when the computer passed

Parameters: 
		board, a pointer to the layout class
		boneyard, a pointer to the stock class
		t, a pair of ints which it the tile the user would like to place on the board

Return Value: None

Local Variables:
		choice, an integer variable which represents where to place the tile

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Human::chooseLocation(Layout * board, Stock * boneyard, pair<int,int> & t)
{
	int choice;

	cout << "You are allowed to choose where to place the tile" << endl;
	cout << "Choose 0 for the left side, 1 for the right side" << endl;
	cin >> choice;

	cout << endl;

	switch (choice)
	{
	case 0: 
		addToLeft(board, boneyard, humanHand, t);
		break;
	case 1: 
		addToRight(board, boneyard, humanHand, t);
		break;
	default:
		chooseLocation(board, boneyard, t);
	}
}

/* ******************************************************************************
Function Name: askForHelp

Purpose: To tell the user what tile they should play and where to placed that tile

Parameters: 
		board, a pointer to the layout class

Return Value: None

Local Variables:
		top, a pair of ints which represents the first tile from the left side
		bottom, a oair of ints which represents the first tile from the right side
		tempPair, a pair of ints which will equal a temporary value as we check for
		the best possible tile
		countPips, an integer variable which equals to the sum of a tile
		largestTile, an integer variable which holds the sum of the tile with the 
		greatest value

Algorithm:
		1) Search through the hand for possibles tile
		2) If the temporary vector is empty, tell the user to pass 
		3) Search through the temporary vector for a double, if there is tell the user
		   to place that tile on the board (Checks for the right side first)
		4) If a double cannot be placed, search for the tile with the greatest value
		   and tell the user to place the tile on the board (on the left side
		   unless the computer passed and the tile is legal on the right side)

Assistance Received: None
**********************************************************************************/
void Human::askForHelp(Layout * board)
{
	// Intialize local variables
	pair<int, int> top = board->returnTopTile();
	pair<int, int> bottom = board->returnBottomTile();

	pair<int, int> tempPair;
	int countPips = 0;
	int largestTile = 0;

	// Search for possible tile
	searchForTile(board, top, bottom);

	// If empty tell the user to pass
	if (humanTemp.empty() == true)
	{
		cout << "There is no tile in your hand that you can play, it is better to pass." << endl;
	}
	else
	{
		// Check if the Computer pass
		if (board->didComputerPass() == true)
		{
			// Chose the best tile 
			for (int a = 0; a < (int)humanTemp.size(); a++)
			{
				// Check for a double
				if (isDouble(humanTemp[a]) == true)
				{
					tempPair = humanTemp[a];
					break;
				}
				else
				{
					// Search for a tile with the greatest sum
					countPips = countTilePips(humanTemp[a]);
					if (largestTile < countPips)
					{
						largestTile = countPips;
						tempPair = humanTemp[a];
					}
				}
			}

			// Check if the tile can be placed on the right side, if not check on the left side
			if (isTileLegalRight(tempPair, bottom) == true)
			{
				cout << "Choose Tile: " << tempPair.first << "-" << tempPair.second << " and put it to the right side." << endl;
			}
			else 
			{
				if (isTileLegalLeft(tempPair, top) == true)
				{
					cout << "Choose Tile: " << tempPair.first << "-" << tempPair.second << " and put it to the left side." << endl;
				}
			}
		}
		else
		{
			for (int a = 0; a < (int)humanTemp.size(); a++)
			{
				// Check if it is a double
				if (isDouble(humanTemp[a]) == true)
				{
					tempPair = humanTemp[a];
					break;
				}
				else
				{
					// Search for the tile with the greatest sum
					countPips = countTilePips(humanTemp[a]);
					if (largestTile < countPips)
					{
						largestTile = countPips;
						tempPair = humanTemp[a];
					}
				}
			}

			// If the temp is a double check if it can be place on the right
			if (isDouble(tempPair) == true && isTileLegalRight(tempPair, bottom) == true)
			{
				cout << "Choose Tile: " << tempPair.first << "-" << tempPair.second << " and put it to the right side." << endl;
			}
			else
			{
				// If the tile is legal tell the user to place the tile
				if (isTileLegalLeft(tempPair, top) == true)
				{
					cout << "Choose Tile: " << tempPair.first << "-" << tempPair.second << " and put it to the left side." << endl;
				}
			}
			
		}
	}	

	cout << endl;
	humanTemp.clear();
}

/* ******************************************************************************
Function Name: Stock

Purpose: To search for potential tiles to play and push back to a temporary vector

Parameters: 
		board, a pointer to the layout class
		t, a pair of ints which represents the first tile on the left side of the board
		s, a pair of ints which represents the first tile on the right side of the board 

Return Value: None

Local Variables:
		i, an integer variable which iterates through a for loop

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Human::searchForTile(Layout * board, pair<int, int>& t, pair<int, int>& s)
{
	for (int i = 0; i < (int)humanHand->size(); i++)
	{
		if (isDouble(humanHand->operator[](i)) == true && isTileLegalRight(humanHand->operator[](i), s) == true)
		{
			humanTemp.push_back(make_pair(humanHand->operator[](i).first, humanHand->operator[](i).second));
		}
		else if (isTileLegalLeft(humanHand->operator[](i), t) == true)
		{
			humanTemp.push_back(make_pair(humanHand->operator[](i).first, humanHand->operator[](i).second));
		}
		else 
		{
			if (board->didComputerPass() == true && isTileLegalRight(humanHand->operator[](i), s) == true)
			{
				humanTemp.push_back(make_pair(humanHand->operator[](i).first, humanHand->operator[](i).second));
			}
		}
	}
}
