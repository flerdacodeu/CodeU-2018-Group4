#pragma once
#include <iostream>
using namespace std;

class Node{
private:
	Node* leftChild;
	Node* rightChild;
	int data;

	void distroy() {
		if (leftChild) {
			delete leftChild;
			leftChild = nullptr;
		}
		if (rightChild) {
			delete rightChild;
			rightChild = nullptr;
		}
	}

public:
	Node(int info, Node* leftChild = nullptr, Node* rightChild = nullptr) {
		this->data = info;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
	}
	
	~Node() {
		distroy();
	}
	
	Node* setLeftChild(Node* node) {
		this->leftChild = node;

		return this;
	}

	Node* setRightChild(Node* node) {
		this->rightChild = node;

		return this;
	}

	int getInfo() {
		return data;
	}

	Node* getLeftChild() {
		return leftChild;
	}

	Node* getRightChild() {
		return rightChild;
	}
};



