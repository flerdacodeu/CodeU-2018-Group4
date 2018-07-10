#include "IslandCount.h"
#include "test_library.h"
#include <iostream>

using namespace std;


int main() {
	bool** map = new bool*[4];
	map[0] = new bool[4]{ false, true, false, true };
	map[1] = new bool[4]{ true, true, false, false };
	map[2] = new bool[4]{ false, false, true, false };
	map[3] = new bool[4]{ false, false, true, false };
	
	IslandCount islandCount(map, 4, 4);
	EXPECT_EQ(islandCount.countIslands(), 3);
		
	// Test with null map
	IslandCount islandCountWithoutMap(nullptr, 0, 0);
	EXPECT_EQ(islandCountWithoutMap.countIslands(), 0);
	
	// Test with one island across th whole map
	bool** mapWithOneIsland = new bool*[1];
	mapWithOneIsland[0] = new bool[3]{ true, true, true };
	IslandCount islandCountTest(mapWithOneIsland, 1, 3);
	EXPECT_EQ(islandCountTest.countIslands(), 1);

	
	system("PAUSE");
	return 0;
}
