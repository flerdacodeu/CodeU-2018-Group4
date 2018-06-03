#include "node.cpp"
#include <cassert>

int main() {
	node* root = new node(7, new node(3, new node(2, new node(1), new node(6)), new node(5)), new node(4, nullptr, new node(8)));
	node* empty_root = nullptr;
	assert(find_lca(7, 8, root) == 7);
	assert(find_lca(10, 9, empty_root) == -1);
	assert(find_lca(6, 9, root) == -1);
	assert(find_lca(1, 6, root) == 2);
	assert(find_lca(8, 6, root) == 7);
	return 0;
}