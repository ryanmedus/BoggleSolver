#include "BoggleBoard.h"

BoggleBoard::BoggleBoard(const string& pathToDictionary) :
	trie(pathToDictionary)
{
	cout << "Boggle Solver" << endl;
	loadBoard();
	posVisited.resize(25, false);
	words.resize(1);
}

void BoggleBoard::loadBoard()
{
	int count = 0;
	for (int i = 0; i < 25; i++)
	{
		board[i] = die[count][rand() % 6];
		count++;
	}
}

BoggleBoard::~BoggleBoard()
{
	
}

void BoggleBoard::printBoard()
{
	loadBoard();
	shuffle();
	for (int i = 0; i < 25; i++)
	{
		if (i % 5 == 0 && i > 0)
			cout << endl;
		cout << board[i] << " ";
	}
	cout << endl;
}

void BoggleBoard::shuffle()
{
	for (int i = 0; i < 25; i++)
	{
		int randomIndex = rand() % 25;
		string temp = "";
		temp = board[randomIndex];
		board[randomIndex] = board[i];
		board[i] = temp;
	}
}

void BoggleBoard::solve()
{
	for (int i = 0; i < 25; i++)
	{
		string letter = board[i];
		solveHelper(i, letter);
	}

	cout << "All possible values from longest to shortest:" << endl;
	
	int maxLength = 0;
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i].length() > maxLength)
			maxLength = words[i].length();
	}
	vector<vector<string>> wordsSorted(maxLength + 1);
	for (int i = 0; i < words.size(); i++)
	{
		wordsSorted[words[i].length()].push_back(words[i]);
	}

	for (int i = wordsSorted.size() - 1; i > 0; i--)
	{
		if (!wordsSorted[i].empty())
		{
			cout << "Length: " << i << " words" << endl;
			for (int j = 0; j < wordsSorted[i].size(); j++)
			{
				cout << wordsSorted[i][j] << " ";
			}
			cout << endl;
		}
	}
}

void BoggleBoard::solveHelper(int pos, string& wordSoFar)
{
	string wordFound = trie.search(wordSoFar);
	const int directionOffsets[] = {-6, -5, -4, -1, 1, 4, 5, 6};

	if (posVisited[pos] == true)
		return;

	posVisited[pos] = true;

	if (wordFound == "NOT FOUND")
	{
		posVisited[pos] = false;
		return;
	}
	if (wordFound == "FOUND" && wordSoFar.length() >= 4)
	{
		bool isNew = true;
		for (int i = 0; i < words.size(); i++)
		{
			if (words[i] == wordSoFar)
			{
				isNew = false;
				break;
			}
		}
		if (isNew)
			words.push_back(wordSoFar);
	}

	for (int i = 0; i < 8; i++)
	{
		int newPos = pos + directionOffsets[i];
		if (isValidDirection(pos, newPos))
		{
			wordSoFar += board[newPos];
			solveHelper(newPos, wordSoFar);
			if (board[newPos].length() != 1)
				wordSoFar.pop_back();
			wordSoFar.pop_back();
		}
	}
	posVisited[pos] = false;
}

bool BoggleBoard::isValidDirection(int currentPos, int newPos)
{
	if (newPos < 0 || newPos >= 25)
		return false;
	if (currentPos % 5 == 0 && newPos % 5 == 4)
		return false;
	if (currentPos % 5 == 4 && newPos % 5 == 0)
		return false;
	return !posVisited[newPos];
}

void BoggleBoard::clearWords()
{
	words.clear();
}