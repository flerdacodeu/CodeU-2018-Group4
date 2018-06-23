#include "iostream"
#include "Grid.h"
#include "Dictionary.h"
#include "WordFinder.h"
#include <string>
#include "test_library.h"

using namespace std;

int main() {
	int i = 3;
	int j = 3;
	char letters[] = { 's', 'p', 'g', 't', 'r', 'n', 's', 'u', 'i' };
	Grid* grid = new Grid(i, j, letters);

	set<string> words = { "apple", "spring", "sun", "sea", "dancer" };
	Dictionary* dictionary = new Dictionary(words);

	WordFinder* wordFinder = new WordFinder(*grid, *dictionary);

	vector<string> result = wordFinder->findAllWordsFormDictionaryInTheGrid();

	vector<string> correctAnswers = { "spring", "sun" };
	vector<string> wrondAnswers = { "spring", "sea" };
	
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << endl;

	EXPECT_EQ(wordFinder->findAllWordsFormDictionaryInTheGrid(), correctAnswers);

	Grid* emptyGrid = new Grid(0, 0, {});
	WordFinder* wordFinderWithEmptyGrid = new WordFinder(*emptyGrid, *dictionary);
	vector<string> empty;

	EXPECT_EQ(wordFinderWithEmptyGrid->findAllWordsFormDictionaryInTheGrid(), empty);

	delete grid;
	delete dictionary;
	delete emptyGrid;

	system("PAUSE");
	return 0;
}
