#pragma once
#include "Node.h"


bool isInTheTree(Node* root, Node* node) {
	if (!root)
		return false;

	if (root == node)
		return true;

	return isInTheTree(root->getLeftChild(), node) || isInTheTree(root->getRightChild(), node);
}

// This is a helper function, do not call directly. Call firstCommonAncestor instead.
// Function assumes that both nodes are in the tree.
//
Node* findFirstCommonAncestorAux(Node* root, Node* node1, Node* node2) {
	if (!root)
		return nullptr;

	if (isInTheTree(root->getLeftChild(), node1) && isInTheTree(root->getLeftChild(), node2))
		return findFirstCommonAncestorAux(root->getLeftChild(), node1, node2);

	if (isInTheTree(root->getRightChild(), node1) && isInTheTree(root->getRightChild(), node2))
		return findFirstCommonAncestorAux(root->getRightChild(), node1, node2);

	return root;
}

Node* firstCommonAncestor(Node* root, Node* node1, Node* node2) {
	if (!root || !node1 || !node2)
		return nullptr;

	if (!isInTheTree(root, node1) || !isInTheTree(root, node2))
		return nullptr;

	return findFirstCommonAncestorAux(root, node1, node2);
}
