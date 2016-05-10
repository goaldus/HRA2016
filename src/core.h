/*************************************************************
* Project name: HRA2016
* File: core.h
* Last change: 09.05.2016 01:13
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file core.h
*
* @brief Header file for core class.
* @author Vilem Jelen, Ondrej Molnar
*/
#ifndef CORE_H
#define CORE_H


using namespace std;

//! A Core class 
/*!
This class is used for safely creating Gameboard and AI objects and
deleting them when needed. For example with creation of a new game.
*/
class Core {

public:
	//! Takes GameBoard class, AI class and allocates memory for them.
	/*!
	\param pointer on GameBoard class
	\param pointer on AI class
	\return tuple of pointers to GameBoard and AI
	*/
	tuple<GameBoard *, AI *> alloc(GameBoard *, AI *, int, int);
	//! Takes GameBoard class, AI class and deletes them.
	/*!
	\param pointer on GameBoard class.
	\param pointer on AI class.
	\return pointer to GameBoard and pointer to AI
	*/
	tuple<GameBoard *, AI *> destroy(GameBoard *, AI *);
};

#endif // CORE_H
/*** End of file core.h ***/