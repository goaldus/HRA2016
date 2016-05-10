/*************************************************************
* Project name: HRA2016
* File: interface.h
* Last change: 09.05.2016 01:13
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file interface.h
*
* @brief Header file for command line interface.
* @author Vilem Jelen, Ondrej Molnar
*/
#ifndef INFACE_H
#define INFACE_H

using namespace std;

//! CLI interface class
/*!
This class is interface for user. Contains behaviour like adding arguments, printing gameboard and setting an environment.
*/
class Interface 
{
public:
	Interface();
	//! Prints gameboard to user in CLI
	/*!
	\param gb pointer on GameBoard class
	*/
	void printBoard(GameBoard *);
	//! Prints help to user in CLI
	void printHelp();
	//! Prints gameboard to user in CLI
	/*!
	\param cmd user command
	\return tuple of strings which are parsed from command for next work
	*/
	tuple<string, string, string> parseCmd(string cmd);
	//! Prints message to user
	/*!
	\param msg string which is printed like information message but formatted
	*/
	void msg(string);
};

#endif // INFACE_H
/*** End of file interface.h ***/