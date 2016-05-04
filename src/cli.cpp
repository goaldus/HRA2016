/*************************************************************
* Project name: HRA2016
* File: cli.cpp
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file cli.cpp
*
* @brief Main file for command line run.
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <string>
#include <algorithm>

#include "gameboard.h"
#include "square.h"
#include "interface.h"

using namespace std;

#define STD_SQ_ARR 64

#ifdef _WIN32
#include <Windows.h>
void SetWindow(int Width, int Height) 
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}
#endif

bool is_digits(const std::string &str)
{
	return all_of(str.begin(), str.end(), ::isdigit); // C++11
}

int main() {

#ifdef _WIN32
	SetWindow(80, 31);
#endif

	string input, command;
	string arg1 = "", arg2 = "";
	GameBoard * gb = NULL;
	Square ** squares = NULL;
	Interface *inface = new Interface();

	while (getline(cin, input)) {
		inface->parseCmd(input, command, arg1, arg2);

		if (command == "exit") {
			cout << "\nKoncim . . . ";
			break;
		}
		else if (command == "help") {
			inface->printHelp();
		}
		else if (command == "new") {
			// command is alone, using default new game settings
			if (arg1 == "") {
				// deafault sizes
				gb = new GameBoard;
				// again using deafult size
				squares = new Square*[STD_SQ_ARR];
				for (int i = 0; i < STD_SQ_ARR; ++i)
					squares[i] = new Square;
			}
			else if (is_digits(arg1) || is_digits(arg2)) {
				int AItype = 0;
				if (is_digits(arg1))
					arg2 = arg1;
				else {
					if (arg1 == "easy")
						AItype = 1;
					else if (arg1 == "hard")
						AItype = 2;
					else {
						inface->error("Chybna obtiznost AI. Dostupne jsou: easy a hard.");
						continue;
					}
					if (arg2 == "") arg2 = "8";
				}
				int gbsize = stoi(arg2);
				// allow only these sizes
				if (gbsize != 6 && gbsize != 8 && gbsize != 10 && gbsize != 12) {
					inface->error("Nepovolena velikost herniho pole. Povolene jsou: 6, 8, 10, 12.");
					continue;
				}
				int arrsize = gbsize * gbsize;
				gb = new GameBoard(gbsize, AItype);
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
			inface->printBoard(gb, squares);
		}
		else if (command == "put" || command == "p" || is_digits(command)) {
			if (gb == NULL) {
				inface->error("Neprobiha zadna hra, nelze polozit kamen.");
				continue;
			}

			int coord1 = -1, coord2 = -1;

			// only coords have been detected (example: 4 5)
			if (is_digits(command) && is_digits(arg1) && arg1 != "") {
				// convert to integer
				coord1 += stoi(command);
				coord2 += stoi(arg1);
			}
			// command example: put 4 5 || p 4 5
			else if (is_digits(arg1) && is_digits(arg2) && arg1 != "" && arg2 != "") {
				// convert to integer
				coord1 += stoi(arg1);
				coord2 += stoi(arg2);
			}
			else {
				inface->error("Zadan put bez souradnic. pro napovedu: help");
				continue;
			}
			// out of bounds control
			if ((coord1 * gb->size + coord2) < 0 || (coord1 * gb->size + coord2) >= (gb->size*gb->size)
				|| coord1 < 0 || coord1 > gb->size || coord2 < 0 || coord2 > gb->size) {
				inface->error("Souradnice mimo herni plochu, nelze polozit kamen.");
				continue;
			}
			// empty square, puts stone and changes turn
			if (squares[coord1 * gb->size + coord2]->owner == 0) {
				squares[coord1 * gb->size + coord2]->owner = (gb->BlackOnTurn ? 2 : 1);
				// change turn
				gb->BlackOnTurn = !gb->BlackOnTurn;
				// tisk stavu
				inface->printBoard(gb, squares);
			}
			else {
				cout << "\n\tNelze polozit, uz zde lezi kamen.\n";
			}
		}
		else {
			cout << "\n\tNeznamy prikaz\n";
		}

		// print when waiting for new command
		cout << "\nZadejte prikaz:  \b";
	}

	// mela by se provest dealokace objektu, neco jako squares delete[]; 
	
	return 0;

}

/*** End of file cli.cpp ***/
