/*************************************************************
* Project name: HRA2016
* File: gameboard.h
* Last change: 09.05.2016 01:13
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
	int rght;
	int lft;
	int rghtop;
	int lftop;
	int top;
	int bot;
	int lfbot;
	int rghbot;
	int mid;
	int AItype;
	std::vector<int> whites;
	std::vector<int> blacks;
	std::vector <std::pair <int, int> > available;
	std::vector <std::pair<int, int> >::iterator it;
	void changeStones(int);
	bool isBorder(int, int);
	void replaceStones(int, int);
	void checkFirstSq(int, int);
	void checkNextSq(int, int, int, int);
	void checkDirections(int);

public:
	int size;
	int * grid;
	bool BlackOnTurn;
	bool enemyAI;

	GameBoard(int, int);
	GameBoard(const GameBoard &obj);
	int getAIType();
	vector<int> getVec(int);
	void placeStone(int);
	void nextTurn();
	void setAvailables();
	void calcScore(int &, int &);
	void remfromVec(std::vector<int> &, int);
	void clearVectors();
	void pushToVector(bool, int);
	std::vector <std::pair <int, int> > getAvail();
	bool checkEnd();
	bool noTurn();
	~GameBoard();

};

#endif // GAMEBOARD_H
/*** End of file gameboard.h ***/