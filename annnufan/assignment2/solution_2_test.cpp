#include "node.cpp"
#include <cassert>

int main() {
	node root(7, new node(3, new node(2, new node(1), new node(6)), new node(5)), new node(4, nullptr, new node(8)));
	assert(find_lowest_common_ancestor(7, 8, &root) == 7);
	assert(find_lowest_common_ancestor(10, 9, nullptr) == -1);
	assert(find_lowest_common_ancestor(6, 9, &root) == -1);
	assert(find_lowest_common_ancestor(1, 6, &root) == 2);
	assert(find_lowest_common_ancestor(8, 6, &root) == 7);
	return 0;
}