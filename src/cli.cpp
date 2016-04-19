#include<iostream>

using namespace std;


class GameBoard {
    short int rght = 1;
    short int lft = -1;
    short int rghtop = -7;
    short int lftop = -9;
    short int top = -8;
    short int bot = 8;
    short int lfbot = 7;
    short int rghbot = 9;
    short int mid = 8 - 1 * 8 / 2; // to get position from which I can initialize stones

public:
	short int size = 8;
	GameBoard();
	GameBoard(short int val);
	void printSides();
};

//Default Gameboard constructor
GameBoard::GameBoard() {
	// empty
}

//Overloaded Gameboard constructor with input size(val)
GameBoard::GameBoard(short int val) {
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

//Properties of squares
class Square {
	short int owner;

public:
	Square();
	friend void printGameBoard(GameBoard gb, Square sq); // @todo temporary friend for testing
};

// Square constructor
Square::Square() {
	owner = 0;
}


/*
@todo add score, active player, ...
@brief gameboard print
*/
void printGameBoard(GameBoard gb, Square sq) {

	cout << "\n      ";
	for (short int i = 0; i < gb.size; ++i) {
		if (i < 9)
			cout << i + 1 << "   ";
		else 
			cout << i + 1 << "  ";
	}
		
	for (short int j = 0; j < gb.size; ++j) {
		cout << "\n    +";
		for (int i = 0; i < gb.size; ++i)
			cout << "---+";

		if (j < 9)
			cout << "\n  " << j + 1 << " |";
		else 
			cout << "\n " << j + 1 << " |";

		for (int j = 0; j < gb.size; ++j) { // @todo add character for stone if square[index].owner = 1;
			/*if (sq.owner != 0) 
				cout << " " << ((sq.owner == 1) ? "O" : "X") << " |";
			else*/
				cout << "   |";
		}

	}
	cout << "\n    +";
	for (int i = 0; i < gb.size; ++i)
		cout << "---+";
	cout << "\n";
}



int main() {
	short int a = 8;

    cout << "Zmacknete klavesu pro zvoleni velikosti pole:\n6 - Q, 8 - any other key, 10 - W, 12 - E\n";

	int gotKey = cin.get();
	if (gotKey == 81 || gotKey == 113) { // key Q,q
		a = 6;
	}
	else if (gotKey == 87 || gotKey == 119) { // key W,w
		a = 10;	
	}
	else if (gotKey == 69 || gotKey == 101) { // key E,e
		a = 12;
	}
			
	GameBoard gb(a);
	/*
	@todo VS2015 cannot compile Square squares[gb.size*gb.size]; without constant size of array
	@brief square objects creation
	*/  
    Square squares[64]; // @todo change "64" to "gb.size*gb.size" 
    cout << "Velikost pole: " << gb.size << "x" << gb.size << endl;
    gb.printSides();

	printGameBoard(gb, squares[5]);
	
    return 0;
}
