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

    vector<int> ancestors;
    
    cout << "6's ancestors: ";
    ancestors = tree.findAncestors(6);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl;
    cout << "1's ancestors: ";
    ancestors = tree.findAncestors(1);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl;
    cout << "2's ancestors: ";
    ancestors = tree.findAncestors(2);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl;
    cout << "3's ancestors: ";
    ancestors = tree.findAncestors(3);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl;
    cout << "4's ancestors: ";
    ancestors = tree.findAncestors(4);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl;
    cout << "5's ancestors: ";
    ancestors = tree.findAncestors(5);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl;
    cout << "7's ancestors: ";
    ancestors = tree.findAncestors(7);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl;
    cout << "8's ancestors: ";
    ancestors = tree.findAncestors(8);
    for (auto a : ancestors) {
        cout << a << ", ";
    }
    cout << endl << endl;

    int keys[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << keys[i] << ", " << keys[j] << " lowest common ancestor: ";
            cout << tree.findLowestCommonAncestor(keys[i], keys[j], 0);
            cout << endl;
        }
    }
    return 0;
}
