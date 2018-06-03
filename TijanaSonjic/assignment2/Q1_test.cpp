#include "Node.h"


//
//				   7
//				 /   \
//				3	  4
//			  /	  \	   \
//			 2	   5	8
//			/ \
//		   1   6
//
int main() {
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);
	Node* node6 = new Node(6);
	Node* root = new Node(7);
	Node* node8 = new Node(8);
	Node* nullRoot = nullptr;

	node2->insertLeftChild(node1)->insertRightChild(node6);
	node3->insertLeftChild(node2)->insertRightChild(node5);
	node4->insertRightChild(node8);
	root->insertLeftChild(node3)->insertRightChild(node4);

	cout << "Ancestors of node with key value 6: ";
	if (!printAncestors(root, 6)) {
		cout << "Key is not in the tree." << endl;
	}
	cout << endl;

	cout << "Ancestors of node with key value 8: ";
	if (!printAncestors(root, 8)) {
		cout << "Key is not in the tree." << endl;
	}
	cout << endl;

	cout << "Ancestors of node with key value 7: ";
	if (!printAncestors(root, 7)) {
		cout << "Key is not in the tree." << endl;
	}
	cout << endl;

	cout << "Ancestors of node with key value 11: ";
	if (!printAncestors(root,11)) {
		cout << "Key is not in the tree." << endl;
	}
	cout << endl;

	cout << "Ancestors of node with key value 55: ";
	if (!printAncestors(nullRoot, 11)) {
		cout << "Key is not in the tree." << endl;
	}
	cout << endl;

	system("PAUSE");
	return 0;
}
