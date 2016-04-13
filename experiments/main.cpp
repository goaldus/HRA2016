#include<iostream>

using namespace std;

auto map = new int[8][8]();
int na_tahu;

// vytiskne aktualni stav herni plochy
void print_map() {
	cout << "\n     0   1   2   3   4   5   6   7";

	for (int i = 0; i < 8; ++i) {
		cout << "\n   +---+---+---+---+---+---+---+---+\n " << i << " |";
		for (int j = 0; j < 8; ++j) {
			if (map[i][j] != 0)
				if (map[i][j] != 3)
					cout << " " << ((map[i][j] == 1) ? "O" : "X") << " |";
				else
					cout << " " << "P" << " |";
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
