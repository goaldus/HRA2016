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

#include "gameboard.h"
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
short int AI::run(GameBoard * gb) {
	short int result = 0;
	// select algorithm
	switch (gb->getAIType()) {
		case 1:
			result = random(gb);
			break;
		case 2:
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
	// wait 1.3 sec
	this_thread::sleep_for(chrono::milliseconds(1300));

	return avail[index];

}


/*** End of file ai.cpp ***/