/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#include "LayoutView.h"

/* ******************************************************************************
Function Name: LayoutView

Purpose: Constructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
LayoutView::LayoutView()
{
	board = NULL;
}

/* ******************************************************************************
Function Name: LayoutView

Purpose: Destructor

Parameters: None

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
LayoutView::~LayoutView()
{
	delete board;
}

/* ******************************************************************************
Function Name: setBoard

Purpose: To set the board

Parameters: 
		newBoard, a pointer to the board

Return Value: None

Local Variables: None

Algorithm: None

Assistance Received: None
**********************************************************************************/
bool LayoutView::setBoard(Layout * newBoard)
{
	// the board is empty so we need to set a new board
	if (board == NULL)
	{
		board = newBoard;
		return true;
	}

	// the board is not empty so we can't set a new board
	return false;
}

/* ******************************************************************************
Function Name: printBoard

Purpose: To print the values of the board

Parameters: None

Return Value: None

Local Variables:
		i, an integer that iterates through the deque which holds the board

Algorithm: None

Assistance Received: None
**********************************************************************************/
void LayoutView::printBoard()
{
	cout << "Display Board:" << endl;
	
	cout << "L";

	for (int i = 0; i < (int)board->getBoard()->size(); i++)
	{
		cout << " " << board->getBoard()->operator[](i).first << "-" << board->getBoard()->operator[](i).second << " ";
	}

	cout << "R" << endl;
}
