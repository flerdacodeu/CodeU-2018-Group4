#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<array> 
#include<set>
#include<queue>
#include"Node.h"

using namespace std;

template<typename T>
Node<T>* search(Node<T>* head, T key)
{
	if (head == NULL) return NULL;

	Node<T>* current_node = head;
	queue<Node<T>* > unvisited;
	unvisited.push(current_node);

	while (unvisited.empty() != true)
	{
		current_node = unvisited.front();
		unvisited.pop();
		if (current_node->key == key) return current_node;
		if (current_node->left != NULL) unvisited.push(current_node->left);
		if (current_node->right != NULL) unvisited.push(current_node->right);
	}
	return NULL;
}

template<typename T>
set<Node<T>* > getAllAncestors(Node<T>* node){
	set<Node<T>* > ancestors;
	Node<T>* current_node = node;
	while (current_node != NULL){
		ancestors.insert(current_node);
		current_node = current_node->parent;
	}
	return ancestors;
}

template<typename T>
Node<T>* findLowestCommonAncestor(Node<T>* node1, Node<T>* node2){
	// Node itself is condisered to be its ancestor

	set<Node<T>* > path_to_root = getAllAncestors(node1);
	Node<T>* current_node = node2;
	while (current_node != NULL){
		if (path_to_root.find(current_node) != path_to_root.end())
			return current_node;
		current_node = current_node->parent;
	}
	// Should never happen, all nodes have at least one common ancestor.
	return NULL;
}

int main(){

	// Example tree from assignment
	Node<int>* tree = new Node<int>(7);
	tree->left = new Node<int>(3, tree);
	tree->right = new Node<int>(4, tree);
	tree->left->left = new Node<int>(2, tree->left);
	tree->left->right = new Node<int>(5, tree->left);
	tree->right->right = new Node<int>(8, tree->right);
	tree->left->left->left = new Node<int>(1, tree->left->left);
	tree->left->left->right = new Node<int>(6, tree->left->left);

	cout << "Input two nodes to find their lowest common ancestor" << endl;
	int key1, key2;
	cin >> key1 >> key2;

	Node<int>* node1 = search(tree, key1);
	Node<int>* node2 = search(tree, key2);

	Node<int>* lowestCommonAncestor = findLowestCommonAncestor(node1, node2);
	cout << "Lowest Common Ancestor is " << lowestCommonAncestor->key << endl;

	return 0;
}
