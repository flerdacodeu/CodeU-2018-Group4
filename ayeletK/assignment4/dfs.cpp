#include "grid.cpp"

// TODO: should be static class?
template <typename T>
class DFS{
    Grid<T>* _grid;
    T _wanted_val;  // what is the interesting data in the grid.
    unordered_set<Position> _unvisited;
    
    unordered_set<Position> get_unvisited_neighbours(Position* curr_pos){
        unordered_set<Position> res;
        for (Position pos: _grid->get_neighbours(curr_pos, _wanted_val)){
            if (_unvisited.find(pos) != _unvisited.end())
                res.insert(pos);
        }
        return res;
    }
    void find_DFS_component(Position* curr_pos, unordered_set<Position>* component){
        component->insert(*curr_pos);
        _unvisited.erase(*curr_pos);
        for (Position neighbour: get_unvisited_neighbours(curr_pos))
            find_DFS_component(&neighbour, component);
    }
    void remove_component(unordered_set<Position>* data_of_interest, unordered_set<Position>* component){
        for (auto iter = component->begin(); iter != component->end(); ++iter){
            data_of_interest->erase(*iter);
        }
    }
public:
    explicit DFS(T wanted_val): _wanted_val(wanted_val) {}
    // Collect all DFS components
    void run_DFS(unordered_set<Position>* data_of_interest, 
                vector<unordered_set<Position>>* dfs_components){
        _unvisited = unordered_set<Position>(*data_of_interest);
        unordered_set<Position> curr_component;
        while (!_unvisited.empty()){
            Position pos = *(_unvisited.begin());
            find_DFS_component(&pos, &curr_component);
            dfs_components->push_back(curr_component);
            // remove_component(data_of_interest, &curr_component);
            curr_component.clear();
        }
    }
};
