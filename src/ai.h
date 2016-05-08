/*************************************************************
* Project name: HRA2016
* File: ai.h
* Last change: 09.05.2016 01:13
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
#ifndef AI_H
#define AI_H

using namespace std;

class Save; // forward declaration 

class AI {
	int random(GameBoard *);
	int simpleH(GameBoard *, Save *);
	int genRandom(int, int);
	double evalPos(int, GameBoard *);

public:
	AI();
	int run(GameBoard *, Save *);
	~AI();
	
};

#endif // AI_H
/*** End of file ai.h ***/