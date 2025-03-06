#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Trie
{
public:
	Trie(const string& filepath);
	~Trie();
	string search(const string& word);
	void printAllWords();
private:
	struct Node
	{
		bool isFullWord;
		bool isPartialWord;
		Node** letters;
	};
	Node* p_head;
	void insert(string word);
	Node* newNode();
	void deconHelper(Node* node);
	void printAllWordsHelper(Node* node, string word);
};

template <class T>
Trie<T>::Trie(const string& filepath)
{
	Node* node = newNode();
	p_head = node;
	string word = " ";
	ifstream file;

	file.open(filepath);

	if (file.good())
	{
		while (file.good())
		{
			getline(file, word);
			insert(word);
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file";
	}
}

template <class T>
typename Trie<T>::Node* Trie<T>::newNode()
{
	Node* n = new Node;
	n->isFullWord = false;
	n->isPartialWord = false;
	n->letters = new Node * [26];
	for (int i = 0; i < 26; i++)
	{
		n->letters[i] = NULL;
	}
	return n;
}

template <class T>
Trie<T>::~Trie()
{
	deconHelper(p_head);
}

template <class T>
void Trie<T>::deconHelper(Node* n)
{
	Node* current = n;
	for (int i = 0; i < 26; i++)
	{
		if (current->letters[i] != NULL)
		{
			deconHelper(current->letters[i]);
		}
	}
	delete[] current->letters;
	delete current;
}

template <class T>
void Trie<T>::insert(string word)
{
	Node* currentNode = p_head;
	for (int i = 0; i < word.length(); i++)
	{
		int currentLetter = word[i];
		currentLetter = tolower(currentLetter) - 97;
		if (i != 0 && currentNode->letters[currentLetter] != NULL)
		{
			currentNode = currentNode->letters[currentLetter];
		}
		else if (currentNode->letters[currentLetter] == NULL)
		{
			currentNode->letters[currentLetter] = newNode();
			currentNode = currentNode->letters[currentLetter];
			currentNode->isPartialWord = true;
		}
		else
		{
			currentNode = currentNode->letters[currentLetter];
		}
		if (i == word.length() - 1)
		{
			currentNode->isFullWord = true;
		}
		
	}
	
}

template <class T>
void Trie<T>::printAllWords()
{
	string word = "";
	printAllWordsHelper(p_head, word);
}

template <class T>
void Trie<T>::printAllWordsHelper(Node* node, string word)
{
	if (node->isFullWord)
	{
		cout << word << " ";
	}
	for (int i = 0; i < 26; i++)
	{
		if (node->letters[i] != NULL)
		{
			char nextChar = 97 + i;
			printAllWordsHelper(node->letters[i], word + nextChar);
		}
	}/*
	if (node == NULL)
		return;*/
}

template <class T>
string Trie<T>::search(const string& word)
{
	Node* currentNode = p_head;
	string retVal = "NOT FOUND";
	if (currentNode == NULL)
	{
		cout << "EMPTY TRIE";
		return "";
	}
	for (int i = 0; i < word.length(); i++)
	{
		currentNode = currentNode->letters[tolower(word[i]) - 97];
		if (currentNode == NULL)
		{
			return "NOT FOUND";
		}
		if (currentNode->isFullWord)
		{
			retVal = "FOUND";
		}
		else if (currentNode->isPartialWord)
		{
			retVal = "PARTIAL";
		}
		else
		{
			retVal = "NOT FOUND";
		}
	}
	return retVal;
}