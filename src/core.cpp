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
* @file core.cpp
*
* @brief Core class
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <tuple>

#include "gameboard.h"
#include "core.h"

using namespace std;

/*
@brief default constructor
*/
Core::Core() {
	
}

/*
@brief allocates memory for other classes
*/
GameBoard * Core::alloc(GameBoard * gb, int size, short int AI) {
	// use default constructor
	if (size == 0) 
		gb = new GameBoard;
	else 
		gb = new GameBoard(size, AI);

	return gb;	
}

/*
@brief Deletes game classes
*/
GameBoard * Core::destroy(GameBoard * gb) {
	// delete only existing objects
	if (gb != NULL) {
		delete gb;
		gb = NULL;	
	}

	return gb;
}

/*** End of file gameboard.cpp ***/