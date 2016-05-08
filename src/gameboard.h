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
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

/* grid square states  */
#define NONE  0
#define WHITE 1
#define BLACK 2
#define AVAIL 3

using namespace std;

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
	std::vector <std::pair <short int, short int> > available;
	std::vector <std::pair<short int, short int> >::iterator it;

public:
	short int size;
	short int * grid;
	bool BlackOnTurn;
	bool enemyAI;
	GameBoard(short int, short int);
	short int getAIType();
	vector<short int> getVec(short int);

	void placeStone(short int);
	void nextTurn();
	void checkNextSq(short int, short int, short int, short int);
	void checkDirections(short int);
	void checkFirstSq(short int, short int);
	void setAvailables();
	void calcScore(int &, int &);
	bool isBorder(short int, short int);
	void remfromVec(std::vector<short int> &, int);
	void clearVectors();
	void pushToVector(bool, short int);
	void changeStones(short int index);
	void replaceStones(short int index, short int dir);
	std::vector <std::pair <short int, short int> > GameBoard::getAvail();
	~GameBoard();

};

#endif // GAMEBOARD_H
/*** End of file gameboard.h ***/