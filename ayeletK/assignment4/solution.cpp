#define LAND true
#define WATER false
#include "dfs.cpp"
#include "grid.cpp"
typedef Grid<bool> Map;

class Solution{
    Map _map;
    DFS<bool> _dfs;
    
    // TODO: if I have time - implement iterator for Grid class
    void collect_all_land_tile_pos(unordered_set<Position>* land_tile){
        int rows, cols;
        _map.get_grid_dimentions(&rows, &cols);
        for (int row = 0; row< rows; ++row){
            for (int col = 0; col < cols; ++col){
                Position pos(row,col);
                if (_map.get_value(&pos) == LAND)
                    land_tile->insert(pos);
            }
        }
    }
public:
    Solution(): _map(), _dfs(LAND) {}
    Solution(int rows_num, int cols_num, bool** map): _map(rows_num,cols_num,map), _dfs(LAND) {}
    int count_islands(){
        unordered_set<Position> land_tile;
        collect_all_land_tile_pos(&land_tile);
        vector<unordered_set<Position>> islands;
        _dfs.run_DFS(&land_tile, &islands);
        return islands.size();
    }
    
};
