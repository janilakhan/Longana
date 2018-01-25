/***********************************************************
* Name:  Janila Khan                                       *
* Project : Project 1 / Longana Game			           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 17, 2017                                  *
************************************************************/

#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<deque>
#include<vector>
#include<utility>
#include "Layout.h"
#include "Stock.h"
#include "Player.h"

class SaveFile
{
public:
	// The Constructor and Destructor of the class
	SaveFile();
	~SaveFile();

	// The function to open the file from a text file
	bool openSavedRound(string file, int &t_score, int &r_num, vector<pair<int,int>> * v, int &c_score, vector<pair<int,int>> * w, int &h_score, deque<pair<int,int>> * x, vector<pair<int,int>> * y, bool &player, int &current, bool &pass);

	// The function to save the round into a text file
	void saveRound(string file, int t_score, int r_num, Player * computer, int c_score, Player * human, int h_score, Layout * board, Stock * boneyard, int current);
};

