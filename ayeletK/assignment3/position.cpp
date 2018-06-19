class Position{
public:
    int _row;
    int _col;
    Position(): Position(-1 ,-1) {}
    Position(int row, int col): _row(row), _col(col) {}
    Position(const Position& pos): _row(pos._row), _col(pos._col) {}
    Position& operator=(const Position& pos) {
        _row = pos._row;
        _col = pos._col;
        return *this;
    }
    bool operator<(const Position& pos) const{
        return _row < pos._row || _col < pos._col;
    }
    bool equal(Position pos){
        return _row == pos._row && _col == pos._col;
    }
};
