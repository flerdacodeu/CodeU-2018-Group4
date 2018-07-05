#include<vector>
#include <assert.h>
using namespace std;

class FindIslands{

public:
	int nr_row;
	int nr_column;
	vector<vector<bool> > isLandTile;
	vector<pair<int, int> > moves;
 
	FindIslands();
	FindIslands(vector<vector<bool> >& isLandTile);
	bool isInBounds(int i, int j);
	void visitOneIsland(vector<vector<bool> >& visited, int i, int j);
	int findNumberOfIslands();
};
