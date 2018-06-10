#pragma once
#include "Node.h"


// Function will return true if key is in the tree.
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
