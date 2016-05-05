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

#include "square.h"
#include "gameboard.h"

using namespace std;

//Default Gameboard constructor
GameBoard::GameBoard() {
	BlackOnTurn = true;
	enemyAI = false;
	size = 8;
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
}

//Overloaded Gameboard constructor with input size(val)
GameBoard::GameBoard(short int size, short int AItype) {
	BlackOnTurn = true;
	enemyAI = (AItype != 0) ? true : false;
	this->AItype = AItype;
	this->size = size;
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
}

/*
@brief Returns AIType number
*/
short int GameBoard::getAIType()
{
	return AItype;
}

/*
@brief Sets first stones to gameboard (game preparation)
*/
void GameBoard::Init(Square ** sq)
{
	short int offset = mid * (size - 1);
	
	sq[offset - 1]->owner = 1;
	sq[offset]->owner = 2;
	sq[offset + size]->owner = 1;
	sq[offset + size - 1]->owner = 2;

	whites.push_back(offset - 1);
	whites.push_back(offset + size);
	blacks.push_back(offset);
	blacks.push_back(offset + size - 1);

}

/*
@brief Function places stone to gameboard's square and adds index to vector so I can work only with selected color
*/
void GameBoard::placeStone(Square *sq, int num)
{
	if (BlackOnTurn)
	{
		sq->owner = 2;
		blacks.push_back(num);
	}
	else
	{ 
		sq->owner = 1;
		whites.push_back(num);
	}
}

/*
@brief Changes turn to next player
*/
void GameBoard::nextTurn()
{
	BlackOnTurn = !BlackOnTurn;
}

/*
@brief Checks square and if he is empty than show user that he can plant there
*/
void GameBoard::checkPlace(short int pos, short int dir, Square **sq, short int enemy, short int me)
{
	short int index = pos + dir;

	if (index >= size*size || sq[index]->owner == me) return;
	else
	{
		if (sq[index]->owner == 0)
		{
			sq[index]->owner = 3;
			available.push_back(index);
		}
		else
			checkPlace(index, dir, sq, enemy, me);
	}
}

/*
@brief This function checks possibilities to end and then calls function checkPlace()
*/
void GameBoard::pes(short int pos, short int dir, Square **sq)
{
	short int index = pos + dir;
	short int enemy;
	short int me;

	if (BlackOnTurn)
	{
		enemy = 1;
		me = 2;
	}
	else
	{
		enemy = 2;
		me = 1;
	}
	if (index >= size*size || sq[index]->owner == me) return; // OUT OF FIELD? OR DO I OWN THIS DISC? THEN GO TO HELL
	else
		if (sq[index]->owner == 0 || sq[index]->owner == 3) return; // IS FIRST SQUARE EMPTY? THEN END MAN!
		else //NOT EMPTY AND NOT MINE SO GO FOR TESTING
		checkPlace(index, dir, sq, enemy, me);
}

void GameBoard::neco(short int pos, Square**squares)
{
	pes(pos, top, squares);
	pes(pos, rghtop, squares);
	pes(pos, rght, squares);
	pes(pos, rghbot, squares);
	pes(pos, bot, squares);
	pes(pos, lfbot, squares);
	pes(pos, lft, squares);
	pes(pos, lftop, squares);
}

void GameBoard::setAvailables(Square **squares)
{
	for (int i = 0; i < available.size(); i++)
	{
		if (squares[available[i]]->owner == 3)
		squares[available[i]]->owner = 0;
	}
		
	available.clear();
	vector<short int> *vecptr;
	if (BlackOnTurn)
		vecptr = &blacks;
	else
		vecptr = &whites;

	for (int i = 0; i < (*vecptr).size(); i++)
		neco((*vecptr)[i], squares);
}

/*** End of file gameboard.cpp ***/