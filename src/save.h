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

//! Class takes care of everything concerning saving/loading
/*!
Function like saving, loading and going back and forth by steps in game is handled by this class.
*/
class Save {
	string filename;
	string * data;
	int step;  // index of state in data (0 is for size and ai info)
	int arrsize; // gb->size * gb->size

public:
	Save();
	//! Copy constructor
	Save(const Save &obj);
	//! Function clears inner variables so it can be used again with empty variables.
	void clear();
	//! Sets up values for save when new game is created
	/*!
	\param gb pointer on GameBoard class
	*/
	void setupSave(GameBoard *);
	//! Adds new state of game to save data
	/*!
	\param gb pointer on GameBoard class
	*/
	void addState(GameBoard *);
	//! Load next or previous state
	/*!
	\param gb pointer on GameBoard class
	\param next signalizes if state is next
	\return 2 variables - tuple of pointers (to GameBoard) and bool signalizing if method was correctly triggered
	*/
	tuple<GameBoard *, bool> loadState(GameBoard *, bool);
	//! Saves game to file.
	/*!
	\param name File name
	\return true if file was correctly saved
	*/
	bool toFile(string);
	//! Loads game from file
	/*!
	\param core File name
	\param gb pointer to GameBoard
	\param ai pointer to ai
	\param name file name
	\return 3 variables - pointer to gameboard, ai and bool signalizing success (true for success).
	*/
	tuple<GameBoard *, AI *, bool> fromFile(Core *, GameBoard *, AI *, string);
	//! Checks if the name for save is not available.
	/*!
	\param name File name
	\return bool signalizing if file name already exists or not
	*/
	inline bool notAvail(string);
	//! Loads data into GameBoard
	/*!
	\param gb pointer to gameboard
	\return pointer to gameboard
	*/
	GameBoard * loadData(GameBoard *);
	~Save();
};

#endif // SAVE_H
/*** End of file save.h ***/