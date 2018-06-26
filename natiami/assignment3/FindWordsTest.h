#include<string>
#include<vector>
#include<set>
#include"Grid.h"
#include"lib.h"

class FindWordsTest{
public:
	void test();
private:
	Dictionary* dictionary;
	Grid* grid;

	void initGrid();
	void initDictionary();
	void test_findAllWords();
	void test_EmptyGrid();
	void test_EmptyDictionary();
};
