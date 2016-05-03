#include <iostream>
#include <string>
#include <algorithm>

#include "gameboard.h"
#include "square.h"

using namespace std;

#define STDSIZE 8
#define STD_SQ_ARR 64


/*
@todo add score, active player, ...
@brief gameboard print
*/
void printGameBoard(GameBoard * gb, Square * sq[]) {

	int white = 0, black = 0, b_score, w_score;

	// "osetreni" deleni nulou  
	if (white == 0) white = 1;
	if (black == 0) black = 1;

	/*
	*  vypocet skore // @todo add score calculation to the core - any class
	*/
	b_score = black * 100 / white;
	w_score = white * 100 / black;

	cout << "\n    Turn: " << ((gb->BlackOnTurn) ? "Black" : "White");
	cout << "\t\tScore: " << "Black " << 127 << " | White " << 57 << endl; //@todo replace PH values for score

	cout << "\n      ";
	for (short int i = 0; i < gb->size; ++i) {
		if (i < 9)
			cout << i + 1 << "   ";
		else
			cout << i + 1 << "  ";
	}

	for (short int k = 0; k < gb->size; ++k) {
		cout << "\n    +";
		for (int i = 0; i < gb->size; ++i)
			cout << "---+";

		if (k < 9)
			cout << "\n  " << k + 1 << " |";
		else
			cout << "\n " << k + 1 << " |";


		for (int j = 0; j < gb->size; ++j) {
			if (sq[k*gb->size + j]->owner != 0)
				if (sq[k*gb->size + j]->owner != 3)
					cout << " " << ((sq[k*gb->size + j]->owner == 1) ? "O" : "X") << " |";
				else
					cout << " " << "!" << " |";    // owner = 3 is placeable position
			else
				cout << "   |";
		}

	}
	cout << "\n    +";
	for (int i = 0; i < gb->size; ++i)
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


bool is_digits(const std::string &str)
{
	return all_of(str.begin(), str.end(), ::isdigit); // C++11
}

int main() {
	string input, command;
	string arg1 = "", arg2 = "";
	GameBoard * gb = NULL;
	Square ** squares = NULL;

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
				// deafault sizes
				gb = new GameBoard(STDSIZE);
				// again using deafult size
				squares = new Square*[STD_SQ_ARR];
				for (int i = 0; i < STD_SQ_ARR ; ++i)
					squares[i] = new Square;
			}
			else if (is_digits(arg1)) {
				int gbsize = stoi(arg1);
				// allow only these sizes
				if (gbsize != 6 && gbsize != 8 && gbsize != 10 && gbsize != 12) {
					cout << "\n\tNepovolena velikost herniho pole. Povolene jsou: 6, 8, 10, 12.\n";
					cout << "\nZadejte prikaz:  \b";
					continue;
				}
				int arrsize = gbsize * gbsize;
				gb = new GameBoard(gbsize);
				// allocate memory for array of squares
				squares = new Square*[arrsize];
				for (int i = 0; i < arrsize; ++i)
					squares[i] = new Square;
			}
			// initial stone formation for any board size
			squares[((gb->size / 2) - 1) * gb->size + ((gb->size / 2) - 1)]->owner = 1;
			squares[(gb->size / 2) * gb->size + (gb->size / 2)]->owner = 1;
			squares[((gb->size / 2) - 1) * gb->size + (gb->size / 2)]->owner = 2;
			squares[(gb->size / 2) * gb->size + ((gb->size / 2) - 1)]->owner = 2;
			// print current state of the game
			printGameBoard(gb, squares);
		}
		else if (command == "put" || command == "p" || is_digits(command)) {
			if (gb == NULL) {
				cout << "\n\tNeprobiha zadna hra, nelze polozit kamen.\n";
				cout << "\nZadejte prikaz:  \b";
				continue;
			}

			int coord1 = -1, coord2 = -1;

			// only coords have been detected (example: 4 5)
			if (is_digits(command) && is_digits(arg1)) {
				// convert to integer
				coord1 += stoi(command);
				coord2 += stoi(arg1);
			}
			// command example: put 4 5 || p 4 5
			else if (is_digits(arg1) && is_digits(arg2)) {
				// convert to integer
				coord1 += stoi(arg1);
				coord2 += stoi(arg2);
			}
			// out of bounds control
			if ((coord1 * gb->size + coord2) < 0 || (coord1 * gb->size + coord2) >= (gb->size*gb->size)) {
				cout << "\n\tSouradnice mimo herni plochu, nelze polozit kamen.\n";
				cout << "\nZadejte prikaz:  \b";
				continue;
			}
			// empty square, puts stone and changes turn
			if (squares[coord1 * gb->size + coord2]->owner == 0) {
				squares[coord1 * gb->size + coord2]->owner = (gb->BlackOnTurn ? 2 : 1);
				// change turn
				gb->BlackOnTurn ? gb->BlackOnTurn = false : gb->BlackOnTurn = true;
				// tisk stavu
				printGameBoard(gb, squares);
			}
			else {
				cout << "\n\tNelze polozit, uz zde lezi kamen.\n";
			}
		}
		else {
			cout << "\n\tneznamy prikaz\n";
		}

		// print when waiting for new command
		cout << "\nZadejte prikaz:  \b";
	}

	// mela by se provest dealokace objektu, neco jako squares delete[]; 

	return 0;

}
