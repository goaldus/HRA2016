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
#include <algorithm>
#include <tuple>

#include "gameboard.h"

using namespace std;

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

bool GameBoard::isBorder(short int dir, short int pos)
{
	//PRAVY OKRAJ
	if (pos % size == size - 1)
		dir = -dir;
	//LEVY OKRAJ
	else if (pos % size != 0)
		return false;

	if (dir == rghtop) return true;
	if (dir == rght) return true;
	if (dir == rghbot) return true;
}

/*
@brief Returns AIType number
*/
short int GameBoard::getAIType()
{
	return AItype;
}

/*
@brief Returns available indexes
*/
vector<short int> GameBoard::getVec(short int num) {
	if (num == WHITE)
		return whites;
	else if (num == BLACK)
		return blacks;
	else // num == AVAIL, 
		return available;

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
	remfromVec(available, index);

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
void GameBoard::checkNextSq(short int pos, short int dir, short int enemy, short int me)
{
	short int index = pos + dir;

	if (index >= size*size || isBorder(dir, pos) ||index < 0 || grid[index] == me || grid[index] == AVAIL) return;
	else
	{
		if (grid[index] == NONE)
		{	/*SEND DIRECTION AND LAST POSITION SO IF HE PLANTS HE CAN GO FROM AVAILABLE POS TO HIS DISC*/
			grid[index] = AVAIL;
			available.push_back(index);
		}
		/*else if (grid[index] == AVAIL)
		{

		}*/
		else	checkNextSq(index, dir, enemy, me);
	}
}

/*
@brief This function checks possibilities to end and then calls function checkNextSq()
*/
void GameBoard::checkFirstSq(short int pos, short int dir)
{
	short int index = pos + dir;
	short int enemy;
	short int me;

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

	if (index >= size*size || index < 0 || isBorder(dir, pos) || grid[index] == me) return; // OUT OF FIELD? OR DO I OWN THIS DISC? THEN GO TO HELL
	else
		if (grid[index] == NONE || grid[index] == AVAIL) return; // IS FIRST SQUARE EMPTY OR IS ALREADY SET ON AVAIL? THEN QUIT MAN!
		else //NOT EMPTY AND NOT MINE SO GO FOR TESTING
		checkNextSq(index, dir, enemy, me);
}

void GameBoard::checkDirections(short int pos)
{
	checkFirstSq(pos, top);
	checkFirstSq(pos, rghtop);
	checkFirstSq(pos, rght);
	checkFirstSq(pos, rghbot);
	checkFirstSq(pos, bot);
	checkFirstSq(pos, lfbot);
	checkFirstSq(pos, lft);
	checkFirstSq(pos, lftop);
}

/*
@brief Function sets possible places to indicate square availability to user
*/
void GameBoard::setAvailables()
{
	// reset available squares
	for (unsigned i = 0; i < available.size(); i++)
		grid[available[i]] = NONE;
	available.clear();

	vector<short int> *vecptr;
	if (BlackOnTurn)
		vecptr = &blacks;
	else
		vecptr = &whites;

	for (unsigned i = 0; i < (*vecptr).size(); i++)
		checkDirections((*vecptr)[i]);
}

/*
@brief Returns score for both players.
*/
void GameBoard::calcScore(int &b_score, int &w_score) {
	w_score = whites.size();
	b_score = blacks.size();

	/* bevare of division by 0 
	if (white_count == 0) white_count = 1;
	if (black_count == 0) black_count = 1;

	b_score = black_count * 100 / white_count;
	w_score = white_count * 100 / black_count;*/
}

/*
@brief gameboard destructor
*/
GameBoard::~GameBoard() {
	delete[] grid;
}

void GameBoard::remfromVec(vector<short int> &vec, int index)
{
	vector<short int>::iterator pos = find(vec.begin(), vec.end(), index);
	if (pos != vec.end()) // == myVector.end() means the element was not found
		vec.erase(pos);
}

void GameBoard::pushToVector(bool white, short int num)
{
	if (white)
		whites.push_back(num);
	else
		blacks.push_back(num);
}

void GameBoard::clearVectors()
{
	whites.clear();
	blacks.clear();
	available.clear();
}




/*** End of file gameboard.cpp ***/