#include<iostream>
#include"FindIslands.h"

using namespace std;

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
	visited[i][j] = true;
	list<pair<int, int> > queue;
	pair<int, int> curr_tile;
	int row, column;
	
	queue.push_back(make_pair(i, j));

	while (!queue.empty()){
		curr_tile = queue.front();
		visited[curr_tile.first][curr_tile.second] = true;
		queue.pop_front();

		for (const pair<int, int>& move : moves){
			row = curr_tile.first + move.first;
			column = curr_tile.second + move.second;
			if (isInBounds(row, column) && isLandTile[row][column] && !visited[row][column]){
				queue.push_back(make_pair(row, column));
			}
		}
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
