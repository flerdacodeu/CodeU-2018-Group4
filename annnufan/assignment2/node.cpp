#include <iostream>
#include <algorithm>


class node {
	int key;
public:
	node(int x, node* l = nullptr, node* r = nullptr) : key(x), left_node(l), right_node(r){}
	~node() {
		delete left_node;
		delete right_node;
	}

	void set_value(int x) {
		key = x;
	}

	int get_value() {
		return key;
	}

	node* left_node, *right_node, *parent_node;
};

bool find_key_and_print_way_to_root(int x, node* v) {
	if (v == nullptr) {
		return false;
	}
	if (x == v->get_value()) {
		return true;
	}
	if (find_key_and_print_way_to_root(x, v->left_node) || find_key_and_print_way_to_root(x, v->right_node)) {
		std::cout << v->get_value() << ' ';
		return true;
	}
	return false;
}

void print_way_to_root_for_key(int x, node* v) {
	if (find_key_and_print_way_to_root(x, v)) {
		std::cout << "\n";
	} else {
		std::cout << "Couldn't find key\n";
	}
}

node* find_node(int x, node* v, node* p) {
	if (v == nullptr) {
		return nullptr;
	}
	v->parent_node = p;
	if (x == v->get_value()) {
		return v;
	}
	node* u = find_node(x, v->left_node, v);
	if (u != nullptr) {
		return u;
	}
	u = find_node(x, v->right_node, v);
	return u;
}

int count_high(node* v) {
	if (v == nullptr) {
		return -1;
	}
	int ans = 0;
	while (v->parent_node != nullptr) {
		ans++;
		v = v->parent_node;
	}
	return ans;
}

int find_lca(int x, int y, node* root) {
	node* u = find_node(x, root, nullptr);
	node* v = find_node(y, root, nullptr);
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
		u = u->parent_node;
	}
	while (u != v) {
		u = u->parent_node;
		v = v->parent_node;
	}
	return u->get_value();
}