/*************************************************************
* Project name: HRA2016
* File: gameboard.cpp
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file gameboard.cpp
*
* @brief Gameboard settings.
* @author Vilem Jelen, Ondrej Molnar
*/

#include <vector>
#include <iostream>
#include <tuple>

#include "gameboard.h"

using namespace std;


bool checkDirections(short int dir, bool invert)
{
	if (invert)
		dir = -dir;
	switch (dir)
	{
	case -5: return true;
	case 1: return true;
	case 7: return true;
	}
	return false;
}

//Default Gameboard constructor
GameBoard::GameBoard() {
	BlackOnTurn = true;
	enemyAI = false;
	size = 8;
	/*Grid*/
	int arrsize = size*size; 
	grid = new short int[arrsize];
	for (int i = 0; i < arrsize; ++i)
		grid[i] = NONE;
	/*Directions*/
	rght = 1;
	lft = -1;
	rghtop = -7;
	lftop = -9;
	top = -8,
	bot = 8;
	lfbot = 7;
	rghbot = 9;
	mid = 4; // to get position from which I can initialize stones
	whites.reserve(7 * size);
	blacks.reserve(7 * size);
	available.reserve(10);
	/* Initialize disk positions */
	short int offset = mid * (size - 1);

	grid[offset - 1] = WHITE;
	grid[offset] = BLACK;
	grid[offset + size] = WHITE;
	grid[offset + size - 1] = BLACK;

	whites.push_back(offset - 1);
	whites.push_back(offset + size);
	blacks.push_back(offset);
	blacks.push_back(offset + size - 1);
}

//Overloaded Gameboard constructor with input size(val)
GameBoard::GameBoard(short int size, short int AItype) {
	BlackOnTurn = true;
	enemyAI = (AItype != 0) ? true : false;
	this->AItype = AItype;
	this->size = size;
	/*Grid*/
	int arrsize = size*size;
	grid = new short int[arrsize];
	for (int i = 0; i < arrsize; ++i)
		grid[i] = NONE;
	/*Directions*/
	rght = 1;
	lft = -1;
	rghtop = -size + 1;
	lftop = -size - 1;
	top = -size,
	bot = size;
	lfbot = size - 1;
	rghbot = size + 1;
	mid = size - 1 * size / 2;
	/*Vector reservation*/
	whites.reserve(7 * size);
	blacks.reserve(7 * size);
	available.reserve(10);
	/* Initialize disk positions */
	short int offset = mid * (size - 1);

	grid[offset - 1] = WHITE;
	grid[offset] = BLACK;
	grid[offset + size] = WHITE;
	grid[offset + size - 1] = BLACK;

	whites.push_back(offset - 1);
	whites.push_back(offset + size);
	blacks.push_back(offset);
	blacks.push_back(offset + size - 1);
}

/*
@brief Returns AIType number
*/
short int GameBoard::getAIType()
{
	return AItype;
}


/*
@brief Function places stone to gameboard's square and adds index to vector so I can work only with selected color
*/
void GameBoard::placeStone(int index)
{
	if (BlackOnTurn)
	{
		grid[index] = BLACK;
		blacks.push_back(index);
	}
	else
	{ 
		grid[index] = WHITE;
		whites.push_back(index);
	}

	nextTurn();
}

/*
@brief Changes turn to next player
*/
void GameBoard::nextTurn()
{
	BlackOnTurn = !BlackOnTurn;
}

/*
@brief Checks square and if it is empty than show user that he can plant there
*/
void GameBoard::checkPlace(short int pos, short int dir, short int enemy, short int me)
{
	short int index = pos + dir;
	bool invert = false;

	if (index % size == 0)
		invert = true;

	if (index >= size*size || checkDirections(dir, invert) || grid[index] == me) return;
	else
	{
		if (grid[index] == NONE)
		{
			grid[index] = AVAIL;
			available.push_back(index);
		}
		else
			checkPlace(index, dir, enemy, me);
	}
}

/*
@brief This function checks possibilities to end and then calls function checkPlace()
*/
void GameBoard::pes(short int pos, short int dir)
{
	short int index = pos + dir;
	short int enemy;
	short int me;
	bool invert = false;

	if (BlackOnTurn)
	{
		enemy = WHITE;
		me = BLACK;
	}
	else
	{
		enemy = BLACK;
		me = WHITE;
	}

	if (index % size == 0)
		invert = true;

	if (index >= size*size || checkDirections(dir, invert)  || grid[index] == me) return; // OUT OF FIELD? OR DO I OWN THIS DISC? THEN GO TO HELL
	else
		if (grid[index] == NONE || grid[index] == AVAIL) return; // IS FIRST SQUARE EMPTY? THEN END MAN!
		else //NOT EMPTY AND NOT MINE SO GO FOR TESTING
		checkPlace(index, dir, enemy, me);
}

void GameBoard::neco(short int pos)
{
	pes(pos, top);
	pes(pos, rghtop);
	pes(pos, rght);
	pes(pos, rghbot);
	pes(pos, bot);
	pes(pos, lfbot);
	pes(pos, lft);
	pes(pos, lftop);
}

/*
@brief Function sets possible places to indicate square availability to user
*/
void GameBoard::setAvailables()
{
	// reset available squares
	for (unsigned i = 0; i < available.size(); i++)
	{
		if (grid[available[i]] == AVAIL)
		grid[available[i]] = NONE;
	}
		
	available.clear();
	vector<short int> *vecptr;
	if (BlackOnTurn)
		vecptr = &blacks;
	else
		vecptr = &whites;

	for (unsigned i = 0; i < (*vecptr).size(); i++)
		neco((*vecptr)[i]);
}

/*
@brief Returns score for both players.
*/
void GameBoard::calcScore(int &b_score, int &w_score) {
	int white_count = whites.size();
	int	black_count = blacks.size();

	// bevare of division by 0 
	if (white_count == 0) white_count = 1;
	if (black_count == 0) black_count = 1;

	b_score = black_count * 100 / white_count;
	w_score = white_count * 100 / black_count;
}

/*** End of file gameboard.cpp ***/