/*************************************************************
* Project name: HRA2016
* File: save.cpp
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file save.cpp
*
* @brief Save class
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <tuple>

#include "gameboard.h"
#include "save.h"

using namespace std;

/*
@brief default constructor
*/
Save::Save() {
	step = 0;
	filename = "";
	data = NULL;
}

/*
@breif clears save for new use
*/
void Save::clear() {
	// save contains something
	if (data != NULL) {
		delete[] data;
	}
}

/*
@brief sets values for save when new game is created
*/
void Save::setupSave(GameBoard * gb) {
	
}


/*** End of file save.cpp ***/