#include <iostream>
#include "codeu_test_lib.h"

#define LAND true
#define SEA false
#define UNMARKED 0

using namespace std;

int searchNeighbors(int rows, int cols, int row, int col, int **islandMark) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return -1;
    }
    if (row - 1 >= 0 && islandMark[row - 1][col] != UNMARKED) {
        return islandMark[row - 1][col];
    }
    if (col - 1 >= 0 && islandMark[row][col - 1] != UNMARKED) {
        return islandMark[row][col - 1];
    }
    if (row + 1 < rows && islandMark[row + 1][col] != UNMARKED) {
        return islandMark[row + 1][col];
    }
    if (col + 1 < cols && islandMark[row][col + 1] != UNMARKED) {
        return islandMark[row][col + 1];
    }
    return UNMARKED;
}

void markIsland(int rows, int cols, int row, int col, int **islandMark, bool **grid, int islandNum) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] == SEA || islandMark[row][col] != UNMARKED) {
        return;
    }
    islandMark[row][col] = islandNum;
    markIsland(rows, cols, row + 1, col, islandMark, grid, islandNum);
    markIsland(rows, cols, row, col + 1, islandMark, grid, islandNum);
    markIsland(rows, cols, row - 1, col, islandMark, grid, islandNum);
    markIsland(rows, cols, row, col - 1, islandMark, grid, islandNum);
}

int countIslands(int rows, int cols, bool **grid) {
    int **islandMark = new int*[rows];
    for (int i = 0; i < rows; i ++) {
        islandMark[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            islandMark[i][j] = 0;
        }
    }
    int islandCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == LAND && islandMark[i][j] == UNMARKED) {
                int islandNum = searchNeighbors(rows, cols, i, j, islandMark);
                if (islandNum == UNMARKED) {
                    islandNum = ++islandCount;
                }
                markIsland(rows, cols, i, j, islandMark, grid, islandNum);
            }
        }
    }

    for (int i = 0; i < rows; i ++) {
        delete islandMark[i];
    }
    delete islandMark;

    return islandCount;
}

bool **createGrid(int rows, int cols) {
    bool **grid = new bool*[rows];
    for (int i = 0; i < rows; i ++) {
        grid[i] = new bool[cols];
    }
    return grid;
}

void resetGrid(int rows, int cols, bool **grid, bool val = false) {
    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = val;
        }
    }
}

void deleteGrid(int rows, bool **grid) {
    for (int i = 0; i < rows; i ++) {
        delete grid[i];
    }
    delete grid;
}

void printGrid(int rows, int cols, bool **grid) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int rows = 4, cols = 4;
    bool **grid = createGrid(rows, cols);
    resetGrid(rows, cols, grid);

    // Test 1 - from the assignment PDF
    grid[0][1] = grid[0][3] = grid[1][0] = grid[1][1] = grid[2][2] = grid[3][2] = true;
    printGrid(rows, cols, grid);
    EXPECT_EQ(countIslands(rows, cols, grid), 3);

    // Test 2 - connect 2 islands
    grid[0][2] = true;
    printGrid(rows, cols, grid);
    EXPECT_EQ(countIslands(rows, cols, grid), 2);

    // Test 3 - connect 3rd island
    grid[2][1] = true;
    printGrid(rows, cols, grid);
    EXPECT_EQ(countIslands(rows, cols, grid), 1);

    // Test 4 - all sea
    resetGrid(rows, cols, grid);
    printGrid(rows, cols, grid);
    EXPECT_EQ(countIslands(rows, cols, grid), 0);

    //Test 5 - all land
    resetGrid(rows, cols, grid, true);
    printGrid(rows, cols, grid);
    EXPECT_EQ(countIslands(rows, cols, grid), 1);

    //Test 6 - maximum number of islands
    resetGrid(rows, cols, grid);
    grid[0][0] = grid[0][2] = grid[1][1] = grid[1][3] = grid[2][0] = grid[2][2] = grid[3][1] = grid[3][3] = true;
    printGrid(rows, cols, grid);
    EXPECT_EQ(countIslands(rows, cols, grid), 8);

    //Test 7 - 1 land tile
    resetGrid(rows, cols, grid);
    grid[3][3] = true;
    printGrid(rows, cols, grid);
    EXPECT_EQ(countIslands(rows, cols, grid), 1);

    deleteGrid(rows, grid);

    return 0;
}