/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "Tournament.h"

/* ******************************************************************************
Function Name: Tournament

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Tournament::Tournament()
{
	tournamentPoints = 0;
	roundnumber = 0;

	humanOverallScore = 0;
	computerOverallScore = 0;

	tournamentOver = false;
}

/* ******************************************************************************
Function Name: Tournament

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
Tournament::~Tournament()
{
}

/* ******************************************************************************
Function Name: tournamentGame

Purpose: To play a tournament

Parameters: None

Return Value: None

Local Variables: 
		gameRound, a pointer to the round class
		choice, a char variable which holds the user decision to play a new game or 
		saved game
		tempBoard, a pointer to a temporary deque of pairs which will hold the board
		tempComputer, a pointer to a temporary vector of pairs which will hold the 
		computer hand
		tempHand, a pointer to a temporary vector of pairs which will hold the human 
		hand
		tempStock, a pointer to a temporary vector of pairs which will hold the boneyard
		player, a boolean value which will return false if there is nothing intialized
		for next player and previous player passed
		pass, a boolean value that will be intialized to true if the previous player 
		passed and false if they didn't
		current, an integer value whichi will be intalized to the current player

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Tournament::tournamentGame()
{	
	Round * gameRound;

	char choice = getTournamentChoice();

	if (choice == 'n')
	{
		cout << "You have decided to start a new tournament." << endl;
		cout << endl;
		tournamentPoints = askPoints();
	}
	else 
	{
		cout << "You have decided to play a tournament that was saved." << endl;

		cout << endl;

		deque<pair<int, int>>* tempBoard = new deque<pair<int,int>>;
		vector<pair<int, int>>* tempComputer = new vector<pair<int,int>>;
		vector<pair<int, int>>* tempHuman = new vector<pair<int,int>>;
		vector<pair<int, int>>* tempStock = new vector<pair<int,int>>;

		bool player = false;
		bool pass = false;

		int current = 0;
	
		do
		{
			fileName = inputFileName();
		} while (!file->openSavedRound(fileName, tournamentPoints, roundnumber, tempComputer, computerOverallScore, tempHuman, humanOverallScore, tempBoard, tempStock, player, current, pass));
		
		gameRound = new Round(roundnumber, tempBoard, tempComputer, tempHuman, tempStock, player, current, pass);

		if (gameRound->isRoundDone() == false)
		{
			fileName = getFileName();
			file->saveRound(fileName, tournamentPoints, roundnumber, gameRound->getComputer(), computerOverallScore, gameRound->getHuman(), humanOverallScore, gameRound->getBoard(), gameRound->getBoneyard(), gameRound->getCurrent());
			return;
		}
		
		humanOverallScore += gameRound->getHumanRoundScore();
		computerOverallScore += gameRound->getComputerRoundScore();

		roundnumber++;

		displayTournamentScores(humanOverallScore, computerOverallScore);

		isTournamentOver(humanOverallScore, computerOverallScore, tournamentPoints);
	}

	while (tournamentOver == false)
	{
		gameRound = new Round(roundnumber);
			
		if (gameRound->isRoundDone() == false)
		{
			fileName = getFileName();
			file->saveRound(fileName, tournamentPoints, roundnumber, gameRound->getComputer(), computerOverallScore, gameRound->getHuman(), humanOverallScore, gameRound->getBoard(), gameRound->getBoneyard(), gameRound->getCurrent());
			return;
		}
		
		humanOverallScore += gameRound->getHumanRoundScore();
		computerOverallScore += gameRound->getComputerRoundScore();

		roundnumber++;

		displayTournamentScores(humanOverallScore, computerOverallScore);

		isTournamentOver(humanOverallScore, computerOverallScore, tournamentPoints);

		cout << endl;
	}

	tournamentWinner(humanOverallScore, computerOverallScore, tournamentPoints);
}

/* ******************************************************************************
Function Name: getTournamentChoice

Purpose: Ask the user if the would like to play a saved game or a new game

Parameters: None

Return Value: None

Local Variables: 
		input, a char variable which holds the user decision to play a new game or
		save game

Algorithm: None

Assistance Received: None
**********************************************************************************/
char Tournament::getTournamentChoice()
{
	char input;

	do
	{
		// Ask the user if they want to start a new game or their saved game
		cout << "Do you want to start a new game (n) or do you have a saved game (s)? : ";
		cin >> input;

		input = tolower(input);
	} while (input != 'n' && input != 's');

	return input;
}

/* ******************************************************************************
Function Name: askPoints

Purpose: Ask the user how many points to end the tournament

Parameters: None

Return Value: None

Local Variables: 
		input, an integer variable which holds the user decision of how many points
		the tournament should be

Algorithm: None

Assistance Received: None
**********************************************************************************/
int Tournament::askPoints()
{
	int input;

	do {
		cout << "How many points for the to end the tournament? : ";
		cin >> input;
	} while (input <= 0);
	
	return input;
}

/* ******************************************************************************
Function Name: isTournamentOver 

Purpose: To determine if the tournament is over

Parameters:
		m, an integer variable which holds the humanOverallScore
		n, an integer variable which holds the computerOverallScore
		s, an integer variable which holds the tournament score

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Tournament::isTournamentOver(int m, int n, int s)
{
	if (s <= m || s <= n)
	{
		tournamentOver = true;
	}
	else
	{
		tournamentOver = false;
	}
}

/* ******************************************************************************
Function Name: displayTournamentScores

Purpose: Displays the scores of each player

Parameters:
		m, an integer variable which holds the humanOverallScore
		n, an integer variable which holds the computerOverallScore

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Tournament::displayTournamentScores(int m, int n)
{
	cout << "Your score for this tournament: " << m << endl;
	cout << "The computer score for this tournament: "<< n << endl;
}

/* ******************************************************************************
Function Name: tournamentWinner

Purpose: Display the winner of the tournament

Parameters:
		m, an integer variable which holds the humanOverallScore
		n, an integer variable which holds the computerOverallScore
		s, an integer variable which holds the tournament score

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
void Tournament::tournamentWinner(int m, int n, int s)
{
	if (m >= s && n >= s)
	{
		if (m >= n)
		{
			cout << "The winner of the tournament is you!" << endl;
		}
		else
		{
			cout << "The winner of the tournament is the computer!" << endl;
		}
	}
	else
	{
		if (m >= s)
		{
			cout << "The winner of the tournament is you!" << endl;
		}
		else
		{
			cout << "The winner of the tournament is the computer!" << endl;
		}
	}
}

/* ******************************************************************************
Function Name: getFileName

Purpose: Input a file name of where to save the game

Parameters: None

Return Value: None

Local Variables: 
		file, a string variable that holds the file name

Algorithm: None

Assistance Received: None
**********************************************************************************/
string Tournament::getFileName()
{
	string file;

	cout << "What would you like to name the file?: ";
	cin >> file;

	return file;
}

/* ******************************************************************************
Function Name: inputFileName

Purpose: Input the filename of the saved round 

Parameters: None

Return Value: None

Local Variables: 
		file, a string variable that holds the file name

Algorithm: None

Assistance Received: None
**********************************************************************************/
string Tournament::inputFileName()
{
	string file;

	cout << "What is the name of the textfile of the saved round?: ";
	cin >> file;

	return file;
}