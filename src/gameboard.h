#pragma once

/// gameboard description
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

public:
	short int size;
	bool BlackOnTurn;
	GameBoard();
	GameBoard(short int val);
	void printSides();
};