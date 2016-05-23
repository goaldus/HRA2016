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

//! class representing Artificial Inteligence 
/*!
This class is used as a container for multiple AI algorithms.
Based on game settings it decides which algorithm will be used 
for computing position of disk to place as AI player.
*/
class AI {
	/// Choose random available position for disk
	int random(GameBoard *);
	/// Choose best position based on simple heuristic
	int simpleH(GameBoard *, Save *);
	/// Generate random number between two integer values
	int genRandom(int, int);
	/// Part of heuristic used in simpleH method
	double evalPos(int, GameBoard *);

public:
	//! Choose an algorithm to run AI with.
	/*!
	\param gb pointer on GameBoard class.
	\param save pointer on Save class.
	\return integer chosed position for new disk placed by AI
	*/
	int run(GameBoard *, Save *);

};

#endif // AI_H
/*** End of file ai.h ***/