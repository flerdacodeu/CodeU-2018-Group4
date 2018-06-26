#pragma once

#include "Grid.h"
#include "Dictionary.h"
#include <vector>

struct Delta {
	int diff_i;
	int diff_j;
};

// Directions for adjacent cells
vector<Delta> difference = { { -1,-1 },{ -1,0 },{ -1,1 },{ 0,-1 },{ 0,1 },{ 1,-1 },{ 1,0 },{ 1,1 } };

class WordFinder {
private:
	Grid grid;
	Dictionary dictionary;
public:
	WordFinder(Grid& gri, const Dictionary& dic) : grid(gri), dictionary(dic) {}

	bool check(int i, int j) {
		return i >= 0 && i < grid.getHeight() && j >= 0 && j < grid.getWidth() && !grid.isViseted(i, j);
	}

	void findWords(vector<string>& matches, int i, int j, vector<char> generatedWord) {
		bool validWord = true;

		generatedWord.push_back(grid.getLetter(i, j));

		string word(generatedWord.begin(), generatedWord.end());

		if (!dictionary.isPrefix(word)) {
			return;
		}

		if (dictionary.isWord(word)) {
			matches.push_back(word);
		}

		grid.setVisitedValue(i, j, true);

		for (const Delta& delta : difference) {
			bool validToMove = check(i + delta.diff_i, j + delta.diff_j);
			if (validToMove)
				findWords(matches, i + delta.diff_i, j + delta.diff_j, generatedWord);
		}

		grid.setVisitedValue(i, j, false);
	}

	// If word can be formed in the grid, it will be included in resulting vector.
	//
	vector<string> findAllWordsFormDictionaryInTheGrid() {		
		vector<string> matches;			// all the words from the dictionary that can be formed in the grid

		if (dictionary.isEmpty() || grid.isEmpty())
			return matches;

		vector<char> generatedWord;

		for (int i = 0; i < grid.getHeight(); i++) {
			for (int j = 0; j < grid.getWidth(); j++) {
				findWords(matches, i, j, generatedWord);
			}
		}

		return matches;
	}
};

