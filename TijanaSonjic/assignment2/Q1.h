#pragma once
#include <iostream>
using namespace std;

class Node{
private:
	Node* leftChild;
	Node* rightChild;
	int info;
public:
	Node(int info, Node* leftChild = nullptr, Node* rightChild = nullptr) {
		this->info = info;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
	}
	
	void distroy() {
		if (leftChild) {
			leftChild->distroy();
			leftChild = nullptr;
		}
		if (rightChild) {
			rightChild->distroy();
			rightChild = nullptr;
		}		
	}

	~Node() {
		distroy();
	}
	
	Node* insertLeftChild(Node* node) {
		this->leftChild = node;

		return this;
	}

	Node* insertRightChild(Node* node) {
		this->rightChild = node;

		return this;
	}

	int getInfo() {
		return info;
	}

	Node* getLeftChild() {
		return leftChild;
	}

	Node* getRightChild() {
		return rightChild;
	}
};

// Function will return false if key is not in the tree.
//
bool printAncestors(Node* root, int key) {
	if (!root)
		return false;

	if (root->getInfo() == key)
		return true;

	if (printAncestors(root->getLeftChild(), key) || printAncestors(root->getRightChild(), key)) {
		cout << root->getInfo() << " ";
		return true;
	}

	return false;
}


