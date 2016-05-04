/*************************************************************
* Project name: HRA2016
* File: square.cpp
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file square.cpp
*
* @brief Squares behaviour
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>

#include "square.h"

using namespace std;

// Square constructor
Square::Square() {
	owner = 0;
}

/*** End of file square.cpp ***/