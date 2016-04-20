#include<iostream>

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

public:
	short int size;
	bool BlackOnTurn;
	GameBoard();
	GameBoard(short int val);
	void printSides();
};

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

//Properties of squares
class Square {
	short int owner;
	bool available;  // stone can be placed here

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

	cout << "\n    Turn: " << ((gb.BlackOnTurn) ? "Black" : "White");
	cout << "\t\tScore: " << "Black " << 127 << " | White " << 57 << endl; //@todo replace PH values for score

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
