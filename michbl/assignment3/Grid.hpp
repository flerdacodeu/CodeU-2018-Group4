#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <vector>

using namespace std;

enum Direction {
    LEFT, RIGHT, UP, DOWN, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, NONE
};

class Grid {
private:
    vector<char> grid;
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
    }

    ~Grid() {}

    int getHeight() {
        return this->height;
    }

    int getWidth() {
        return this->width;
    }

    bool getChar(const int row, const int col, char &c) {
        if (row < 0 || row >= this->height || col < 0 || col >= this->width) {
            return false;
        }

        int idx = row * this->width + col;
        c = this->grid[idx];
        return true;
    }

    void getNextIdxs(const int row, const int col, int &nextRow, int &nextCol, Direction dir = NONE) {
        switch (dir) {
            case LEFT:
                nextRow = row;
                nextCol = col - 1;
                break;
            case RIGHT:
                nextRow = row;
                nextCol = col + 1;
                break;
            case UP:
                nextRow = row - 1;
                nextCol = col;
                break;
            case DOWN:
                nextRow = row + 1;
                nextCol = col;
                break;
            case TOP_LEFT:
                nextRow = row - 1;
                nextCol = col - 1;
                break;
            case TOP_RIGHT:
                nextRow = row - 1;
                nextCol = col + 1;
                break;
            case BOTTOM_LEFT:
                nextRow = row + 1;
                nextCol = col - 1;
                break;
            case BOTTOM_RIGHT:
                nextRow = row + 1;
                nextCol = col + 1;
                break;
            default:
                nextRow = row;
                nextCol = col;
                break;
        }
    }
};


#endif //GRID_HPP
