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

#include <iostream>

#include "gameboard.h"

using namespace std;

//Default Gameboard constructor
GameBoard::GameBoard() {
	BlackOnTurn = true;
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
}

//Overloaded Gameboard constructor with input size(val)
GameBoard::GameBoard(short int val) {
	BlackOnTurn = true;
	size = val;
	rght = 1;
	lft = -1;
	rghtop = -val + 1;
	lftop = -val - 1;
	top = -val,
	bot = val;
	lfbot = val - 1;
	rghbot = val + 1;
	mid = val - 1 * val / 2; // to get position from which I can initialize stones
}

/*** End of file gameboard.cpp ***/