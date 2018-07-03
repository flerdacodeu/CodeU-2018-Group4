#include "position.cpp"
#include <vector>
#include <unsorted_set>

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
    Grid(): _rows(-1), _cols(-1) {}
    Grid(int rows_num, int cols_num, bool** data){
        _rows = rows_num;
        _cols = cols_num;
        for (int row = 0; row < _rows; ++row){
            _grid.push_back(vector<T>(_cols));
            for (int col = 0; col < _cols; ++col){
                _grid[row][col] = data[row][col];
            }
        }
    }
    explicit Grid(vector<vector<T>>* data): _grid(*data) {}
    void update_value(Position* pos, T val){
        if (is_legal_position(pos)) 
            _grid[pos->get_row()][pos->get_col()] = val;
    }
    T get_value(Position* pos){
        if (is_legal_position(pos)){
            return _grid[pos->get_row()][pos->get_col()];
        }
        return T();
    }
    void get_grid_dimentions(int* rows, int* cols){
        *rows = _rows;
        *cols = _cols;
    }
    bool is_legal_position(Position* pos){
        return is_legal_row(pos->get_row()) && is_legal_col(pos->get_col());
    }
    unordered_set<Position> get_neighbours(Position* pos, T wanted_val){
        unordered_set<Position> neighbours;
        Position neighbour;
        for (int i: DELTA){
            for (int j: DELTA){
                if (abs(i-j) != 1) continue;
                neighbour = Position(pos->get_row()+i, pos->get_col()+j);
                if (is_legal_position(&neighbour) && get_value(&neighbour) == wanted_val)
                        neighbours.insert(neighbour);
            }
        }
        return neighbours;
    }
};
