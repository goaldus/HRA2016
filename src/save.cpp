/*************************************************************
* Project name: HRA2016
* File: save.cpp
* Last change: 09.05.2016 01:13
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file save.cpp
*
* @brief Save class - containing loading, saving, going back and forth (in moves)
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif

#include "gameboard.h"
#include "ai.h"
#include "core.h"
#include "save.h"

using namespace std;

/*
@brief default constructor
*/
Save::Save() {
	step = 0;
	arrsize = 0;
	filename = "saves\\";
	data = NULL;
}

/*
@brief Copy constructor
*/
Save::Save(const Save &obj) {
	step = obj.step;
	arrsize = obj.arrsize;
	filename = obj.filename;
	// copy data
	data = new string[arrsize];
	*data = *obj.data;

	for (int i = 0; i < arrsize; ++i)
		data[i] = obj.data[i];
}

/*
@brief clears save for new use
*/
void Save::clear() {
	// save contains something
	if (data != NULL) {
		step = 0;
		arrsize = 0;
		filename = "saves\\";
		delete[] data;
	}
}

/*
@brief sets up values for save when new game is created
*/
void Save::setupSave(GameBoard * gb) {
	// clear save
	clear();
	// set initial values 
	arrsize = gb->size * gb->size;
	data = new string[arrsize];
	// add size and AItype information
	data[step] = to_string(gb->size) + " " + to_string(gb->getAIType()) + "\n";
	// add first state
	addState(gb);
}

/*
@brief Adds new state of game to save data
*/
void Save::addState(GameBoard * gb) {
	step++;
	int val;

	// if there was some step changing
	for (int i = step; i < arrsize; ++i)
		data[i].clear();

	for (int i = 0; i < arrsize; ++i) {
		val = gb->grid[i];
		if (val == AVAIL) val = NONE;
		if (i != arrsize - 1)
			data[step] += to_string(val) + " ";
		else
			data[step] += to_string(val) + "\n";
	}	
}

/*
@brief loads data into gameboard
*/
GameBoard * Save::loadData(GameBoard * gb) {
	short int val = 0;

	// clear blacks and whites
	gb->clearVectors();
	// set player on turn
	if (step % 2 == 0)
		gb->BlackOnTurn = false;
	else
		gb->BlackOnTurn = true;

	for (int i = 0; i < arrsize; ++i) {
		val = atoi(data[step].substr(i * 2, 1).data());
		// set grid
		gb->grid[i] = val;
		// add to blacks or whites
		if (val == WHITE)
			gb->pushToVector(true, i);
		else if (val == BLACK)
			gb->pushToVector(false, i);
	}

	return gb;
}


/*
@brief Load next or previous state
*/
tuple<GameBoard *, bool> Save::loadState(GameBoard * gb, bool next) {
	
	if (next) {
		step++;
		if (data[step].empty()) {
			step--;
			return make_tuple(gb, false);
		}
	}
	else { // load previous state
		step--;
		if (step < 1) {
			step++;
			return make_tuple(gb, false);
		}
	}
	
	gb = loadData(gb);

	return make_tuple(gb, true);
}

/*
@brief Checks if the name for save is not available.
*/
inline bool Save::notAvail(string name) {
	ifstream f(name.data());
	return f.good();
}

/*
@brief Save game to file.
*/
bool Save::toFile(string name) {
	filename = "saves\\";
	// use standard name
	if (name.empty()) {
		int num_name = 1;
		while (notAvail(filename + to_string(num_name))) {
			num_name++;
		}
		filename += to_string(num_name);
	}
	// use custom name
	else {
		if (notAvail(filename + name))
			return false;	
		else
			filename += name;
	}
	// create save dir
#ifdef _WIN32
	_mkdir("saves");
#else 
	mkdir("saves", 0777); 
#endif
	// write to file
	ofstream f(filename.data());
	if (f.is_open())
		for (int i = 0; i <= step; ++i) {
			f << data[i];
		}
	else
		return false;

	return true;
}

/*
@brief Load game from file
*/
tuple<GameBoard *, AI *, bool> Save::fromFile(Core * core, GameBoard * gb, AI * ai, string name) {
	filename = "saves\\" + name;

	ifstream f(filename.data());
	if (f.is_open()) {
		// clear save
		clear();
		// delete actual game if it exists
		tie(gb, ai) = core->destroy(gb, ai);

		string line = "";
		getline(f, line);
		int size = atoi(line.substr(0, 2).data());
		// set arrsize and new data
		arrsize = size * size;
		data = new string[arrsize];
		// save first line of file
		data[step] = line;
		// get AItype
		int val = atoi(line.substr(2).data());

		// alloc new game
		tie(gb, ai) = core->alloc(gb, ai, size, val);

		// load rest of file into data
		while (getline(f, line)) {
			data[++step] = line;
		}

		gb = loadData(gb);

		return make_tuple(gb, ai, true);
	}
	else 
		return make_tuple(gb, ai, false);
}


/*
@brief Destructor
*/
Save::~Save() {
	delete[] data;
}


/*** End of file save.cpp ***/