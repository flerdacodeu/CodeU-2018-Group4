#include "test.hpp"
#include "disjoint_set.hpp"

// This solution is, I believe, more efficient than a recursive one
// But requires an additional data structure
// That may be a problem if map is too big

#define LAND true
#define SEA false

// Map must be rectangular
bool is_map_valid (std::vector<std::vector<bool> > tile_map)
{
    if (tile_map.size() == 0)
        return false;
    for (int i = 0; i < tile_map.size(); i++)
        if (tile_map[i].size() != tile_map[0].size())
            return false;
    return true;        
}

// Two tiles belong to the same island if they are both LAND 
// and are adjacent horizontally or vertically, but not diagonally.

// Number of rows and number of columns are computed internally for given map
// That is why I did not put them as the function parameters
// However if it is a strong requirement to match the described interface
// I can rewrite the function and make them explicit 
int count_islands (std::vector<std::vector<bool> > tile_map)
{
    if (!is_map_valid(tile_map))
        return 0;
    int height = tile_map.size();    
    int width = tile_map[0].size();    
    int island_counter = 0;
    DisjointSet islands_set (height * width);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tile_map[i][j] == SEA)
                continue;
            island_counter++;    
            if ((j > 0) && (tile_map[i][j - 1] == LAND))
                if (islands_set.unite (i * width + j, i * width + j - 1))
                    island_counter--;
            if ((i > 0) && (tile_map[i - 1][j] == LAND))
                if (islands_set.unite (i * width + j, (i - 1) * width + j))
                    island_counter--;
        }
    }
    return island_counter;
}

void test_empty_map() 
{
    std::vector<std::vector<bool> > empty_tile_map;
    EXPECT_EQ(0, count_islands (empty_tile_map));
}

void test_invalid_map()
{
    std::vector<std::vector<bool> > invalid_tile_map({{LAND, LAND, SEA}, {SEA, LAND}});
    EXPECT_EQ(0, count_islands (invalid_tile_map));
}

void test_valid_map()
{
    std::vector<std::vector<bool> > valid_tile_map({{SEA, LAND, SEA, LAND}, {LAND, LAND, SEA, SEA}, {SEA, SEA, LAND, SEA}, {SEA, SEA, LAND, SEA}});
    EXPECT_EQ(3, count_islands (valid_tile_map));
}

void test_map_with_no_sea()
{
    std::vector<std::vector<bool> > no_sea_tile_map({{LAND, LAND, LAND}, {LAND, LAND, LAND}});
    EXPECT_EQ(1, count_islands (no_sea_tile_map));
}

void test_map_with_no_land()
{
    std::vector<std::vector<bool> > no_land_tile_map({{SEA, SEA}, {SEA, SEA}, {SEA, SEA}});
    EXPECT_EQ(0, count_islands (no_land_tile_map));
}

int main ()
{
    test_empty_map();
    test_invalid_map();
    test_valid_map();
    test_map_with_no_sea();
    test_map_with_no_land();
    return 0;
}