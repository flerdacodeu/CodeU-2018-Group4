#include "position.cpp"
#include "dictionary.cpp"

class Grid{
    int _rows, _cols;
    vector<vector<char>> _grid;
    bool update_location(int* row, int* col){
        if (*col + 1 < _cols){ 
            (*col)++;
            return true;
        }
        else if (*row + 1 < _rows) {
            *col = 0;
            (*row)++;
            return true;
        }
        return false;
    }
    bool legal_row(int row){
        return row >=0 && row < _rows;
    }
    bool legal_col(int col){
        return col >=0 && col < _cols;
    }
    bool legal_position(Position pos){
        return legal_row(pos._row) && legal_col(pos._col);
    }
    set<Position> get_neighbours(Position curr_pos){
        Position neighbour;
        set<Position> neighbours;
        for(int row=curr_pos._row - 1; row <= curr_pos._row + 1; ++row){
            for(int col=curr_pos._col - 1; col <= curr_pos._col + 1; ++col){
                neighbour = Position(row, col);
                if (legal_position(neighbour) && !curr_pos.equal(neighbour)) {
                    neighbours.insert(neighbour);
                }
            }
        }
        return neighbours;
    }
    set<Position> get_unvisited_neighbours(Position curr_pos, set<Position>* visited){
        set<Position> res;
        for (Position pos: get_neighbours(curr_pos)){
            if (visited->find(pos) == visited->end())
                res.insert(pos);
        }
        return res;
    }
    void words_with_prefix(Position curr_pos, set<Position>* visited, 
    Dictionary* dict, vector<char>* prefix, set<string>* words){
        prefix->push_back(get_value(curr_pos));
        visited->insert(curr_pos);
        string curr_prefix = string(prefix->begin(), prefix->end());
        if (! dict->is_prefix(curr_prefix)) {
            visited->erase(curr_pos);
            prefix->pop_back();
            return;
        }
        if (dict->is_word(curr_prefix))
            words->insert(curr_prefix);
        for (Position neighbour: get_unvisited_neighbours(curr_pos, visited))
            words_with_prefix(neighbour, visited, dict, prefix, words);
        visited->erase(curr_pos);
        prefix->pop_back();
    }
    set<string> find_words_from_position(Position start_pos, Dictionary* dict){
        set<string> res;
        vector<char> prefix;
        set<Position> visited;  // can be improved to hashset ?
        words_with_prefix(start_pos, &visited, dict, &prefix, &res);
        return res;

    }
    set<string> find_all_words(Dictionary* dict){
        set<string> res;
        set<string> iteration_res;
        for (int row = 0; row<_rows; ++row){
            for (int col = 0; col < _cols; ++col){
                iteration_res = find_words_from_position(Position(row,col),dict);
                res.insert(iteration_res.begin(), iteration_res.end());
            }
        }
        return res;
    }
public:
    explicit Grid(int rows, int cols): _rows(rows), _cols(cols) {
        // _grid.reserve(_rows);
    }
    void initialize_grid(vector<char> data){
        int row = 0, col = 0;
        for (int i = 0; i < data.size(); ++i){
            if (col == 0){
                _grid.push_back(vector<char>());
            }
            _grid.at(row).push_back(data.at(i));
            if (!update_location(&row, &col)) break;
        }
    }
    void update_value(int row, int col, char val){
        if (legal_row(row) && legal_col(col))
            _grid.at(row).at(col) = val;
    }
    char get_value(int row, int col){
        if (legal_row(row) && legal_col(col))
            return _grid.at(row).at(col);
    }
    char get_value(Position pos){
        if (legal_position(pos))
            return _grid.at(pos._row).at(pos._col);
    }
    void get_grid_dimentions(int* rows, int* cols){
        *rows = _rows;
        *cols = _cols;
    }
    // --------------------------- Q1 solution --------------------------- //
    
    set<string> get_all_words_in_grid(Dictionary* dictionary){
        return find_all_words(dictionary);;
    }
};
