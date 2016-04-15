#include<iostream>

using namespace std;

auto map = new int[8][8]();
int na_tahu;

enum smery{
	vpravo = +1,
	vlevo = -1,
	nula = +0,
};

void score(int &w_score, int &b_score) {
	int white = 0;
	int black = 0;

	// spocitani kamenu 
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (map[i][j] == 1)
				white++;
			else if (map[i][j] == 2)
				black++;
		}
	}

	// "osetreni" deleni nulou  
	if (white == 0) white = 1;
	if (black == 0) black = 1;

	/* 
	*  vypocet skore 
	*/
	b_score = black * 100 / white;
	w_score = white * 100 / black;


	return;
}

// vytiskne aktualni stav herni plochy
void print_map() {
	// vypocet skore
	int w_score, b_score;
	score(w_score, b_score);
	// tisk score
	cout << "\n   Score: " << "Black " << b_score << " | White " << w_score << endl;

	// tisk herni plochy
	cout << "\n     0   1   2   3   4   5   6   7";

	for (int i = 0; i < 8; ++i) {
		cout << "\n   +---+---+---+---+---+---+---+---+\n " << i << " |";
		for (int j = 0; j < 8; ++j) {
			if (map[i][j] != 0)
				if (map[i][j] != 3)
					cout << " " << ((map[i][j] == 1) ? "O" : "X") << " |";
				else
					cout << " " << "!" << " |";
			else
				cout << "   |";
		}
	}
	cout << "\n   +---+---+---+---+---+---+---+---+\n";
}


// nefunguje !!!
// oznaci policka dostupna pro polozeni kamene
void mark_placeable() {
	int akt = 0;

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (map[i][j] == 1) {
				while (map[i + ++akt][j] == 2);
				if (map[i + ++akt][j] == 0) map[i + akt][j] = 3;
			}
		}
	}
}




int main() {
	// nastaveni stavu hry
	// 0 = prazdne pole
	// 1 = bily kamen
	// 2 = cerny kamen
	// 3 = lze sem polozit pro akt. hrace
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			map[i][j] = 0;
		}
	}

	map[2][3] = 1;
	map[2][4] = 2;
	map[3][2] = 2;
	map[3][3] = 2;
	map[3][4] = 2;
	map[4][2] = 2;
	map[4][3] = 2;
	map[4][4] = 1;
	map[4][5] = 2;
	map[5][3] = 1;
	map[5][5] = 1;

	// na tahu bily
	na_tahu = 1;

	//mark_placeable();

	print_map();


	return 0;
}
