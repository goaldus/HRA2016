/*************************************************************
* Project name: HRA2016
* File: interface.h
* Last change: 04.05.2016 17:38
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

#pragma once

using namespace std;

class Interface 
{
public:
	Interface();
	void printBoard(GameBoard *, Square **);
	void printHelp();
	void parseCmd(string, string &, string &, string &);
	void msg(string);
};

/*** End of file interface.h ***/