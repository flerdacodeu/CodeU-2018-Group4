#include"FindIslandsTest.h"

void FindIslandsTest::test(){
	test_findNumberOfIslands();
	test_diagonalLands();
	test_EmptyMapOfTiles();
	test_allWater();
	test_allLand();
}

void FindIslandsTest::test_findNumberOfIslands(){
	vector<vector<bool> > mapOfTiles{ { false, true, false, true },
								{ true, true, false, false },
								{ false, false, true, false },
								{ false, false, true, false } };
	findIslands = FindIslands(4, 4, mapOfTiles);

	int expected_nr_island = 3;
	EXPECT_EQ(expected_nr_island, findIslands.findNumberOfIslands());
}

void FindIslandsTest::test_diagonalLands(){
	vector<vector<bool> > mapOfTiles{ { true, false, true, false },
										{ false, true, false, true },
										{ true, false, true, false },
										{ false, true, false, true } };
	findIslands = FindIslands(4, 4, mapOfTiles);

	int expected_nr_island = 8;
	EXPECT_EQ(expected_nr_island, findIslands.findNumberOfIslands());
}

void FindIslandsTest::test_EmptyMapOfTiles(){
	vector<vector<bool> > mapOfTiles;
	findIslands = FindIslands(0, 0, mapOfTiles);

	int expected_nr_island = 0;
	EXPECT_EQ(expected_nr_island, findIslands.findNumberOfIslands());
}

void FindIslandsTest::test_allWater(){
	vector<vector<bool> > mapOfTiles{ { false, false, false, false },
										{ false, false, false, false },
										{ false, false, false, false },
										{ false, false, false, false } };
	findIslands = FindIslands(4, 4, mapOfTiles);

	int expected_nr_island = 0;
	EXPECT_EQ(expected_nr_island, findIslands.findNumberOfIslands());
}

void FindIslandsTest::test_allLand(){
	vector<vector<bool> > mapOfTiles{ { true, true, true, true },
										{ true, true, true, true },
										{ true, true, true, true },
										{ true, true, true, true } };
	findIslands = FindIslands(4, 4, mapOfTiles);

	int expected_nr_island = 1;
	EXPECT_EQ(expected_nr_island, findIslands.findNumberOfIslands());
}