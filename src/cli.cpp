#include <iostream>
#include <string>
#include "gameboard.h"
#include "square.h"

using namespace std;


/*
@todo add score, active player, ...
@brief gameboard print
*/
void printGameBoard(GameBoard gb, Square sq[]) {

	int white = 0, black = 0, b_score, w_score;

	// "osetreni" deleni nulou  
	if (white == 0) white = 1;
	if (black == 0) black = 1;

	/*
	*  vypocet skore // @todo add score calculation to the core - any class
	*/
	b_score = black * 100 / white;
	w_score = white * 100 / black;

	cout << "\n    Turn: " << ((gb.BlackOnTurn) ? "Black" : "White");
	cout << "\t\tScore: " << "Black " << 127 << " | White " << 57 << endl; //@todo replace PH values for score

	cout << "\n      ";
	for (short int i = 0; i < gb.size; ++i) {
		if (i < 9)
			cout << i + 1 << "   ";
		else
			cout << i + 1 << "  ";
	}

	for (short int k = 0; k < gb.size; ++k) {
		cout << "\n    +";
		for (int i = 0; i < gb.size; ++i)
			cout << "---+";

		if (k < 9)
			cout << "\n  " << k + 1 << " |";
		else
			cout << "\n " << k + 1 << " |";


		for (int j = 0; j < gb.size; ++j) {
			if (sq[k*gb.size + j].owner != 0)
				if (sq[k*gb.size + j].owner != 3)
					cout << " " << ((sq[k*gb.size + j].owner == 1) ? "O" : "X") << " |";
				else
					cout << " " << "!" << " |";    // owner = 3 is placeable position
			else
				cout << "   |";
		}

	}
	cout << "\n    +";
	for (int i = 0; i < gb.size; ++i)
		cout << "---+";
	cout << "\n";
}

/*
* @brief parse command with up to 3 parts
*/
void parseCmd(string cmd, string &first, string &second, string &third) {
	size_t index = 0;

	if ((index = cmd.find(" ")) != string::npos) {
		first = cmd.substr(0, index);
		cmd.erase(0, index + strlen(" "));
		cout << cmd << endl;
		if ((index = cmd.find(" ")) != string::npos) {
			second = cmd.substr(0, index);
			cmd.erase(0, index + strlen(" "));
			if ((index = cmd.find(" ")) != string::npos) {
				third = cmd.substr(0, index);
				cmd.erase(0, index + strlen(" "));
			}
			else
				third = cmd;
		}
		else
			second = cmd;
	}
	else 
		first = cmd;
}


int main() {
	string input, command;
	string arg1 = "", arg2 = "";

	cout << "\nVita vas hra Reversi.\nPro ukonceni zadejte prikaz \"exit\", pro napovedu \"help\".\n";
	cout << "\nZadejte prikaz:  \b";

	while (getline(cin, input)) {
		parseCmd(input, command, arg1, arg2);

		if (command == "exit") {
			cout << "\nKoncim . . . ";
			break;
		}
		else if (command == "help") {
			cout << "\n    Zde se zavola napoveda\n";
		}
		else if (command == "new") {
			// command is alone, using default new game settings
			if (arg1 == "") {
				// gameboard size 8
				GameBoard gb(8);
				// therefore 64 squares
				Square squares[64];
				// test
				squares[5].owner = 1;
				squares[6].owner = 2;
				squares[63].owner = 3;
				// print current state of the game
				printGameBoard(gb, squares);
			}
			// this may be useful later for checking if string is digit
			// if ((arg1.find_first_not_of("0123456789") == string::npos))
		}
		else {
			cout << "\n\tneznamy prikaz\n";
		}
		// @todo - broken 
		/*else if (command == "put" || command == "p" || (command.find_first_not_of("0123456789") == string::npos)) {
			// only coords have been detected (example: 4 5)
			if (arg1.find_first_not_of("0123456789") == string::npos) {
				int putHere, coord1, coord2;
				// convert to integer
				coord1 = stoi(command);
				coord2 = stoi(arg1);
				// decrement preparation (internal coords lower by 1)
				coord1--;
				coord2--;
				// final coord
				//@todo change 8 to gb.size, now it cant be reached
				putHere = coord1 * 8 + coord2;

				cout << "vlozim sutr na index: " << putHere << " a vytisknu stav\n";
			}
			cout << "vlozim novy sutr a vytisknu stav\n";
			//printGameBoard(gb, squares);
		}
		*/


		cout << "\nZadejte prikaz:  \b";
	}

	return 0;

	// older code
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
	// test
	squares[5].owner = 1;
	squares[6].owner = 2;
	squares[63].owner = 3;

	printGameBoard(gb, squares);
	
    return 0;
}
