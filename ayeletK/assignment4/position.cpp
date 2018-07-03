#include <utility>

class Position{
    pair<int,int> _pos;
public:
    explicit Position(): _pos() {}
    Position(int row, int col): _pos(row,col) {}
    int get_row() const { return _pos.first; }
    int get_col() const { return _pos.second; }
    bool operator==(const Position& p) const { return _pos == p._pos; }
    bool operator<(const Position& p) const { return _pos < p._pos; }
    
};
namespace std {
    template <> struct hash<Position> {
        inline size_t operator()(const Position &pos) const {
            std::hash<int> int_hasher;
            int row = pos.get_row();
            int col = pos.get_col();
            return int_hasher(row*col) ^ int_hasher(col);
        }
    };
}
