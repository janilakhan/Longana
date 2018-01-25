/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<iostream> 
#include<utility>
#include"Layout.h"

class LayoutView
{
public:
	// The Constructor and Destructor of this class
	LayoutView();
	~LayoutView();

	// Sets the board
	bool setBoard(Layout * newBoard);

	// Function to print the values of the board
	void printBoard();

private:
	// Pointer to the board
	Layout * board;
};

