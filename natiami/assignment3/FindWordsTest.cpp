#include "FindWordsTest.h"

void FindWordsTest::test(){
	test_findAllWords();
	test_EmptyGrid();
	test_EmptyDictionary();
}

Grid* FindWordsTest::initGrid(){
	string gridRow1 = "AAR";
	string gridRow2 = "TCD";
	Grid* grid = new Grid(3, 2);
	for (size_t j = 0; j < grid->width; j++)
	{
		grid->cells[0][j] = gridRow1[j];
		grid->cells[1][j] = gridRow2[j];
	}
	return grid;
}

Dictionary* FindWordsTest::initDictionary(){
	set<string> words = { "CAR", "CARD", "CART", "CAT" };
	set<string> prefixes = { "C", "CA", "CAR", "CARD", "CART", "CAT" };
	Dictionary* dictionary = new Dictionary(words, prefixes);
	return dictionary;
}

void FindWordsTest::test_findAllWords(){
	Dictionary* dictionary = initDictionary();
	Grid* grid = initGrid();
	set<string> found_words = grid->findAllWords(dictionary);
	set<string> expected_words = { "CAR", "CARD", "CAT" };
	EXPECT_EQ(expected_words, found_words);
}

void FindWordsTest::test_EmptyGrid(){
	Dictionary* dictionary = initDictionary();
	Grid* grid = new Grid();
	set<string> found_words = grid->findAllWords(dictionary);
	set<string> expected_words = set<string>();
	EXPECT_EQ(expected_words, found_words);
}

void FindWordsTest::test_EmptyDictionary(){
	Dictionary* dictionary = new Dictionary();
	Grid* grid = initGrid();
	set<string> found_words = grid->findAllWords(dictionary);
	set<string> expected_words = set<string>();
	EXPECT_EQ(expected_words, found_words);
}

