#include"Grid.h"

Grid::Grid(){
	this->cells = vector<vector<char> >();
}

Grid::Grid(int width, int height){
	this->width = width;
	this->height = height;
	this->cells = vector<vector<char> >(height, vector<char>(width));
	this->moves = { 0, -1, -1, 0, 0, 1, 1, 0, -1, -1, -1, 1, 1, -1, 1, 1 };
}

bool Grid::checkBordersOfGrid(int i, int j){
	return i < this->height && i > -1 && j < this->width && j > -1;
}

void Grid::findWordsFromACell(Dictionary* dictionary, vector<vector<bool> > visited, set<string>& words, int i, int j, string word){
	char letter = this->cells[i][j];
	word += letter;
	visited[i][j] = true;

	if (dictionary->isPrefix(word)){
		for (size_t k = 0; k < this->movesSize; k += 2)
		{
			if (checkBordersOfGrid(i + this->moves[k], j + this->moves[k + 1])){
				if (!visited[i + this->moves[k]][j + this->moves[k + 1]])
					findWordsFromACell(dictionary, visited, words, i + this->moves[k], j + this->moves[k + 1], word);
			}

		}
		words.insert(word);
	}
}

set<string> Grid::filterWords(Dictionary* dictionary, set<string>& words){
	set<string>::iterator it;
	for (it = words.begin(); it != words.end();) {
		if (!dictionary->isWord(*it)){
			words.erase(it++);
		}
		else {
			++it;
		}
	}
	return words;
}

set<string> Grid::findAllWords(Dictionary* dictionary){
	set<string> words;
	vector<vector<bool> > visited(this->height, vector<bool>(this->width));

	for (size_t i = 0; i < this->height; i++)
	{
		for (size_t j = 0; j < this->width; j++)
		{
			findWordsFromACell(dictionary, visited, words, i, j, "");
		}
	}

	words = this->filterWords(dictionary, words);
	return words;
}

