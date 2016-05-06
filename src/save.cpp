/*************************************************************
* Project name: HRA2016
* File: save.cpp
* Last change: 04.05.2016 17:38
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
* @brief Save class
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
#include "save.h"

using namespace std;

/*
@brief default constructor
*/
Save::Save() {
	step = 0;
	filename = "saves\\";
	data = NULL;
}

/*
@breif clears save for new use
*/
void Save::clear() {
	// save contains something
	if (data != NULL) {
		step = 0;
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
	int arrsize = gb->size * gb->size;
	data = new string[arrsize];

	data[step] = to_string(gb->size) + " " + to_string(gb->getAIType()) + "\n";
	step++; // shift to next line

	for (int i = 0; i < arrsize; ++i) {
		if (i != arrsize - 1)
			data[step] += to_string(gb->grid[i]) + " ";
		else
			data[step] += to_string(gb->grid[i]) + "\n";
	}
	step++;
}

/*
@brief Adds new state of game to save data
*/
void Save::addState() {

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
	mkdir("saves", 0777); // notice that 777 is different than 0777
#endif
	// write to file
	ofstream f(filename.data());
	if (f.is_open())
		for (int i = 0; i < step; ++i) {
			f << data[i];
		}
	else
		return false;

	return true;
}


/*** End of file save.cpp ***/