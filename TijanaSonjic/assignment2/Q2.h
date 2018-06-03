#pragma once
#include <iostream>
using namespace std;

class Node {
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

bool isInTheTree(Node* root, Node* node) {
	if (!root)
		return false;

	if (root == node)
		return true;

	return isInTheTree(root->getLeftChild(), node) || isInTheTree(root->getRightChild(), node);
}

Node* findFirstCommonAncestor(Node* root, Node* node1, Node* node2) {
	if (!root)
		return nullptr;

	if (isInTheTree(root->getLeftChild(), node1) && isInTheTree(root->getLeftChild(), node2))
		return findFirstCommonAncestor(root->getLeftChild(), node1, node2);

	if (isInTheTree(root->getRightChild(), node1) && isInTheTree(root->getRightChild(), node2))
		return findFirstCommonAncestor(root->getRightChild(), node1, node2);

	return root;
}

Node* firstCommonAncestor(Node* root, Node* node1, Node* node2) {
	if (!root || !node1 || !node2)
		return nullptr;

	if (!isInTheTree(root, node1) || !isInTheTree(root, node2))
		return nullptr;

	return findFirstCommonAncestor(root, node1, node2);
}
