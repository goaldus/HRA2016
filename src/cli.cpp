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
#include <tuple>

#include "square.h"
#include "gameboard.h"
#include "interface.h"
#include "core.h"
#include "save.h"

using namespace std;

#define STD_SQ_ARR 64

#ifdef _WIN32
#include <Windows.h>
void SetWindowSize(int width, int height) {
	_COORD coord;
	coord.X = width;
	coord.Y = height;

	_SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = height - 1;
	rect.Right = width - 1;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);      
	SetConsoleScreenBufferSize(handle, coord);             
	SetConsoleWindowInfo(handle, TRUE, &rect);             
}
#endif

bool is_digits(const string &str)
{
	if (str.empty())
		return false;
	return all_of(str.begin(), str.end(), ::isdigit); 
}

int main() {

	#ifdef _WIN32
	SetWindowSize(80, 31);
	#endif

	string input, command = "";
	string arg1 = "", arg2 = "";
	GameBoard * gb = NULL;
	Square ** squares = NULL;
	Core *core = new Core();
	Interface *inface = new Interface();
	Save * save = NULL;

	while (getline(cin, input)) {
		tie(command, arg1, arg2) = inface->parseCmd(input);

		if (command == "exit") {
			cout << "\nKoncim . . . ";
			break;
		}
		else if (command == "help") {
			inface->printHelp();
		}
		/******		new		******/	
		else if (command == "new") {
			// delete game in progress before creating new
			tie(gb, squares) = core->destroy(gb, squares);
			// command is alone, using default new game settings
			if (arg1.empty()) {
				tie(gb, squares) = core->alloc(gb, squares, 0, 0);				
			}
			else if (is_digits(arg1) || is_digits(arg2) || !arg1.empty()) {
				int AItype = 0;
				if (is_digits(arg1))
					arg2 = arg1;
				else {
					if (arg1 == "easy")
						AItype = 1;
					else if (arg1 == "hard")
						AItype = 2;
					else {
						inface->msg("Chybna obtiznost AI. Dostupne jsou: easy a hard.");
						continue;
					}
					if (arg2.empty()) arg2 = "8";
				}
				int gbsize = stoi(arg2);
				// allow only these sizes
				if (gbsize != 6 && gbsize != 8 && gbsize != 10 && gbsize != 12) {
					inface->msg("Nepovolena velikost herniho pole. Povolene jsou: 6, 8, 10, 12.");
					continue;
				}
				tie(gb, squares) = core->alloc(gb, squares, gbsize, AItype);
			}
			// initial stone formation for any board size
			gb->Init(squares);
			// print current state of the game
			inface->printBoard(gb, squares);
		}
		/******		put		******/
		else if (command == "put" || command == "p" || is_digits(command)) {
			if (gb == NULL) {
				inface->msg("Neprobiha zadna hra, nelze polozit disk.");
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
			else {
				inface->msg("Zadan put bez souradnic. pro napovedu: help");
				continue;
			}
			// out of bounds control
			if (coord1 < 0 || coord1 >= gb->size || coord2 < 0 || coord2 >= gb->size) {
				inface->msg("Souradnice mimo herni plochu, nelze polozit disk.");
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
				inface->msg("Nelze polozit, uz zde lezi disk.");
				continue;
			}
		}
		/******		open		******/
		else if (command == "open") {
			// should open game in new terminal window
		}
		/******		save		******/
		else if (command == "save" || command == "s") {
			if (gb == NULL) {
				inface->msg("Neprobiha zadna hra, nelze ulozit hru.");
				continue;
			}
			// arg1 is name for saved game
			if (!arg1.empty()) {
				// save game history into file: "saves/arg1"
			}
			else {
				// save game into file: "saves/number_of_save"
			}
		}
		/******		load		******/
		else if (command == "load" || command == "l") {
			if (!arg1.empty()) {
				// load game history from file: "saves/arg1"
			}
			else {
				inface->msg("Nebyl zadan nazev ulozene hry.");
				continue;
			}
		}
		/******		next		******/
		else if (command == "next" || command == "n") {
			if (gb == NULL) {
				inface->msg("Neprobiha zadna hra, nelze jit kupredu.");
				continue;
			}
			// one step further in game history
			// next method of class state 
		}
		/******		back		******/
		else if (command == "back" || command == "b") {
			if (gb == NULL) {
				inface->msg("Neprobiha zadna hra, nelze se vratit zpet.");
				continue;
			}
			// one step back in game history
			// back method of class state 
		}
		/******		unknown	command		******/
		else {
			cout << "\n\tNeznamy prikaz\n";
		}

		// print when waiting for new command
		cout << "\nZadejte prikaz:  \b";
	}

	// delete objects
	tie(gb, squares) = core->destroy(gb, squares);
	delete core;
	delete inface;
	delete save;
	return 0;

}

/*** End of file cli.cpp ***/
