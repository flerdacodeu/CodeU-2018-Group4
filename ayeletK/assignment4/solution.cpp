#define LAND true
#define WATER false
#include "dfs.cpp"
#include "grid.cpp"
typedef Grid<bool> Map;
typedef vector<vector<bool>> Map_vec;

class Solution{
    Map _map;
    GridComponentsFinder<bool> _grid_components_finder;
public:
    Solution(): _map(), _grid_components_finder() {}
    Solution(Map_vec* map_vec): _map(map_vec), _grid_components_finder(LAND) {
        int i = 0;
    }
    int count_islands(){
        return _grid_components_finder.count_components(&_map);
    }
};
