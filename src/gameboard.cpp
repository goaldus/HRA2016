#include <iostream>

#include "gameboard.h"

using namespace std;

//Default Gameboard constructor
GameBoard::GameBoard() {
	BlackOnTurn = true;
	size = 8;
	rght = 1;
	lft = -1;
	rghtop = -7;
	lftop = -9;
	top = -8,
	bot = 8;
	lfbot = 7;
	rghbot = 9;
	mid = 4; // to get position from which I can initialize stones
}

//Overloaded Gameboard constructor with input size(val)
GameBoard::GameBoard(short int val) {
	BlackOnTurn = true;
	size = val;
	rght = 1;
	lft = -1;
	rghtop = -val + 1;
	lftop = -val - 1;
	top = -val,
	bot = val;
	lfbot = val - 1;
	rghbot = val + 1;
	mid = val - 1 * val / 2; // to get position from which I can initialize stones
}

//Only for directions check
void GameBoard::printSides() {
	cout << "posun vlevo o: " << lft << endl;
	cout << "posun vpravo o: " << rght << endl;
	cout << "posun vlevo nahoru o: " << lftop << endl;
	cout << "posun vpravo nahoru o: " << rghtop << endl;
	cout << "posun dolu o: " << bot << endl;
	cout << "posun nahoru o: " << top << endl;
	cout << "posun vlevo dolu o: " << lfbot << endl;
	cout << "posun vpravo dolu o: " << rghbot << endl;
}
