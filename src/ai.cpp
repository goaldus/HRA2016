/*************************************************************
* Project name: HRA2016
* File: ai.cpp
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file ai.cpp
*
* @brief Class representing artificial inteligence
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iterator>

#include "gameboard.h"
#include "save.h"
#include "ai.h"


using namespace std;

/*
@brief default constructor
*/
AI::AI() {

}

/*
@brief Runs selected AI
@return chosen index for Disk
*/
short int AI::run(GameBoard * gb, Save * save) {
	short int result = 0;
	// select algorithm
	switch (gb->getAIType()) {
		case 1:
			result = random(gb);
			break;
		case 2:
			result = simpleH(gb, save);
			break;
	}

	return result;
}

/*
@brief Generate random number in selected range
*/
int AI::genRandom(int from, int to) {
	random_device rd;
	// get seed for generator
	mt19937 seed(rd());
	// set range for generator
	uniform_int_distribution<> number(from, to);

	return number(seed);
}

/*
@brief Algorithm for choosing random position
*/
short int AI::random(GameBoard * gb) {
	vector<short int> avail = gb->getVec(AVAIL);
	// select random index from vector
	int index = genRandom(0, avail.size());
	// wait 1.2 sec
	this_thread::sleep_for(chrono::milliseconds(1200));

	return avail[index];
}

/*
@brief Evaluate position on Gameboard
*/
double AI::evalPos(short int index, GameBoard * gb) {
	int x = index / gb->size;
	int y = index % gb->size;
	int max = gb->size - 1;

	if ((x == 0 && (y == 0 || y == max)) || (x == max && (y == 0 || y == max))) {
		return 1.5;
	}
	else if ((x == 0 && (y == 1 || y == max-1)) || (x == 1 && (y == 0 || y == max)) || 
		(x == max && (y == 1 || y == max-1)) || (x == max-1 && (y == 0 || y == max))) {
		return 0.4;
	}
	else if (((x == 0 || x == max) && (y >= 2 && y < max - 1)) || ((y == 0 || y == max) && (x >= 2 && x < max - 1))) {
		return 0.7;
	}
	else
		return 1.0;
}

/*
@brief Algorithm with simple heuristic 
*/
short int AI::simpleH(GameBoard * gb, Save * save) {
	bool loadRes;
	size_t w_count = gb->getVec(WHITE).size();
	double pos_val = 0.0;
	int turn_val = 0;
	vector<short int> avail = gb->getVec(AVAIL);
	// for storing value of available places
	vector<double> value;
	value.reserve(avail.size());

	for (unsigned i = 0; i < avail.size(); ++i) {
		pos_val = evalPos(avail[i], gb);
		gb->placeStone(avail[i]);
		save->addState(gb);
		// number of gained disks
		turn_val = (int)(gb->getVec(WHITE).size() - w_count);
		value.push_back(pos_val * turn_val);
		// return to previous state
		tie(gb, loadRes) = save->loadState(gb, false);
	}

	// max value in vector
	auto max_value = max_element(value.begin(), value.end());
	// index of max_value in vector
	short int best_index = distance(value.begin(), max_value);

	// wait 1.2 sec
	this_thread::sleep_for(chrono::milliseconds(1200));

	return avail[best_index];
}

/*
@brief AI destructor
*/
AI::~AI() {

}

/*** End of file ai.cpp ***/