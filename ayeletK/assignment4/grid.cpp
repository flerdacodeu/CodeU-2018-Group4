#include "position.cpp"
#include <vector>
#include <unsorted_set>
#include <stdlib.h>

using namespace std;

vector<Position> delta_positions = {Position(-1,0), Position(0,-1), Position(1,0), Position(0,1)};

template <typename T>
class Grid{
    int _rows, _cols;
    vector<vector<T>> _grid;
    
    bool is_legal_row(int row){
        return row >=0 && row < _rows;
    }
    bool is_legal_col(int col){
        return col >=0 && col < _cols;
    }
public:
    Grid(): Grid(nullptr) {}
    explicit Grid(vector<vector<T>>* data): _rows(-1), _cols(-1) {
        if (data != nullptr) {
            _grid = *data;
            _rows = _grid.size();
            if (_rows > 0) _cols = _grid[0].size();
        }
    }
    T get_value(const Position& pos){
        if (is_legal_position(pos)){
            return _grid[pos.get_row()][pos.get_col()];
        }
        return T();
    }
    void get_grid_dimentions(int* rows, int* cols){
        *rows = _rows;
        *cols = _cols;
    }
    bool is_legal_position(const Position& pos){
        return is_legal_row(pos.get_row()) && is_legal_col(pos.get_col());
    }
    unordered_set<Position> get_neighbours_of_val(const Position& curr_pos, T wanted_val){
        unordered_set<Position> neighbours;
        Position neighbour;
        int row, col;
        for (Position pos: delta_positions){
            neighbour = curr_pos + pos;
            if (neighbour == curr_pos) continue;
            if (get_value(neighbour) == wanted_val)
                neighbours.insert(neighbour);
        }
        return neighbours;
    }
};
