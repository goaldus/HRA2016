/*************************************************************
* Project name: HRA2016
* File: square.h
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file square.h
*
* @brief Header file for squares in gameboard.
* @author Vilem Jelen, Ondrej Molnar
*/

#pragma once

///Properties of squares
class Square {

public:
	Square();
	short int owner;

};

/*** End of file square.h ***/