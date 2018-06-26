#include "FindWordsTest.h"

void FindWordsTest::test(){
	test_findAllWords();
	test_EmptyGrid();
	test_EmptyDictionary();
}

void FindWordsTest::initGrid(){
	grid = new Grid(3, 2);
	grid->cells = { { 'A', 'A', 'R' }, { 'T', 'C', 'D' } };
}

void FindWordsTest::initDictionary(){
	set<string> words = { "CAR", "CARD", "CART", "CAT" };
	set<string> prefixes = { "C", "CA", "CAR", "CARD", "CART", "CAT" };
	dictionary = new Dictionary(words, prefixes);
}

void FindWordsTest::test_findAllWords(){
	initDictionary();
	initGrid();
	set<string> expected_words = { "CAR", "CARD", "CAT" };
	EXPECT_EQ(expected_words, grid->findAllWords(dictionary));
}

void FindWordsTest::test_EmptyGrid(){
	initDictionary();
	Grid emptyGrid;
	set<string> empty_expected_words;
	EXPECT_EQ(empty_expected_words, emptyGrid.findAllWords(dictionary));
}

void FindWordsTest::test_EmptyDictionary(){
	Dictionary* dictionary = new Dictionary();
	initGrid();
	set<string> expected_words = set<string>();
	EXPECT_EQ(expected_words, grid->findAllWords(dictionary));
}

