#include "node.cpp"

int main() {
	node root(7, new node(3, new node(2, new node(1), new node(6)), new node(5)), new node(4, nullptr, new node(8)));
	print_path_to_root_for_key(7, &root);
	print_path_to_root_for_key(10, nullptr);
	print_path_to_root_for_key(9, &root);
	print_path_to_root_for_key(1, &root);
	print_path_to_root_for_key(8, &root);
	return 0;
}