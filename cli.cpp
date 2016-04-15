#include <iostream>

using namespace std;

int gbSize; //global variable

enum directions
{
    rght = 1,
    lft = -1,
    rt = -5,
    lt = -7,
    top = -6,
    bot = 6,
    lbt = 5,
    rbt = 7
};

class Square
{
public:

    int owner;

Square()
{
    owner = 0;
}

};


int main()
{
    cin >> gbSize;

    Square squares[gbSize*gbSize];


	cout << "\n     0   1   2   3   4   5   6   7";

	for (int i = 0; i < 8; ++i) {
		cout << "\n   +---+---+---+---+---+---+---+---+\n " << i << " |";
		for (int j = 0; j < 8; ++j) {
					cout << "   |";

		}
	}
	cout << "\n   +---+---+---+---+---+---+---+---+\n";


    return 0;
}
