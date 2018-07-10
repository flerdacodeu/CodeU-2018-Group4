#pragma once
class IslandCount{
private:
	bool** isLand;
	int height;
	int width;
public:

	IslandCount() {}

	IslandCount(bool** matrix, int height, int width) : isLand(matrix) {
		this->height = height;
		this->width = width;
	}

	int countIslands() {
		int num = 0;

		if (!isLand || height <= 0 || width <= 0)
			return num;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (isLand[i][j]) {
					mergeAdjacentLands(i, j);
					num++;
				}
			}
		}
		return num;
	}

	~IslandCount() {
		for (int i = 0; i < height; i++) {
			delete[] isLand[i];
		}
		delete[] isLand;
	}

private:
	void mergeAdjacentLands(int i, int j) {
		if (i < 0 || i >= height || j < 0 || j >= width || isLand[i][j] == false)
			return;

		isLand[i][j] = false;

		mergeAdjacentLands(i - 1, j);
		mergeAdjacentLands(i + 1, j);
		mergeAdjacentLands(i, j - 1);
		mergeAdjacentLands(i, j + 1);
	}
};

