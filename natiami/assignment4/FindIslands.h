#include<vector>
using namespace std;

class FindIslands{

public:
	int nr_row;
	int nr_column;
	vector<vector<bool> > mapOfTiles;
 
	FindIslands();
	FindIslands(int nr_row, int nr_column, vector<vector<bool> >& mapOfTiles);
	bool checkBounds(int i, int j);
	void visitOneIsland(vector<vector<bool> >& visited, int i, int j);
	int findNumberOfIslands();
};