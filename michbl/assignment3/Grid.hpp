#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

using namespace std;

class Grid {
private:
    vector<char> grid;
    vector<bool> visited;
    int height;
    int width;
public:
    Grid(const vector<char> g, const int h, const int w) {
        if (h * w != g.size()) {
            throw runtime_error("Grid dimensions don't match");
        }
        this->grid = g;
        this->height = h;
        this->width = w;
        this->clearVisited();
    }

    ~Grid() {}

    int getHeight() const {
        return this->height;
    }

    int getWidth() const {
        return this->width;
    }

    bool getChar(const int row, const int col, char &c) const {
        if (row < 0 || row >= this->height || col < 0 || col >= this->width) {
            return false;
        }

        int idx = row * this->width + col;
        c = this->grid[idx];
        return true;
    }

    void clearVisited() {
        this->visited.clear();
        for (int i = 0; i < this->height * this->width; i++) {
            this->visited.push_back(false);
        }
    }

    void markVisited(int row, int col) {
        if (row < 0 || row >= this->height || col < 0 || col >= this->width) {
            return;
        }
        int idx = row * this->width + col;
        this->visited[idx] = true;
    }

    void markUnvisited(int row, int col) {
        if (row < 0 || row >= this->height || col < 0 || col >= this->width) {
            return;
        }
        int idx = row * this->width + col;
        this->visited[idx] = false;
    }

    bool visitedCell(int row, int col) {
        if (row < 0 || row >= this->height || col < 0 || col >= this->width) {
            return false;
        }
        int idx = row * this->width + col;
        return this->visited[idx];
    }
};


#endif //GRID_HPP
