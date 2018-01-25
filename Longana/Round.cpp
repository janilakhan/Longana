/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Round.h"

/* ******************************************************************************
Function Name: Round

Purpose: Constructor

Parameters: 
		n, intialize to the value of num which will help to find the engine and the
		first player

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Round::Round(int n): num(n)
{
	// Assign the players of the game
	humanPlayer = new Human();
	computerPlayer = new Computer();

	// Create a new board 
	board = new Layout();
	boardView.setBoard(board);
	
	// Creates a stock
	boneyard = new Stock();

	// Get Functions from the Hand class
	userHand = new Hand();

	// Draw tiles right as the round has begun
	boneyard->drawTiles(humanPlayer->getHumanHand(),firstDraw);
	boneyard->drawTiles(computerPlayer->getComputerHand(), firstDraw);

	firstPlayer = false;
	roundOver = false;

	humanRoundScore = 0;
	computerRoundScore = 0;

	playRound();
}

/* ******************************************************************************
Function Name: Round

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Round::~Round()
{
	delete board;
	delete boneyard;
	delete userHand;
	delete humanPlayer;
	delete computerPlayer;
}

/* ******************************************************************************
Function Name: Round

Purpose: Constructor

Parameters: 
		n, an integer variable that holds the round number
		v, a pointer to a deque of pairs which holds the board
		w, a pointer to a vector of pairs which holds the computer hand
		x, a pointer to a vector of pairs which holds the human hand
		y, a pointer to a vector of pairs which holds the boneyard
		player, a boolean value which determines if the first player has played 
		or not
		current, an integer variable which determines who is the current player
		pass, a boolean variable which determines if the previous player has passed

Return Value: None

Local Variables:None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Round::Round(int n, deque<pair<int,int>>*v, vector<pair<int,int>>*w, vector<pair<int,int>>*x, vector<pair<int,int>>*y, bool player, int current, bool pass)
{
	num = n;

	board = new Layout(v);
	boardView.setBoard(board);

	boneyard = new Stock(y);
	
	userHand = new Hand();

	humanPlayer = new Human(x);
	computerPlayer = new Computer(w);

	if (player == false)
	{
		firstPlayer = false;
	}
	else
	{
		firstPlayer = true;
		currentPlayer = current;
	}

	if (pass == true)
	{
		if (current == 1)
		{
			board->humanPass = true;
		}
		else
		{
			board->computerPass = true;
		}
	}
	else
	{
		if (current == 0)
		{
			board->humanPass = false;
		}
		else
		{
			board->computerPass = false;
		}
	}

	humanRoundScore = 0;
	computerRoundScore = 0;

	roundOver = false;

	playRound();
}

/* ******************************************************************************
Function Name: playRound

Purpose: Plays a round unless interuppted

Parameters: None

Return Value: None

Local Variables:
		input, a char variable which holds the user decision to keep playing or to save

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Round::playRound()
{	
	// Ask the user if they would like to keep playing or to save
	char input;
	do {
		cout << "Do you want to save the round (s) or keep on playing (p): ";
		cin >> input;
		input = tolower(input);
	} while (input != 's' && input != 'p');

	if (input == 's')
	{
		return;
	}

	cout << endl;

	// Check if the firstPlayer was found
	if (firstPlayer == false)
	{
		// Find the engine number for this round
		engine = engineNumber(num);

		// Print the Round Number
		cout << "Round# : " << num + 1 << endl;

		cout << endl;

		// Determine the first player
		findFirstPlayer(humanPlayer->getHumanHand(), computerPlayer->getComputerHand());

		cout << endl;
	}

	// Print the Board
	boardView.printBoard();

	// Blank Line
	cout << endl;
	
	while (roundOver == false)
	{
		// Get the size of the board
		boneyard->getSize();
		cout << endl;

		if (currentPlayer == 0)
		{
			// humans turn
			cout << "Human Player Turn" << endl;
			humanPlayer->play(board, boneyard);	
		}
		else
		{
			// Computer turn
			cout << "Computer Player Turn" << endl;
			computerPlayer->play(board, boneyard);
		}	

		// Print the board
		boardView.printBoard();
		cout << endl;

		// ask the user if they would like to save or keep playing
		do {
			cout << "Do you want to save the round (s) or keep on playing (p): ";
			cin >> input;
			input = tolower(input);
		} while (input != 's' && input != 'p');

		if (input == 's')
		{
			return;
		}

		// Blank line
		cout << endl;
		
		// Alternate players
		alternatePlayer(currentPlayer);

		// Check if the round is over
		isRoundOver(humanPlayer->getHumanHand(), computerPlayer->getComputerHand(), boneyard->getStock());
	}

	cout << "End of the round!" << endl;

	// Blank Line
	cout << endl;

	// Calculate the score for each player
	roundScore(humanPlayer->getHumanHand(), computerPlayer->getComputerHand(), boneyard->getStock());

	// Blank Line
	cout << endl;

	// Display the score of the round
	displayRoundScore(humanRoundScore, computerRoundScore);

	// Blank Line
	cout << endl;
}

/* ******************************************************************************
Function Name: engineNumber

Purpose: To determine the engine for the round

Parameters: 
		num, an integer variable that holds value of the round number

Return Value: an integer value of what the engine is

Local Variables:
		mod, an integer variable that hold the value after being mod

Algorithm: None

Assistance Received: None
**********************************************************************************/
int Round::engineNumber(int num)
{
	int mod;

	mod = num % 7;

	switch (mod) {
	case 1:
		engine = 5;
		break;
	case 2:
		engine = 4;
		break;
	case 3:
		engine = 3;
		break;
	case 4:
		engine = 2;
		break;
	case 5:
		engine = 1;
		break;
	case 6:
		engine = 0;
		break;
	default:
		engine = 6;
		break;
	}

	return engine;
}

/* ******************************************************************************
Function Name: searchEngine

Purpose: To determine if the engine is in a user's hand

Parameters: 
		v, a pointer to a vector of pairs which represents a user's hand
		num, an integer variable which holds the vlue of the engine

Return Value: A boolean value which represents if the engine was found or not

Local Variables:
		temp, a pair of ints which is intialize to be the engine
		it, an iterator which iterates and seaches for the engine tile

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool Round::searchEngine(vector<pair<int,int>> *v, int num)
{
	// Intialize temp
	pair<int, int> temp = make_pair(num, num);

	// Search for the engine
	vector<pair<int, int>>::iterator it = find(v->begin(), v->end(), temp);

	// Return if found, false if not
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
Function Name: findFirstPlayer

Purpose: Determine who is the first player of the round

Parameters:
		v, a pointer to a vector of pairs which represents the human hand
		w, a pointer to a vector of pairs which represents the computer hand

Return Value: None

Local Variables: None

Algorithm:
		1) Search the human hand for the engine, if found place the tile
		2) Search for the computer hand for the engine, if found place the tile
		3) If not found both players draw a tile and keep on going until one user 
		   has the engine and places it on the board

Assistance Received: None
**********************************************************************************/
void Round::findFirstPlayer(vector<pair<int, int>> * v, vector<pair<int,int>> *w)
{
	do {
		if (searchEngine(v, engine) == true)
		{
			firstPlayer = true;
			currentPlayer = 1;
			cout << "Human is the first player" << endl;
			board->placeEngine(v, engine);
		}
		else if(searchEngine(w, engine) == true)
		{
			firstPlayer = true;
			currentPlayer = 0;
			cout << "Computer is the first player" << endl;
			board->placeEngine(w, engine);
		}
		else
		{
			boneyard->drawTiles(v, draw);
			boneyard->drawTiles(w, draw);
		}
	} while (firstPlayer == false);
}

/* ******************************************************************************
Function Name: alternatePlayer

Purpose: To change player

Parameters:
		player, an integer variable which holds whose turn it is to play

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Round::alternatePlayer(int player)
{
	
	if (player == 0)
	{
		currentPlayer = 1;
	}
	else
	{
		currentPlayer = 0;
	}
}

/* ******************************************************************************
Function Name: isRoundOver

Purpose: Determine if the Round is over

Parameters:
		x, a pointer to a vector of pairs which represents the human hand
		w, a pointer to a vector of pairs which represents the computer hand
		z, a pointer to a vector of pairs which represents the boneyard

Return Value: None

Local Variables: None

Algorithm: 
		1) Checks if the humanHand or computerHand is empty, if true then roundOver 
		   is true
		2) Checks if the boneyard is empty and if both players have passed, if true 
		   then roundOver is true
		3) Else returns false

Assistance Received: None
**********************************************************************************/
void Round::isRoundOver(vector<pair<int, int>>* x, vector<pair<int, int>>* w, vector<pair<int, int>>* z)
{
	if (x->empty() == true || w->empty() == true)
	{
		roundOver = true;
	}
	else if (z->empty() == true && board->didHumanPass() == true && board->didComputerPass() == true)
	{
		roundOver = true;
	}
	else
	{
		roundOver = false;
	}
}

/* ******************************************************************************
Function Name: roundScore

Purpose: Calculate the score of the round

Parameters:
		x, a pointer to a vector of pairs which represents the human hand
		w, a pointer to a vector of pairs which represents the computer hand
		z, a pointer to a vector of pairs which represents the boneyard

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Round::roundScore(vector<pair<int, int>> * x, vector<pair<int,int>>*w, vector<pair<int,int>> * z)
{
	// Display Each users Hand
	cout << "Your Hand:" << endl;
	userHand->displayHand(x);

	cout << endl;

	cout << "Computer Hand:" << endl;
	userHand->displayHand(w);

	cout << endl;

	// Check if the human or the computer hand are empty
	if (x->empty() == true || w->empty() == true)
	{
		// if the human hand is empty, the human gains the computer hand value
		if (x->empty() == true)
		{
			humanRoundScore = userHand->countHand(w);
			cout << "You win this round and gains " << humanRoundScore << " points." << endl;
		}
		else
		{
			// if the computer hand is empty, the computer gains the human hand points
			computerRoundScore = userHand->countHand(x);
			cout << "The computer wins this round and gains " << computerRoundScore << " points." << endl;
		}
	}
	else
	{
		// if the boneyard is empty and both player pass, calculate both player hand and see who has the smallest sum
		// the smallest sum is the winner of the round
		if (z->empty() == true && board->didHumanPass() == true && board->didComputerPass() == true)
		{
			humanRoundScore = userHand->countHand(x);
			computerRoundScore = userHand->countHand(w);

			if (humanRoundScore < computerRoundScore)
			{
				humanRoundScore = computerRoundScore;
				computerRoundScore = 0;
				cout << "You win this round and gains " << humanRoundScore << " points." << endl;
			}
			// If tied both players get zero points
			else if (humanRoundScore == computerRoundScore)
			{
				humanRoundScore = 0;
				computerRoundScore = 0;
				cout << "This round is a draw since both players have the same amount of points." << endl;
			}
			else
			{
				computerRoundScore = humanRoundScore;
				humanRoundScore = 0;
				cout << "The computer wins this round and gains " << computerRoundScore << " points." << endl;
			}
		}
	}
}

/* ******************************************************************************
Function Name: displayRoundScore

Purpose: Display the score of each player of the round

Parameters:
		n, integer variable which represents the humanScore
		m, integer variable which represents the computerHand

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Round::displayRoundScore(int n, int m)
{
	cout << "Your Score for this round: " << n << endl;
	cout << "The computer score for this round: " << m << endl;
}

