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
#include <utility>

#include "gameboard.h"

using namespace std;

//Overloaded Gameboard constructor with input size(val)
GameBoard::GameBoard(int size, int AItype) {
	BlackOnTurn = true;
	enemyAI = (AItype != 0) ? true : false;
	this->AItype = AItype;
	this->size = size;
	/*Grid*/
	int arrsize = size*size;
	grid = new int[arrsize];
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
	available.reserve(20);
	/* Initialize disk positions */
	int offset = mid * (size - 1);

	grid[offset - 1] = WHITE;
	grid[offset] = BLACK;
	grid[offset + size] = WHITE;
	grid[offset + size - 1] = BLACK;

	whites.push_back(offset - 1);
	whites.push_back(offset + size);
	blacks.push_back(offset);
	blacks.push_back(offset + size - 1);
}



bool GameBoard::isBorder(int dir, int pos)
{
	//LEFT BORDER
	if (pos % size == 0) {
		if (dir == lft) return true;
		if (dir == lftop) return true;
		if (dir == lfbot) return true;
	}
	//RIGHT BORDER
	else if (pos % size == size - 1)
	{
		if (dir == rght) return true;
		if (dir == rghtop) return true;
		if (dir == rghbot) return true;
	}

return false;
}

/*
@brief Returns AIType number
*/
int GameBoard::getAIType()
{
	return AItype;
}

/*
@brief Returns available indexes
*/
vector<int> GameBoard::getVec(int num) {
	if (num == WHITE)
		return whites;
	else if (num == BLACK)
		return blacks;
}

vector <pair <int, int> > GameBoard::getAvail() 
{
	return available;
}

struct isEqual
{
	isEqual(const int& a_wanted) : wanted(a_wanted) {}
	int wanted;
	bool operator()(const pair<int, int>& element)
	{
		return element.first == wanted;
	}
};


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

	changeStones(index);
	nextTurn();
}

void GameBoard::changeStones(int index)
{
	sort(available.begin(), available.end());
	it = find_if(available.begin(), available.end(), isEqual(index));

	while (it != available.end() && it->first == index)
	{
		replaceStones(index, it->second);
		it = available.erase(it);
	}
}

/*
@brief Function replaces stones till his own stone is found, then function ends
*/
void GameBoard::replaceStones(int index, int dir)
{
	int next = index - dir;
	vector<int> *vToSet;
	vector<int> *vToRem;
	int color;

	if (BlackOnTurn)
	{
		vToSet = &blacks;
		vToRem = &whites;
		color = BLACK;
	}
	else
	{
		vToSet = &whites;
		vToRem = &blacks;
		color = WHITE;
	}

	do
	{
		grid[next] = color;
		(*vToSet).push_back(next);
		remfromVec(*vToRem, next);
		next -= dir;
	} while (grid[next] != color);
}

/*
@brief Changes turn to next player
*/
void GameBoard::nextTurn()
{
	BlackOnTurn = !BlackOnTurn;
}

/*
@brief Checks square and if it is empty then show the user that he can plant there
*/
void GameBoard::checkNextSq(int pos, int dir, int enemy, int me)
{
	int index = pos + dir;

	if (index >= size*size || isBorder(dir, pos) || index < 0 || grid[index] == me) return;
	else
	{
		if (grid[index] == NONE)
		{	/*SEND DIRECTION AND LAST POSITION SO IF HE PLANTS HE CAN GO FROM AVAILABLE POS TO HIS DISC*/
			grid[index] = AVAIL;
			available.push_back(make_pair(index, dir));
		}
		else if (grid[index] == AVAIL)
		{
			available.push_back(make_pair(index, dir));
		}
		else	checkNextSq(index, dir, enemy, me);
	}
}

/*
@brief This function checks possibilities to end and then calls function checkNextSq()
*/
void GameBoard::checkFirstSq(int pos, int dir)
{
	int index = pos + dir;
	int enemy;
	int me;
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

	/*First square is taken or the position is invalid*/
	if (index >= size*size || index < 0 || isBorder(dir, pos) || grid[index] == me || grid[index] == NONE || grid[index] == AVAIL)
		return;
	else
		checkNextSq(index, dir, enemy, me);
		
}

void GameBoard::checkDirections(int pos)
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
	for (it = available.begin(); it != available.end(); ++it)
		grid[it->first] = NONE;
	available.clear();

	vector<int> *vecptr;
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

void GameBoard::remfromVec(vector<int> &vec, int index)
{
	vector<int>::iterator pos = find(vec.begin(), vec.end(), index);
	if (pos != vec.end()) // == myVector.end() means the element was not found
		vec.erase(pos);
}

void GameBoard::pushToVector(bool white, int num)
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

bool GameBoard::checkEnd()
{
	if (((blacks.size() + whites.size()) == size*size) || available.size() == 0)
		return true;
	else
		return false;
}

bool GameBoard::noTurn()
{
	if (available.size() == 0)
		return true;
	else
		return false;
}

/*** End of file gameboard.cpp ***/