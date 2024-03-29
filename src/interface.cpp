/*************************************************************
* Project name: HRA2016
* File: inteface.cpp
* Last change: 09.05.2016 01:13
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
#include <tuple>

#include "gameboard.h"
#include "interface.h"

using namespace std;

/*
@brief Function prints gameboard.
*/
void Interface::printBoard(GameBoard * gb) {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	int b_score, w_score;
	int index;

	// get score
	gb->calcScore(b_score, w_score);

	cout << "\n    Turn: " << ((gb->BlackOnTurn) ? "Black" : "White");
	cout << "\t\tScore: " << "Black " << b_score << " | White " << w_score; 
	if (gb->getAIType() == 1)
		cout << "\t\tAI: easy\n";
	else if (gb->getAIType() == 2)
		cout << "\t\tAI: hard\n";
	else 
		cout << endl;

	cout << "\n      ";
	for (int i = 0; i < gb->size; ++i) {
		if (i < 9)
			cout << i + 1 << "   ";
		else
			cout << i + 1 << "  ";
	}

	for (int k = 0; k < gb->size; ++k) {
		cout << "\n    +";
		for (int i = 0; i < gb->size; ++i)
			cout << "---+";

		if (k < 9)
			cout << "\n  " << k + 1 << " |";
		else
			cout << "\n " << k + 1 << " |";


		for (int j = 0; j < gb->size; ++j) {
			index = k*gb->size + j;
			if (gb->grid[index] != NONE)
				if (gb->grid[index] != AVAIL)
					cout << " " << ((gb->grid[index] == WHITE) ? "O" : "X") << " |";
				else
					cout << " " << "_" << " |";    // position is available
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
		<< "\tvolitelne parametry jsou obtiznost AI a velikost herniho pole,\n"
		<< "\tbez parametru je velikost pole 8 a protihracem clovek\n"
		<< "\n  [put|p] x y                 - polozi disk na souradnice x, y"
		<< "\n  open                        - otevre hru v novem okne"
		<< "\n  save [nazev_hry]            - ulozi hru s volitelnym nazvem"
		<< "\n  load nazev_hry              - nacte hru \"nazev_hry\""
		<< "\n  n | next                    - posune se dopredu v historii"
		<< "\n  b | back                    - posune se zpet v historii"
		<< "\n  help                        - zobrazi napovedu"
		<< "\n  exit                        - ukonci program\n\n\n\n\n\n\n\n\n\n";
}

/*
* @brief Parse command with up to 3 parts
*/
tuple<string, string, string> Interface::parseCmd(string cmd) {
	size_t index = 0;
	string s[3];

	for (int i = 0; i < 3; ++i) {
		if ((index = cmd.find(" ")) != string::npos) {
			s[i] = cmd.substr(0, index);
			cmd.erase(0, index + 1);
		}
		else {
			s[i] = cmd;
			break;
		}		
	}

	return make_tuple(s[0], s[1], s[2]);
}

/*
@brief Prints an error to commandline
*/
void Interface::msg(string msg)
{
	cout << "\n\t" << msg << "\n";
	cout << "\nZadejte prikaz:  \b";
}

/*** End of file interface.cpp ***/