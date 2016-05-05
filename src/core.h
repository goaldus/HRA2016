/*************************************************************
* Project name: HRA2016
* File: core.h
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file core.h
*
* @brief Header file for core class.
* @author Vilem Jelen, Ondrej Molnar
*/

#pragma once

using namespace std;

#define STD_SQ_SIZE 64


class core {
	int sqSize;

public:
	core();
	tuple<GameBoard *, Square **> core::alloc(GameBoard *, Square **, int, short int);
	tuple<GameBoard *, Square **> core::destroy(GameBoard *, Square **);
};

/*** End of file gameboard.h ***/