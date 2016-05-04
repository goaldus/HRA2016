/*************************************************************
* Project name: HRA2016
* File: inteface.cpp
* Last change: 04.05.2016 17:38
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file interface.cpp
*
* @brief Command line interface which supports both Linux and Windows.
* @author Vilem Jelen, Ondrej Molnar
*/

#include <iostream>
#include <string>

#include "square.h"
#include "gameboard.h"
#include "interface.h"

using namespace std;

/*
@brief Function prints gameboard.
*/
void Interface::printBoard(GameBoard * gb, Square ** sq) {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	int white = 0, black = 0, b_score, w_score;

	// "osetreni" deleni nulou  
	if (white == 0) white = 1;
	if (black == 0) black = 1;

	/*
	*  vypocet skore // @todo add score calculation to the core - any class
	*/
	b_score = black * 100 / white;
	w_score = white * 100 / black;

	cout << "\n    Turn: " << ((gb->BlackOnTurn) ? "Black" : "White");
	cout << "\t\tScore: " << "Black " << 127 << " | White " << 57; //@todo replace PH values for score
	if (gb->getAIType() == 1)
		cout << "\t\tAI: easy\n";
	else if (gb->getAIType() == 2)
		cout << "\t\tAI: hard\n";
	else 
		cout << endl;

	cout << "\n      ";
	for (short int i = 0; i < gb->size; ++i) {
		if (i < 9)
			cout << i + 1 << "   ";
		else
			cout << i + 1 << "  ";
	}

	for (short int k = 0; k < gb->size; ++k) {
		cout << "\n    +";
		for (int i = 0; i < gb->size; ++i)
			cout << "---+";

		if (k < 9)
			cout << "\n  " << k + 1 << " |";
		else
			cout << "\n " << k + 1 << " |";


		for (int j = 0; j < gb->size; ++j) {
			if (sq[k*gb->size + j]->owner != 0)
				if (sq[k*gb->size + j]->owner != 3)
					cout << " " << ((sq[k*gb->size + j]->owner == 1) ? "O" : "X") << " |";
				else
					cout << " " << "!" << " |";    // owner = 3 is placeable position
			else
				cout << "   |";
		}

	}
	cout << "\n    +";
	for (int i = 0; i < gb->size; ++i)
		cout << "---+";
	cout << "\n";
}

/*
@brief Prints welcome message.
*/
Interface::Interface()
{
	cout << "\nVita vas hra Reversi.\nPro ukonceni zadejte prikaz \"exit\", pro napovedu \"help\".\n";
	cout << "\nZadejte prikaz:  \b";
}

/*
@brief Prints help.
*/
void Interface::printHelp()
{
	cout << "\n  new [easy|hard] [6|8|10|12] - vytvori novou hru\n"
		<< "\tvolitelne parametry jsou obtiznost AI a velikost herniho pole\n"
		<< "\tbez parametru je velikost pole 8 a protihracem clovek\n"
		<< "\n  [put|p] x y                 - polozi disk na souradnice x, y\n"
		<< "\n  open                        - otevre hru v novem okne\n"
		<< "\n  save [nazev_hry]            - ulozi hru s volitelnym nazvem\n"
		<< "\n  load [nazev_hry]            - nacte hru \"nazev_hry\"\n"
		<< "\tbez parametru vypise seznam ulozenych her\n"
		<< "\n  n | next                    - posune se dopredu v historii\n"
		<< "\n  b | back                    - posune se zpet v historii\n"
		<< "\n  help                        - zobrazi napovedu\n"
		<< "\n  exit                        - ukonci program\n\n\n\n\n\n\n\n\n";
}

/*
* @brief Parse command with up to 3 parts
*/
void Interface::parseCmd(string cmd, string &first, string &second, string &third) {
	size_t index = 0;

	if ((index = cmd.find(" ")) != string::npos) {
		first = cmd.substr(0, index);
		cmd.erase(0, index + strlen(" "));
		if ((index = cmd.find(" ")) != string::npos) {
			second = cmd.substr(0, index);
			cmd.erase(0, index + strlen(" "));
			if ((index = cmd.find(" ")) != string::npos) {
				third = cmd.substr(0, index);
				cmd.erase(0, index + strlen(" "));
			}
			else
				third = cmd;
		}
		else
			second = cmd;
	}
	else
		first = cmd;
}

/*
@brief Prints an error to commandline
*/
void Interface::error(string msg)
{
	cout << "\n\t" << msg << "\n";
	cout << "\nZadejte prikaz:  \b";
}

/*** End of file interface.cpp ***/