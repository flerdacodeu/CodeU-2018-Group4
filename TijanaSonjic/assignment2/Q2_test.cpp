#include "Node.h"
#include "Q2.h"


//
//			   7
//			 /   \
//			3      4
//		      /	  \	\
//		     2	   5	 8
//		    / \
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
	Node* notInTheTree = new Node(100);

	node2->setLeftChild(node1)->setRightChild(node6);
	node3->setLeftChild(node2)->setRightChild(node5);
	node4->setRightChild(node8);
	root->setLeftChild(node3)->setRightChild(node4);

	// Both nodes are in the tree
	Node* commonNode = firstCommonAncestor(root, node6, node8);
	if (commonNode)
		cout << "First common ancestor is node " << commonNode->getInfo() << " ." << endl;
	else
		cout << "These nodes don't have common ancestor." << endl;

	// One node is nullptr
	commonNode = firstCommonAncestor(root, nullRoot, node8);
	if (commonNode)
		cout << "First common ancestor is node " << commonNode->getInfo() << " ." << endl;
	else
		cout << "These nodes don't have common ancestor." << endl;

	// Root node is nullptr
	commonNode = firstCommonAncestor(nullRoot, node1, node8);
	if (commonNode)
		cout << "First common ancestor is node " << commonNode->getInfo() << " ." << endl;
	else
		cout << "These nodes don't have common ancestor." << endl;

	// One node is not in the tree
	commonNode = firstCommonAncestor(root, notInTheTree, node8);
	if (commonNode)
		cout << "First common ancestor is node " << commonNode->getInfo() << " ." << endl;
	else
		cout << "These nodes don't have common ancestor." << endl;

	delete root;

	system("PAUSE");
	return 0;
}
