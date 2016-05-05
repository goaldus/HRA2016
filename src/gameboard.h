/*************************************************************
* Project name: HRA2016
* File: gameboard.h
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file gameboard.h
*
* @brief Header file for command line main.
* @author Vilem Jelen, Ondrej Molnar
*/

#pragma once

#include <vector>

/* grid square states  */
#define NONE  0
#define WHITE 1
#define BLACK 2
#define AVAIL 3

class GameBoard {
	short int rght;
	short int lft;
	short int rghtop;
	short int lftop;
	short int top;
	short int bot;
	short int lfbot;
	short int rghbot;
	short int mid;
	short int AItype;
	std::vector<short int> whites;
	std::vector<short int> blacks;
	std::vector<short int> available;

public:
	short int size;
	short int * grid;
	bool BlackOnTurn;
	bool enemyAI;
	GameBoard();
	GameBoard(short int, short int);
	short int getAIType();

	void placeStone(int);
	void nextTurn();
	void checkPlace(short int, short int, short int, short int);
	void neco(short int);
	void pes(short int, short int);
	void setAvailables();
	void calcScore(int &, int &);

	//~GameBoard() { std::cout << "Gameboard destroyed\n"; }

};

/*** End of file gameboard.h ***/