/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "SaveFile.h"

/* ******************************************************************************
Function Name: SaveFile

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
SaveFile::SaveFile()
{
}

/* ******************************************************************************
Function Name: SaveFile

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
SaveFile::~SaveFile()
{
}

/* ******************************************************************************
Function Name: Stock

Purpose: To take in input from a text file

Parameters: 
		file, a string variable that holds the text file name
		t_score, an integer variable that will be intalized to the tournament score
		r_num, an integer variable that will be intialized to the round number
		v, a pointer to a vector of pairs which will hold the computer hand
		c_score, an integer variable that will be intialized to the computerOverallScore  
		w, a pointer to a vector of pairs which will hold the human hand
		h_score, an integer variable that will be intialized to the humanOverallScore
		x, a pointer to a deque of pairs which will hold the board
		y, a pointer to a vector of pairs which will hold the boneyard
		player, a boolean value which will return false if there is nothing intialized 
		for next player and previous player passed
		current, an integer value whichi will be intalized to the current player
		pass, a boolean value that will be intialized to true if the previous player passed
		and false if they didn't

Return Value: None

Local Variables:
		counter, an integer variable which will be intialized to cout the lines in the file 
		fileLine, a string variable which will allow us to see one string in the textfile
		at a time
		boardTemp, a deque of strings which will hold the pairs as a string value
		handTemp, a vector of strings which will hold the pairs as a string value
		boneTemp, a vector of strings which will hold the pairs as a string value
		hand_str, a string variable which will hold a pair as a string 
		board_str, a string variable which will hold a pair as a string 
		bone_str, a string variable which will hold a pair as a string
		first, an integer that will hold the first value of the pair
		second, an integer that will hold the second value of an integer
		pos, an integer that will give the position of a specific character in a string

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool SaveFile::openSavedRound(string file, int &t_score, int &r_num, vector<pair<int,int>> * v, int &c_score, vector<pair<int,int>> * w, int &h_score, deque<pair<int,int>> * x, vector<pair<int,int>> * y, bool &player, int &current, bool &pass)
{
	ifstream inPut;

	// Open the file
	inPut.open(file);

	// If not able to open, print out an error message
	if (!inPut)
	{
		cout << "Invalid file name!" << endl;
		return false;
	}

	// Intialize local variable 
	int counter = 0;
	string fileLine;
	deque<string> boardTemp;
	vector<string> handTemp;
	vector<string> boneTemp;


	while (getline(inPut, fileLine))
	{
		// Intialize the hand
		if (counter == 4 || counter == 8)
		{
			// Search for ":" and change the string to eliminate those characters
			int pos = fileLine.find(":");
			fileLine = fileLine.substr(pos + 1);

			stringstream hand(fileLine);
			string hand_str;
			int a = 0;

			// While there is still pairs in the string keep pushing them into the handTemp vector
			while (hand >> hand_str)
			{
				handTemp.push_back(hand_str);
				a++;
			}

			// Intialize the computer hand
			int first, second;
			if (counter == 4)
			{
				for (int i = 0; i < (int)handTemp.size(); i++)
				{
					first = stoi(handTemp[i].substr(0));
					second = stoi(handTemp[i].substr(2));

					v->push_back(make_pair(first, second));
				}
				handTemp.clear();
			}
			else
			{
				//Intialize the human hand
				for (int i = 0; i < (int)handTemp.size(); i++)
				{
					first = stoi(handTemp[i].substr(0));
					second = stoi(handTemp[i].substr(2));

					w->push_back(make_pair(first, second));
				}
				handTemp.clear();
			}
		}
		// Intialize the board
		else if (counter == 12)
		{
			stringstream boardStream(fileLine);
			string board_str;
			int b = 0;

			// While there are still pairs in the string keep pushing them into the boardTemp deque
			while (boardStream >> board_str)
			{
				// If the string has L or R skip
				if (board_str.compare("L") == 0 || board_str.compare("R") == 0)
				{
					continue;
				}
				else
				{
					boardTemp.push_back(board_str);
					b++;
				}
			}

			// Intialize the board
			int first, second;
			for (int i = 0; i < (int)boardTemp.size(); i++)
			{
				first = stoi(boardTemp[i].substr(0));
				second = stoi(boardTemp[i].substr(2));

				x->push_back(make_pair(first, second));
			}

		}
		// Intialize the Boneyard
		else if (counter == 15)
		{
			stringstream bone(fileLine);
			string bone_str;
			int c = 0;

			// While the boneyard still has pair keep pushing them into the boneTemp vector
			while (bone >> bone_str)
			{
				boneTemp.push_back(bone_str);
				c++;
			}

			// Intialize the boneyard
			int first, second;
			for (int i = 0; i < (int)boneTemp.size(); i++)
			{
				first = stoi(boneTemp[i].substr(0));
				second = stoi(boneTemp[i].substr(2));

				y->push_back(make_pair(first, second));
			}
		}
		// Intialize vaues of other parameters
		else
		{
			// Search for ":" and eliminate the characters before pos
			int pos = fileLine.find(":");
			fileLine = fileLine.substr(pos + 1);
			
			switch (counter)
			{
				// Tournament Score
			case 0:
				t_score = stoi(fileLine);
				break;
				// Round number
			case 1:
				r_num = stoi(fileLine);
				r_num = r_num - 1;
				break;
				// Computer Score
			case 5:
				c_score = stoi(fileLine);
				break;
				// Human Score
			case 9:
				h_score = stoi(fileLine);
				break;
			// Previous player passed
			case 17:
				if (fileLine.size() == 1)
				{
					player = false;
				}
				else
				{
					player = true;
					if (fileLine.compare(" Yes") == 0)
					{
						pass = true;
					}
					else
					{
						pass = false;
					}
				}
				break;
			// Next Player
			case 19:
				if (fileLine.size() == 1)
				{
					player = false;
				}
				else
				{
					player = true;
					if (fileLine.compare(" Human") == 0)
					{
						current = 0;
					}
					else
					{
						current = 1;
					}
				}
				break;
			default:
				break;
			}
		}	
		counter++;
	}

	return true;
}

/* ******************************************************************************
Function Name: saveRound

Purpose: Save the round to a textfile by writing to the file

Parameters: 
		file, a string variable that holds the name of the textfile
		t_score, an integer variable that is intialized to the value of the tournament score
		r_num, an integer variable that is intialized to the value of the round number
		computer, a pointer variable to the computer class
		c_score, an integer variable that is intialized to the value of the computerOverallScore
		human, a pointer variable to the human class
		n_score, an integer variable that is intialized to the value of the humanOverallScore
		board, a pointer variable to the layout class
		boneyard, a pointer variable to the stock class
		current, an interger variable that is intialized to the value of the currentPlayer

Return Value: None

Local Variables:
		i, an integer variable that will iterate through a for loop

Algorithm: None

Assistance Received: None
**********************************************************************************/
void SaveFile::saveRound(string file, int t_score, int r_num, Player * computer, int c_score, Player * human, int h_score, Layout * board, Stock * boneyard, int current)
{
	ofstream outPut;
	
	// Open the file
	outPut.open(file);

	if (!outPut)
	{
		// Not able to save the file
		outPut << "The file could not be saved!" << endl;
		return;
	}

	// Get the tournament score
	outPut << "Tournament Score: " << t_score << endl;
		
	// Get the round number
	outPut << "Round No.: " << r_num + 1 << endl;

	// Blank Line
	outPut << endl;

	// Computer Hand and Score
	outPut << "Computer:" << endl;
		
	outPut << "   Hand: ";
	for (int i = 0; i < (int)computer->getComputerHand()->size(); i++)
	{
		outPut << computer->getComputerHand()->operator[](i).first << "-" << computer->getComputerHand()->operator[](i).second << " ";
	}

	outPut << endl;

	outPut << "   Score: " << c_score << endl;

	// Blank Line
	outPut << endl;

	// Human Hand and Score
	outPut << "Human:" << endl;

	outPut << "   Hand: ";
	for (int i = 0; i < (int)human->getHumanHand()->size(); i++)
	{
		outPut << human->getHumanHand()->operator[](i).first << "-" << human->getHumanHand()->operator[](i).second << " ";
	}

	outPut << endl;

	outPut << "   Score: " << h_score << endl;

	// Blank Line
	outPut << endl;

	// Get the layout
	outPut << "Layout:" << endl;
	outPut << "  L ";
	for (int i = 0; i < (int)board->getBoard()->size(); i++)
	{
		outPut << board->getBoard()->operator[](i).first << "-" << board->getBoard()->operator[](i).second << " ";
	}
	outPut << " R";

	// Blank Line
	outPut << endl;
	outPut << endl;

	// Get the boneyard
	outPut << "Boneyard:" << endl;
	for (int i = 0; i < (int)boneyard->getStock()->size(); i++)
	{
		outPut << boneyard->getStock()->operator[](i).first << "-" << boneyard->getStock()->operator[](i).second << " ";
	}

	// Blank Line
	outPut << endl;
	outPut << endl;

	// Get the previous player pass
	outPut << "Previous Player Passed: ";
	if (board->getBoard()->size() == 0)
	{
		outPut << endl;
	}
	else
	{
		if (current == 1)
		{
			if (board->computerPass == true)
			{
				outPut << "Yes" << endl;
			}
			else
			{
				outPut << "No" << endl;
			}
		}
		else
		{
			if (board->humanPass == true)
			{
				outPut << "Yes" << endl;
			}
			else
			{
				outPut << "No" << endl;
			}
		}
	}
	
	// Blank Line
	outPut << endl;

	// Get the next player
	outPut << "Next Player: ";
	if (board->getBoard()->size() == 0)
	{
		outPut << endl;
	}
	else
	{
		if (current == 0)
		{
			outPut << "Computer" << endl;
		}
		else
		{
			outPut << "Human" << endl;
		}
	}
	
	// Close the file
	outPut.close();
}
