#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<array> 
#include<queue>
#include"Node.h"

using namespace std;

template<typename T>
Node<T>* search(Node<T>* head, T key)
{
	// Check if the tree is empty
	if (head == NULL)	return NULL;

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
void print_ancestors(Node<T>* head, T key){
	Node<int>* node = search(head, key);
	if (head == NULL) cout << "This tree is empty";
	else if (node == head) cout << "This node is the root";
	else if (node != NULL){
		// Print the ancestors
		while (node->parent != NULL){
			cout << node->parent->key << " ";
			node = node->parent;
		}
	}
	else cout << "Could not find a node with this key " << key;
	cout << endl;
}

int main(){

	// Node itself is condisered to be its ancestor
	Node<int>* tree = new Node<int>(7);
	tree->left = new Node<int>(3, tree);
	tree->right = new Node<int>(4, tree);
	tree->left->left = new Node<int>(2, tree->left);
	tree->left->right = new Node<int>(5, tree->left);
	tree->right->right = new Node<int>(8, tree->right);
	tree->left->left->left = new Node<int>(1, tree->left->left);
	tree->left->left->right = new Node<int>(6, tree->left->left);

	int key;
	cout << "Input the key to print its ancestors" << endl;
	cin >> key;
	print_ancestors(tree, key);

	return 0;
}
