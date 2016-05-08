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
#ifndef AI_H
#define AI_H

using namespace std;

class Save; // forward declaration 

class AI {
	short int random(GameBoard *);
	short int simpleH(GameBoard *, Save *);
	int genRandom(int, int);

public:
	AI();
	short int run(GameBoard *, Save *);
	~AI();
	
};

#endif // AI_H
/*** End of file ai.h ***/