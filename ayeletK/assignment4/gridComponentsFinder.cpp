template <typename T>
class GridComponentsFinder{
    Grid<T>* _grid;
    T _value_to_use;  // This class will only work on grid cells with this value. Other cells will be ignored
    unordered_set<Position> _unvisited;
    
    unordered_set<Position> get_unvisited_neighbours(const Position& curr_pos){
        unordered_set<Position> res;
        for (Position pos: _grid->get_neighbours_of_val(curr_pos, _value_to_use)){
            if (_unvisited.find(pos) != _unvisited.end())
                res.insert(pos);
        }
        return res;
    }
    void find_component(const Position& curr_pos, unordered_set<Position>* component){
        component->insert(curr_pos);
        _unvisited.erase(curr_pos);
        for (Position neighbour: get_unvisited_neighbours(curr_pos))
            find_component(neighbour, component);
    }
    
    // TODO: if I have time - implement iterator for Grid class
    // This method initialize _unvisited to be the collection of all grid positions with _value_to_use
    void collect_all_relevant_pos(){
        int rows, cols;
        _grid->get_grid_dimentions(&rows, &cols);
        for (int row = 0; row< rows; ++row){
            for (int col = 0; col < cols; ++col){
                Position pos(row,col);
                if (_grid->get_value(pos) == _value_to_use)
                    _unvisited.insert(pos);
            }
        }
    }
public:
    explicit GridComponentsFinder(T wanted_val = T()): _grid(nullptr), _value_to_use(wanted_val) {}
    // Collect all Grid components
    void find_components(Grid<T>* grid, vector<unordered_set<Position>>* grid_components){
        if (grid == nullptr) return;
        _grid = grid;
        unordered_set<Position> curr_component;
        while (!_unvisited.empty()){
            Position pos = *(_unvisited.begin());
            find_component(pos, &curr_component);
            grid_components->push_back(curr_component);
            curr_component.clear();
        }
    }
    int count_components(Grid<T>* grid){
        if (grid == nullptr) return 0;
        _grid = grid;
        collect_all_relevant_pos();
        vector<unordered_set<Position>> grid_components;
        find_components(grid, &grid_components);
        return grid_components.size();
    }
};
