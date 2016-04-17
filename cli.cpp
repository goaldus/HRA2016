#include <iostream>

using namespace std;

class GameBoard
{
public:
    void init(short int val);
    short int gbSize;
    void printSides();

private:
    short int rght;
    short int lft;
    short int rghtop;
    short int lftop;
    short int top;
    short int bot;
    short int lfbot;
    short int rghbot;
    short int mid;
};

//Initialization of gameboard
void GameBoard::init(short int val)
{
    gbSize = val;
    rght = 1;
    lft = -1;
    rghtop = -val+1;
    lftop = -val-1;
    top = -val,
    bot = val;
    lfbot = val-1;
    rghbot = val+1;
    mid = val-1*val/2; // to get position from which I can initialize stones
}
//Only for check directions
void GameBoard::printSides()
{
    cout << "posun vlevo o: " << lft << endl;
    cout << "posun vpravo o: " << rght << endl;
    cout << "posun vlevo nahoru o: " << lftop << endl;
    cout << "posun vpravo nahoru o: " << rghtop << endl;
    cout << "posun dolu o: " << bot << endl;
    cout << "posun nahoru o: " << top << endl;
    cout << "posun vlevo dolu o: " << lfbot << endl;
    cout << "posun vpravo dolu o: " << rghbot << endl;
}

//Properties of squares
class Square
{
public:
    Square()
    {
        owner = 0;
    }

private:
    int owner;
};



int main()
{
    GameBoard gb;
    short int a;
    cout << "Zadejte velikost pole: _\b";
    cin >> a;
    gb.init(a);
    Square squares[gb.gbSize*gb.gbSize];
    cout << "Velikost pole: " << gb.gbSize << endl;
    gb.printSides();

    /*
    @todo Unable to compare variable i to gb.gbSize, dunno why, need to be fixed a little bit
    @brief gameboard print
    */
	cout << "\n     ";
	for (short int i = 0; i < a; ++i)
        cout << i+1 << "   ";

    for (short int j = 0; j < a; ++j)
    {
        cout << "\n   +";
        for (int i = 0; i < a; ++i)
            cout << "---+";

        cout << "\n "<< j+1 << " |";

        for (int j = 0; j < a; ++j) // @todo add character for stone if square[index].owner = 1;
            cout << "   |";

    }
    cout << "\n   +";
    for (int i = 0; i < a; ++i)
		cout << "---+";
    cout << "\n";
    return 0;
}
