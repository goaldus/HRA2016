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

//! A Save class 
/*!
This class is used for storing information about game history and
executing all operations done with it. For example saving or loading game.
The data in Save class contain information about every step through game.
(Exluding AI turns)
*/
class Save {
	string filename;
	string * data;
	int step;  // index of state in data (0 is for size and ai info)
	int arrsize; // gb->size * gb->size
	void clear();

public:
	//! A constructor.
	/*!
	Initializes values for Save class.
	*/
	Save();
	//! A copy constructor.
	/*!
	Used in AI class for cloning game history into a new object.
	*/
	Save(const Save &obj); 
	//! Prepares Save after creation of new game.
	/*!
	\param gb pointer on GameBoard class.
	*/
	void setupSave(GameBoard *);
	//! Adds information about new state of the game into Save data.
	/*!
	\param gb pointer on GameBoard class.
	*/
	void addState(GameBoard *);
	//! Loads chosen state of the game into GameBoard instance.
	/*!
	\param gb pointer on GameBoard class.
	\param next bool used for choosing direction of load
	\return pointer to GameBoard and bool based on success
	*/
	tuple<GameBoard *, bool> loadState(GameBoard *, bool);
	//! Save game into file.
	/*!
	\param name string Name of new save file.
	\return bool based on success of saving
	*/
	bool toFile(string);
	//! Load saved game from file.
	/*!
	Takes Core for creating and deleting objects,
	Gameboard for loading new state into it 
	AI for setting it for new game and name of chosen game for loading.
	\param core pointer on Core class.
	\param gb pointer on GameBoard class.
	\param ai pointer on AI class.
	\param name string with name of saved game.
	\return pointer to GameBoard and pointer to AI and bool indicating success
	*/
	tuple<GameBoard *, AI *, bool> fromFile(Core *, GameBoard *, AI *, string);
	//! Checks if the name for save is available.
	/*!
	\param name string of tested file.
	\return bool indicating availibility
	*/
	inline bool notAvail(string);
	//! Loads data from Save into GameBoard instance.
	/*!
	\param gb pointer on GameBoard
	\return pointer on GameBoard with new data
	*/
	GameBoard * loadData(GameBoard *);
	//! A destructor
	/*!
	Deletes Save data. 
	*/
	~Save();
};

#endif // SAVE_H
/*** End of file save.h ***/
