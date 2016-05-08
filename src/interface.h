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

class Interface 
{
public:
	Interface();
	void printBoard(GameBoard *);
	void printHelp();
	tuple<string, string, string> parseCmd(string cmd);
	void msg(string);
};

#endif // INFACE_H
/*** End of file interface.h ***/