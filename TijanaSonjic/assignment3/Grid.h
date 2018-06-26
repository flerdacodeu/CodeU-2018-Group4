#pragma once

#include "iostream"
using namespace std;

class Grid{
	class GridCell {
	public:
		char letter;
		bool visited;
		
		GridCell() {}

		GridCell(char letter, bool visited) {
			this->letter = letter;
			this->visited = visited;
		}

		
	};

	GridCell** grid;
	int height, width;
public:
	Grid(int n, int m, char letters[]) {
		height = n;
		width = m;
		grid = new GridCell*[height];
		for (int i = 0; i < height; i++) {
			grid[i] = new GridCell[width];
		}

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				grid[i][j] = *(new GridCell(letters[i*height + j], false));
	}

	void print() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				cout << grid[i][j].letter << " ";
			cout << endl;
		}
	}

	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}

	bool isViseted(int i, int j) {
		return grid[i][j].visited;
	}

	char getLetter(int i, int j) {
		return grid[i][j].letter;
	}

	void setVisitedValue(int i, int j, bool value) {
		grid[i][j].visited = value;
	}

	bool isEmpty() {
		return grid == nullptr;
	}

	~Grid() {
		for (int i = 0; i < height; i++)
			delete[] grid[i];

		delete[] grid;
	}
};

