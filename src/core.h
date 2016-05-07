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


class Core {

public:
	Core();
	tuple<GameBoard *, AI *> Core::alloc(GameBoard *, AI *, int, short int);
	tuple<GameBoard *, AI *> Core::destroy(GameBoard *, AI *);
};

/*** End of file core.h ***/