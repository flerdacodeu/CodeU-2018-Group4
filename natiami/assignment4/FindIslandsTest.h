#include<vector>
#include"FindIslands.h"
#include"lib.h"

class FindIslandsTest{
public:
	void test();
	FindIslands findIslands;

private:
	void test_findNumberOfIslands();
	void test_diagonalLands();
	void test_EmptyisLandTile();
	void test_allWater();
	void test_allLand();
};
