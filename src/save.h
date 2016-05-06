/*************************************************************
* Project name: HRA2016
* File: save.h
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file save.h
*
* @brief Header file for save class.
* @author Vilem Jelen, Ondrej Molnar
*/

#pragma once

using namespace std;


class Save {
	string filename;
	string * data;
	int step;  // index of state in data (0 is for size and ai info)

public:
	Save();
	void clear();
	void setupSave(GameBoard *);
	bool toFile(string);
	inline bool notAvail(string);
	
};

/*** End of file save.h ***/