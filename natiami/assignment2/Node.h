#ifndef Node_h
#define Node_h
#pragma once

template<typename T>
struct Node
{
	T key;
	Node *left, *right, *parent;

	Node(T key) {
		this->key = key;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}

	Node(T key, Node* parent) :Node(key) {
		this->key = key;
		this->parent = parent;
	}
	Node(T key, Node* left, Node* right, Node* parent) {
		this->key = key;
		this->left = left;
		this->right = right;
		this->parent = parent;
	}
};

#endif