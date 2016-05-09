/*************************************************************
* Project name: HRA2016
* File: save.h
* Last change: 09.05.2016 01:13
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
#ifndef SAVE_H
#define SAVE_H

using namespace std;

// forward declarations
class Core;
class AI;

class Save {
	string filename;
	string * data;
	int step;  // index of state in data (0 is for size and ai info)
	int arrsize; // gb->size * gb->size

public:
	Save();
	Save(const Save &obj); // copy constructor
	void clear();
	void setupSave(GameBoard *);
	void addState(GameBoard *);
	tuple<GameBoard *, bool> loadState(GameBoard *, bool);
	bool toFile(string);
	tuple<GameBoard *, AI *, bool> fromFile(Core *, GameBoard *, AI *, string);
	inline bool notAvail(string);
	GameBoard * loadData(GameBoard *);
	~Save();
};

#endif // SAVE_H
/*** End of file save.h ***/