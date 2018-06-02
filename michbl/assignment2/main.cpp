#include <iostream>
#include "BinaryTree.hpp"


using namespace std;

int main() {
    BinaryTree<int> tree;
    tree.insertRoot(7);
    tree.insertKey(3, 7, LEFT);
    tree.insertKey(4, 7, RIGHT);
    tree.insertKey(2, 3, LEFT);
    tree.insertKey(5, 3, RIGHT);
    tree.insertKey(8, 4, RIGHT);
    tree.insertKey(1, 2, LEFT);
    tree.insertKey(6, 2, RIGHT);


    tree.printTree();
    cout << endl << endl;

    cout << "6's ancestors: ";
    tree.printAncestors(6);
    cout << endl;
    cout << "1's ancestors: ";
    tree.printAncestors(1);
    cout << endl;
    cout << "2's ancestors: ";
    tree.printAncestors(2);
    cout << endl;
    cout << "3's ancestors: ";
    tree.printAncestors(3);
    cout << endl;
    cout << "4's ancestors: ";
    tree.printAncestors(4);
    cout << endl;
    cout << "5's ancestors: ";
    tree.printAncestors(5);
    cout << endl;
    cout << "7's ancestors: ";
    tree.printAncestors(7);
    cout << endl;
    cout << "8's ancestors: ";
    tree.printAncestors(8);
    cout << endl << endl;

    int keys[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << keys[i] << ", " << keys[j] << " lowest common ancestor: ";
            tree.printLowestCommonAncestor(keys[i], keys[j]);
            cout << endl;
        }
    }
    return 0;
}