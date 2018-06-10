#include <iostream>
#include <algorithm>

class node {
	int key;
	node *left_node, *right_node, *parent_node;
public:
	node(int x, node* l = nullptr, node* r = nullptr) : key(x), left_node(l), right_node(r), parent_node(nullptr) {
		if (left_node != nullptr) {
			left_node->parent_node = this;
		}
		if (right_node != nullptr) {
			right_node->parent_node = this;
		}
	}

	~node() {
		delete left_node;
		delete right_node;
	}

	int get_value() {
		return key;
	}

	node* get_left() {
		return left_node;
	}

	node* get_right() {
		return right_node;
	}

	node* get_parent() {
		return parent_node;
	}
};

node* find_node(int key, node* v) {
	if (v == nullptr) {
		return nullptr;
	}
	if (key == v->get_value()) {
		return v;
	}
	node* u = find_node(key, v->get_left());
	if (u != nullptr) {
		return u;
	}
	u = find_node(key, v->get_right());
	return u;
}

void print_path_to_root(node* v) {
	if (v == nullptr) {
		return;
	}
	while (v->get_parent() != nullptr) {
		v = v->get_parent();
		std::cout << v->get_value() << ' ';
	}
	std::cout << "\n";
}

void print_path_to_root_for_key(int key, node* root) {
	node* v = find_node(key, root);
	if (v == nullptr) {
		std::cout << "Couldn't find key\n";
		return;
	}
	print_path_to_root(v);
}

int count_high(node* v) {
	int ans = -1;
	while (v != nullptr) {
		ans++;
		v = v->get_parent();
	}
	return ans;
}

int find_lowest_common_ancestor(int key_1, int key_2, node* root) {
	node* u = find_node(key_1, root);
	node* v = find_node(key_2, root);
	if (u == nullptr || v == nullptr) {
		return -1;
	}
	int u_h = count_high(u);
	int v_h = count_high(v);
	if (u_h < v_h) {
		std::swap(u_h, v_h);
		std::swap(u, v);
	}
	while (u_h > v_h) {
		u_h--;
		u = u->get_parent();
	}
	while (u != v) {
		u = u->get_parent();
		v = v->get_parent();
	}
	return u->get_value();
}