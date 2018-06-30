#include "IslandCount.h"
#include "test_library.h"
#include <iostream>

using namespace std;

void testEqual(IslandCount* islandCount, int num) {
	EXPECT_EQ(islandCount->countIslands(), num);
}

int main() {
	bool** map = new bool*[4];
	map[0] = new bool[4]{ false, true, false, true };
	map[1] = new bool[4]{ true, true, false, false };
	map[2] = new bool[4]{ false, false, true, false };
	map[3] = new bool[4]{ false, false, true, false };
	
	IslandCount* islandCount = new IslandCount(map, 4, 4);

	testEqual(islandCount, 3);

	
	// Test with null map
	IslandCount* islandCountWithoutMap = new IslandCount(nullptr, 0, 0);

	testEqual(islandCountWithoutMap, 0);


	// Test with one island across th whole map
	bool** mapWithOneIsland = new bool*[1];
	mapWithOneIsland[0] = new bool[3]{ true, true, true };

	IslandCount* islandCountTest = new IslandCount(mapWithOneIsland, 1, 3);
	testEqual(islandCountTest, 1);


	delete islandCount;
	delete islandCountWithoutMap;
	delete islandCountTest;

	system("PAUSE");
	return 0;
}
