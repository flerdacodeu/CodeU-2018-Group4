#include"FindIslands.h"

FindIslands::FindIslands(){}

FindIslands::FindIslands(int nr_row, int nr_column, vector<vector<bool> >& mapOfTiles) : nr_row(nr_row), nr_column(nr_column), mapOfTiles(mapOfTiles){
}

bool FindIslands::checkBounds( int i, int j){
	return i >= 0 && i < nr_row && j >= 0 && j < nr_column;
}

void FindIslands::visitOneIsland(vector<vector<bool> >& visited, int i, int j){
	visited[i][j] = true;
	vector<pair<int, int> > moves{ { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	int row, column;

	for (size_t k = 0; k < moves.size(); k++)
	{
		row = i + moves[k].first;
		column = j + moves[k].second;
		if (checkBounds(row, column)){
			if (!visited[row][column] && mapOfTiles[row][column])
				visitOneIsland( visited, row, column);
		}
	}

}

int FindIslands::findNumberOfIslands(){

	vector<vector<bool> > visited(nr_row, vector<bool>(nr_column));
	int nr_island = 0;

	for (size_t i = 0; i < nr_row; i++)
	{
		for (size_t j = 0; j < nr_column; j++)
		{
			if (!visited[i][j] && mapOfTiles[i][j]){
				visitOneIsland( visited, i, j);
				++nr_island;
			}
		}
	}
	return nr_island;
}
