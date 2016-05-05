/*************************************************************
* Project name: HRA2016
* File: core.cpp
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
* @brief Core class
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <tuple>

#include "square.h"
#include "gameboard.h"
#include "core.h"

using namespace std;

//Default constructor
core::core() {
	
}

/*
@brief Constructs game classes
*/
tuple<GameBoard *, Square **> core::alloc(GameBoard * gb, Square ** sq, int size, short int AI) {
	// use default constructor
	if (size == 0) {
		sqSize = STD_SQ_SIZE;
		gb = new GameBoard;
	}
	else {
		sqSize = size * size;
		gb = new GameBoard(size, AI);
	}
	// allocate memory for array of squares
	sq = new Square*[sqSize];
	for (int i = 0; i < sqSize; ++i)
		sq[i] = new Square;

	return make_tuple(gb, sq);	
}

/*
@brief Deletes game classes
*/
tuple<GameBoard *, Square **> core::destroy(GameBoard * gb, Square ** sq) {
	// delete only existing objects
	if (gb != NULL) {
		delete gb;

		for (int i = 0; i < sqSize; ++i)
			delete sq[i];
		delete[] sq;

		gb = NULL;
		sq = NULL;
	}
	return make_tuple(gb, sq);
}

/*** End of file gameboard.cpp ***/