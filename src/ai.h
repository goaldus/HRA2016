/*************************************************************
* Project name: HRA2016
* File: ai.h
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file ai.h
*
* @brief Header file for AI class.
* @author Vilem Jelen, Ondrej Molnar
*/

#pragma once

using namespace std;


class AI {
	short int random(GameBoard *);
	int genRandom(int, int);

public:
	AI();
	short int run(GameBoard *);
	
};

/*** End of file ai.h ***/