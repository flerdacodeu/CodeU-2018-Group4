#include "iostream"
#include "set"
#include "vector"
#include <algorithm>
#include <string>
#include "test_libraryr.h"

using namespace std;



set<string> dictionary = { "apple", "spring", "sun", "sea", "dancer" };

typedef struct gridCell {
	char letter;
	bool visited;
} GridCell;

typedef struct delta {
	int dx;
	int dy;
} Delta;

GridCell grid[][3] = {
						{ {'s', false}, {'p', false}, {'g', false} },
						{ {'t', false}, {'r', false}, {'n', false} },
						{ {'s', false}, {'u', false}, {'i', false} }
					};

// Directions for adjacent cells
Delta difference[8] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

// Discard words that have letters which are not in the grid.
//
set<string> reduceDictionary(set<string> dictionary, set<char> gridLetters) {
	set<string> result;

	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
		int cnt = 0;
		string word = *it;
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		for (int i = 0; i < word.length(); i++) {
			if (gridLetters.find(word[i]) == gridLetters.end())
				break;
			cnt++;
		}

		if (word.length() == cnt)
			result.insert(word);
	}

	return result;
}

// This allows the search function to abort search paths which can never result in words.
//
set<string> generateWordsPrefixes(set<string> dictionary) {
	set<string> result;

	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
		string word = *it;
		for (int i = 0; i <= word.length(); i++) {
			result.insert(word.substr(0, i));
		}
	}

	return result;
}

set<char> makeGridSet(GridCell grid[][3]) {
	set<char> result;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			result.insert(grid[i][j].letter);
		}
	return result;
}

bool isPrefix(set<string> prefixes, string word) {
	return prefixes.find(word) != prefixes.end();
}

bool isWord(set<string> dictionary, string word) {
	return dictionary.find(word) != dictionary.end();
}

bool check(int i, int j) {
	return i >= 0 && i < 3 && j >= 0 && j < 3 && !grid[i][j].visited;
}

void findWords(set<string> dictionary, set<string> prefixes, vector<string>& matches, int i, int j, vector<char> generatedWord) {
	bool validWord = true;

	generatedWord.push_back(grid[i][j].letter);
	
	string word(generatedWord.begin(), generatedWord.end());

	if (!isPrefix(prefixes, word)) {
		return;
	}

	if (isWord(dictionary, word)) {
		matches.push_back(word);
	}

	grid[i][j].visited = true;
	vector<char> newWord(generatedWord);

	for (int k = 0; k < 8; k++) {
		bool validToMove = check(i + difference[k].dx, j + difference[k].dy);
		if(validToMove)
			findWords(dictionary, prefixes, matches, i + difference[k].dx, j + difference[k].dy, newWord);
	}

	grid[i][j].visited = false;
	generatedWord.pop_back();
}

// If word can be formed in the grid, it will be included in resulting vector.
//
vector<string> findAllWordsFormDictionaryInTheGrid(set<string> dictionary, GridCell grid[][3]) {
	set<char> gridLetters = makeGridSet(grid);
	set<string> reducedDictionary = reduceDictionary(dictionary, gridLetters);
	set<string> prefixes = generateWordsPrefixes(reducedDictionary);

	vector<string> matches;			// all the words from the dictionary that can be formed in the grid

	vector<char> generatedWord;	

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			findWords(reducedDictionary, prefixes, matches, i, j, generatedWord);
		}
	}

	return matches;
}


int main() {
	vector<string> result = findAllWordsFormDictionaryInTheGrid(dictionary, grid);
	set<string> emptyDictionary = {};

	vector<string> correctAnswers = { "spring", "sun" };
	vector<string> wrondAnswers = { "spring", "sea" };
	vector<string> empty;

	for (int i = 0; i < result.size(); i++)
		cout << result[i] << endl;

	EXPECT_EQ(findAllWordsFormDictionaryInTheGrid(dictionary, grid), correctAnswers);

	EXPECT_EQ(findAllWordsFormDictionaryInTheGrid(emptyDictionary, grid), empty);

	EXPECT_EQ(findAllWordsFormDictionaryInTheGrid(dictionary, new GridCell[3][3]), empty);

	system("PAUSE");
	return 0;
}
