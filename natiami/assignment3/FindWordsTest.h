#include<string>
#include<vector>
#include<set>
#include"Grid.h"
#include"lib.h"

class FindWordsTest{
public:
	void test();
private:
	Grid* initGrid();
	Dictionary* initDictionary();
	void test_findAllWords();
	void test_EmptyGrid();
	void test_EmptyDictionary();
};