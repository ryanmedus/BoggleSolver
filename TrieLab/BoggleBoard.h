#pragma once
#include <string>
#include <vector>
#include "Trie.h"

using namespace std;

class BoggleBoard
{
public:
    BoggleBoard(const string& pathToDictionary);
    ~BoggleBoard();
    void printBoard();
    void solve();
    void clearWords();
private:
    Trie<string> trie;
    vector<string> words;
    vector<bool> posVisited;
    bool isValidDirection(int currentPos, int newPos);
    void loadBoard();
    void shuffle();
    void solveHelper(int pos, string& wordSoFar);
    string board[25];
    string die[25][6] = { {"N", "S", "C", "T", "E", "C"},
    { "A", "E", "A", "E", "E", "E" },
    { "H", "H", "L", "R", "O", "D" },
    { "O", "R", "W", "V", "G", "R" },
    { "S", "P", "R", "I", "Y", "Y" },
    { "S", "U", "E", "N", "S", "S" },
    { "M", "E", "A", "U", "E", "G" },
    { "S", "E", "P", "T", "I", "C" },
    { "D", "H", "H", "O", "W", "N" },
    { "L", "E", "P", "T", "I", "S" },
    { "S", "T", "L", "I", "E", "I" },
    { "A", "R", "S", "I", "Y", "F" },
    { "T", "E", "T", "I", "I", "I" },
    { "O", "T", "T", "T", "M", "E" },
    { "N", "M", "N", "E", "G", "A" },
    { "N", "N", "E", "N", "A", "D" },
    { "O", "U", "O", "T", "T", "O" },
    { "B", "Z", "J", "B", "X", "K" },
    { "A", "A", "F", "A", "S", "R" },
    { "T", "O", "O", "U", "W", "N" },
    { "O", "T", "H", "D", "D", "N" },
    { "R", "A", "A", "S", "F", "I" },
    { "H", "O", "D", "R", "L", "N" },
    { "E", "E", "E", "E", "A", "M" },
    { "He", "Qu", "Th", "In", "Er", "An" } };
};

