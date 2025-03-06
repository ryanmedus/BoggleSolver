#include <iostream>
#include "BoggleBoard.h"

using namespace std;

int main()
{
    srand(time(0));

    int replay = 1;
    char ch;

    BoggleBoard bb("bigDictionary.txt");

    while (replay == 1)
    {
        bb.printBoard();
        bb.solve();
        cout << "\nPress ENTER to play again...";
        cin.get();
        cout << endl;
        bb.clearWords();
    }

    return 0;
}