#pragma once
class IslandCount{
private:
	bool** map;
	int height;
	int width;
public:

	IslandCount() {}

	IslandCount(bool** matrix, int height, int width) : map(matrix) {
		this->height = height;
		this->width = width;
	}

	// Assumption: All four edges of the grid are surrounded by water.
	//
	int countIslands() {
		int num = 0;

		if (!map || height <= 0 || width <= 0)
			return num;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (map[i][j]) {
					mergeAdjacentLands(i, j);
					num++;
				}
			}
		}
		return num;
	}

	~IslandCount() {
		for (int i = 0; i < height; i++) {
			delete[] map[i];
		}
		delete[] map;
	}

private:
	void mergeAdjacentLands(int i, int j) {
		if (i < 0 || i >= height || j < 0 || j >= width || map[i][j] == false)
			return;

		map[i][j] = false;

		mergeAdjacentLands(i - 1, j);
		mergeAdjacentLands(i + 1, j);
		mergeAdjacentLands(i, j - 1);
		mergeAdjacentLands(i, j + 1);
	}
};
