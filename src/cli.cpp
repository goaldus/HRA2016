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

#include "gameboard.h"
#include "save.h"
#include "interface.h"
#include "ai.h"
#include "core.h"



using namespace std;


#ifdef _WIN32
#include <Windows.h>
/*
@brief Function is called only in windows and sets command line resolution
*/
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

/*
@brief Checks if string is a number
@return true or false
*/
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
	Core *core = new Core();
	Interface *inface = new Interface();
	Save * save = new Save();
	AI * ai = NULL;
	bool loadResult;

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
			int AItype = 0;
			int size = 8;
			// delete game in progress before creating new
			tie(gb, ai) = core->destroy(gb, ai);
			// command is alone, using default new game settings
			if (arg1.empty()) {
				tie(gb, ai) = core->alloc(gb, ai, size, AItype);
			}
			else if (is_digits(arg1) || is_digits(arg2) || !arg1.empty()) {
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
				size = stoi(arg2);
				// allow only these sizes
				if (size != 6 && size != 8 && size != 10 && size != 12) {
					inface->msg("Nepovolena velikost herniho pole. Povolene jsou: 6, 8, 10, 12.");
					continue;
				}
				tie(gb, ai) = core->alloc(gb, ai, size, AItype);
			}
			// init save data
			save->setupSave(gb);
			// set available places
			gb->setAvailables();
			// print current state of the game
			inface->printBoard(gb);
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
			//Index of single square
			int index = coord1 * gb->size + coord2;
			// empty square, puts stone and changes turn
			if (gb->grid[index] == AVAIL) {
				gb->placeStone(index);
				save->addState(gb);
				gb->setAvailables();
				inface->printBoard(gb);
				if (gb->checkEnd())
					cout << "\n\tKONEC HRY!\n" << "\tOvsem muzete zacit novou a nebo si nahrat ulozenou pozici." << endl;
				if (gb->noTurn())
					continue;
				// AI code here
				if(gb->enemyAI) {
					gb->placeStone(ai->run(gb, save));
					gb->setAvailables();
					inface->printBoard(gb);
				}
				if (gb->checkEnd())
					cout << "\n\tKONEC HRY!\n" << "\tOvsem muzete zacit novou a nebo si nahrat ulozenou pozici." << endl;
			}
			else {
				inface->msg("Na tuto pozici nelze polozit disk.");
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
			// save to file with standard or custom name
			if (!save->toFile(arg1)) {
				inface->msg("Ulozena hra s timto nazvem uz existuje.");
				continue;
			}
			else {
				inface->msg("Hra byla uspesne ulozena.");
				continue;
			}

		}
		/******		load		******/
		else if (command == "load" || command == "l") {
			if (!arg1.empty()) {
				// delete actual game if it exists
				tie(gb, ai) = core->destroy(gb, ai);
				// create new game and load data from file=arg1
				tie(gb, loadResult) = save->fromFile(gb, arg1);
				// create new ai
				if (gb->enemyAI)
					ai = new AI();

				if (!loadResult) {
					inface->msg("Nepodarilo se nacist hru.");
					continue;
				}
				else {
					gb->setAvailables();
					if (gb->noTurn())
					{
						gb->nextTurn();
						gb->setAvailables();
						if (gb->noTurn())
							continue;
					}
					inface->printBoard(gb);


				}
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
			tie(gb, loadResult) = save->loadState(gb, true);
			if (!loadResult) {
				inface->msg("Nelze jit o tah dopredu.");
				continue;
			}
			gb->setAvailables();
			inface->printBoard(gb);
		}
		/******		back		******/
		else if (command == "back" || command == "b") {
			if (gb == NULL) {
				inface->msg("Neprobiha zadna hra, nelze se vratit zpet.");
				continue;
			}
			// one step back in game history
			tie(gb, loadResult) = save->loadState(gb, false);
			if (!loadResult) {
				inface->msg("Nelze jit o tah zpet.");
				continue;
			}
			gb->setAvailables();
			inface->printBoard(gb);
		}
		/******		unknown	command		******/
		else {
			cout << "\n\tNeznamy prikaz\n";
		}

		// print when waiting for new command
		cout << "\nZadejte prikaz:  \b";
	}

	// delete objects
	tie(gb, ai) = core->destroy(gb, ai);
	delete core;
	delete inface;
	delete save;
	return 0;

}

/*** End of file cli.cpp ***/
