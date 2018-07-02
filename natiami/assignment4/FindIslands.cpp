#include"FindIslands.h"

FindIslands::FindIslands(){}

FindIslands::FindIslands(vector<vector<bool> >& isLandTile) {
	this->isLandTile = isLandTile;
	nr_row = isLandTile.size();
	if (nr_row != 0) nr_column = isLandTile[0].size();

	for (int i = 0; i < nr_row; i++)
	{
		assert(isLandTile[i].size() == nr_column);
	}
	moves = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
}

bool FindIslands::isInBounds(int i, int j){
	return i >= 0 && i < nr_row && j >= 0 && j < nr_column;
}

void FindIslands::visitOneIsland(vector<vector<bool> >& visited, int i, int j){
	if (!isInBounds(i, j) || !isLandTile[i][j] || visited[i][j]) {
		return;
	}
	visited[i][j] = true;

	for (const pair<int, int>& move : moves)
	{
		visitOneIsland(visited, i + move.first, j + move.second);
	}
}

int FindIslands::findNumberOfIslands(){

	vector<vector<bool> > visited(nr_row, vector<bool>(nr_column));
	int nr_island = 0;

	for (int i = 0; i < nr_row; i++)
	{
		for (int j = 0; j < nr_column; j++)
		{
			if (!visited[i][j] && isLandTile[i][j]){
				visitOneIsland( visited, i, j);
				++nr_island;
			}
		}
	}
	return nr_island;
}
