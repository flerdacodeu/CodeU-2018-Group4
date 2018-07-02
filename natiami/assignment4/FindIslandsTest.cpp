#include"FindIslandsTest.h"

void FindIslandsTest::test(){
	test_findNumberOfIslands();
	test_diagonalLands();
	test_EmptyisLandTile();
	test_allWater();
	test_allLand();
}

void FindIslandsTest::test_findNumberOfIslands(){
	vector<vector<bool> > isLandTile{ { false, true, false, true },
								{ true, true, false, false },
								{ false, false, true, false },
								{ false, false, true, false } };

	EXPECT_EQ(3, FindIslands(isLandTile).findNumberOfIslands());
}

void FindIslandsTest::test_diagonalLands(){
	vector<vector<bool> > isLandTile{ { true, false, true, false },
										{ false, true, false, true },
										{ true, false, true, false },
										{ false, true, false, true } };

	EXPECT_EQ(8, FindIslands(isLandTile).findNumberOfIslands());
}

void FindIslandsTest::test_EmptyisLandTile(){
	vector<vector<bool> > isLandTile;
	EXPECT_EQ(0, FindIslands(isLandTile).findNumberOfIslands());
}

void FindIslandsTest::test_allWater(){
	vector<vector<bool> > isLandTile{ { false, false, false, false },
										{ false, false, false, false },
										{ false, false, false, false },
										{ false, false, false, false } };

	EXPECT_EQ(0, FindIslands(isLandTile).findNumberOfIslands());
}

void FindIslandsTest::test_allLand(){
	vector<vector<bool> > isLandTile{ { true, true, true, true },
										{ true, true, true, true },
										{ true, true, true, true },
										{ true, true, true, true } };

	EXPECT_EQ(1, FindIslands(isLandTile).findNumberOfIslands());
}
