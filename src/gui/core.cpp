/*************************************************************
* Project name: HRA2016
* File: core.cpp
* Last change: 09.05.2016 01:13
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file core.cpp
*
* @brief Core class
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <tuple>

#include "gameboard.h"
#include "ai.h"
#include "core.h"


using namespace std;


/*
@brief allocates memory for other classes
*/
tuple<GameBoard *, AI *> Core::alloc(GameBoard * gb, AI * ai, int size, int AItype) {
	gb = new GameBoard(size, AItype);

	if (gb->enemyAI)
		ai = new AI();

	return make_tuple(gb, ai);
}

/*
@brief Deletes game classes
*/
tuple<GameBoard *, AI *> Core::destroy(GameBoard * gb, AI * ai) {
	// delete only existing objects
	if (gb != NULL) {
		delete gb;
		gb = NULL;	
	}

	if (ai != NULL) {
		delete ai;
		ai = NULL;
	}

	return make_tuple(gb, ai); 
}

/*** End of file gameboard.cpp ***/