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

//! A GameBoard class 
/*!
This class is representing board and used for all operations
with disks and the board itself.
*/
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
	//! A constructor.
	/*!
	Initializes values for GameBoard class.
	\param size int of the GB
	\param AItype int of enemy player
	*/
	GameBoard(int, int);
	//! A copy constructor.
	/*!
	Clones GB into new GB.
	\param obj old GameBoard
	*/
	GameBoard(const GameBoard &obj);
	//! Returns type of AI in actual game.
	/*!
	\return int type of enemy player
	*/
	int getAIType();
	//! Return one of vectors used in GB.
	/*!
	Initializes values for GameBoard class.
	\param num int for vector choosing
	\return vector int
	*/
	vector<int> getVec(int);
	//! Place disk on board.
	/*!
	\param index int position in GB grid
	*/
	void placeStone(int);
	//! Changes turn to next player
	void nextTurn();
	//! Function sets possible places to indicate square availability to user
	void setAvailables();
	//! Returns score for both players.
	void calcScore(int &, int &);
	void remfromVec(std::vector<int> &, int);
	void clearVectors();
	void pushToVector(bool, int);
	std::vector <std::pair <int, int> > getAvail();
	bool checkEnd();
	bool noTurn();
	//! A destructor
	/*!
	Deletes grid data.
	*/
	~GameBoard();

};

#endif // GAMEBOARD_H
/*** End of file gameboard.h ***/