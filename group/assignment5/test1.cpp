#include <iostream>
#include <string>
#include "WordDependencyGraph.h"
#include "test_library.h"

using namespace std;


int main() {
	vector<string> dictionary = { "ART", "RAT", "CAT", "CAR", "D#Žd2" };
	WordDependencyGraph wordDependencyGraph(dictionary);
	
	vector<char> result = wordDependencyGraph.topologicalSort();
	string str(result.begin(), result.end());
	
	EXPECT_EQ("ŽTd#2ARCD", str);			// TODO: this is one of possible solutions

	
	system("PAUSE");
	return 0;
}
