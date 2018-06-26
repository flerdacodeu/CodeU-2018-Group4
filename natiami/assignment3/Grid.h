#include<string>
#include<vector>
#include<set>
#include"Dictionary.h"

class Grid{
public:
	vector<vector<char> > cells;
	int width;
	int height;
	vector<pair<int, int>> moves;
	const int movesSize = 16;

	Grid();
	Grid(int width, int height);
	bool checkBordersOfGrid(int i, int j);
	void findWordsFromACell(Dictionary* dictionary, vector<vector<bool> > visited, set<string>& words, int i, int j, string word);
	set<string> filterWords(Dictionary* dictionary, set<string>& words);
	set<string> findAllWords(Dictionary* dictionary);
};
