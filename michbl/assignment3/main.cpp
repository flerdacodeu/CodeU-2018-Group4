#include <iostream>
#include <set>
#include "Dictionary.hpp"
#include "Grid.hpp"
#include "codeu_test_lib.h"

enum Direction {
    LEFT, RIGHT, UP, DOWN, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};

void getNextIdxs(const int row, const int col, const Direction dir, int &nextRow, int &nextCol) {
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

void wordSearchBT(const Dictionary &dict, Grid &grid, int row, int col, set<string> &res, string &word) {
    char c;
    if (!grid.getChar(row, col, c) || grid.visitedCell(row, col)) {
        return;
    }

    word.push_back(c);
    grid.markVisited(row, col);
    if (dict.isWord(word)) {
        res.insert(word);
    }

    if (!dict.isPrefix(word)) {
        word.pop_back();
        grid.markUnvisited(row, col);
        return;
    }

    static const Direction dirs[] = {LEFT, RIGHT, UP, DOWN, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
    int nextRow, nextCol;
    for (Direction dir : dirs) {
        getNextIdxs(row, col, dir, nextRow, nextCol);
        wordSearchBT(dict, grid, nextRow, nextCol, res, word);
    }
    word.pop_back();
    grid.markUnvisited(row, col);
}

set<string> wordSearch(const Dictionary &dict, Grid &grid) {
    int h = grid.getHeight();
    int w = grid.getWidth();
    set<string> result;
    result.clear();
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            string word = "";
            grid.clearVisited();
            wordSearchBT(dict, grid, row, col, result, word);
        }
    }
    return result;
}

int main() {
    vector<char> g = {'A', 'A', 'R', 'T', 'C', 'D'};
    Grid grid(g, 2, 3);

    // test assignment example
    Dictionary dict1({"CAR", "CARD", "CART", "CAT"});
    set<string> result = wordSearch(dict1, grid);

    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.find("CAR") != result.end());
    EXPECT_TRUE(result.find("CARD") != result.end());
    EXPECT_TRUE(result.find("CAT") != result.end());

    // test empty word isn't found
    Dictionary dict2({"CAR", "CARD", "CART", "CAT", ""});
    result = wordSearch(dict2, grid);

    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.find("CAR") != result.end());
    EXPECT_TRUE(result.find("CARD") != result.end());
    EXPECT_TRUE(result.find("CAT") != result.end());

    // test no word can be found
    Dictionary dict3({"HOUSE", "BIT", "FLUSH"});
    result = wordSearch(dict3, grid);
    EXPECT_EQ(result.size(), 0);

    // test empty dictionary
    Dictionary dict4 = Dictionary();
    result = wordSearch(dict4, grid);
    EXPECT_EQ(result.size(), 0);

    // test not visiting same cell twice in same word
    Dictionary dict5({"CAR", "CARD", "CART", "CAT", "CARDR", "TATA", "TACARA"});
    result = wordSearch(dict5, grid);

    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.find("CAR") != result.end());
    EXPECT_TRUE(result.find("CARD") != result.end());
    EXPECT_TRUE(result.find("CAT") != result.end());

    return 0;
}