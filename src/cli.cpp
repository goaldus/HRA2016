#include<iostream>

#include "gameboard.h"
#include "square.h"

using namespace std;


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
