#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
using namespace std;

// Assuming T is comparable and printable
// Assuming keys are unique

template <typename T>
struct Node {
    T key;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
};

template <typename T>
class BinaryTree {
private:
    Node<T> *root;

    void copyTree(Node<T> *parent, Node<T> *newNode, string side) {
        if (newNode == nullptr) {
            return;
        }

        Node<T> *child = new Node<T>;
        child->key = newNode->key;
        if (side == "left") {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        copyTree(child, newNode->left, "left");
        copyTree(child, newNode->right, "right");
    }

    void insert(Node<T> *node, T key, T parentKey, bool &success) {
        if (node == nullptr) {
            return;
        }
        if (node->key == parentKey) {
            if (node->left == nullptr) {
                Node<T> *child = new Node<T>;
                child->key = key;
                node->left = child;
                success = true;
                return;
            }
            else if (node->right == nullptr) {
                Node<T> *child = new Node<T>;
                child->key = key;
                node->right = child;
                success = true;
                return;
            }
            else { // parent already has 2 children
                return;
            }
        }
        insert(node->left, key, parentKey, success);
        if (success) {
            return;
        }
        insert(node->right, key, parentKey, success);
    }

    void destroyTree(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void printTree(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        printTree(node->left);
        printTree(node->right);
        cout << node->key << " ";
    }

    void printAncestors(Node<T> *node, T key, bool &found) {
        if (node == nullptr) {
            return;
        }
        if (node->key == key) {
            found = true;
            return;
        }
        if (!found) {
            printAncestors(node->left, key, found);
        }
        if (!found) {
            printAncestors(node->right, key, found);
        }
        if (found) {
            if (node == this->root) {
                cout << node->key << endl;
            }
            else {
                cout << node->key << ", ";
            }
        }
    }

    bool bothKeysAreInSubtree(Node<T> *node, T key1, T key2) {
        bool found1 = false, found2 = false;
        bothKeysAreInSubtreeAux(node->left, key1, key2, found1, found2);
        bothKeysAreInSubtreeAux(node->right, key1, key2, found1, found2);
        return found1 && found2;
    }

    void bothKeysAreInSubtreeAux(Node<T> *node, T key1, T key2, bool &found1, bool &found2) {
        if (node == nullptr) {
            return;
        }
        if (node->key == key1) {
            found1 = true;
        }
        if (node->key == key2) {
            found2 = true;
        }
        bothKeysAreInSubtreeAux(node->left, key1, key2, found1, found2);
        bothKeysAreInSubtreeAux(node->right, key1, key2, found1, found2);
    }

    void printLowestCommonAncestor(Node<T> *node, T key1, T key2, bool &found) {
        if (node == nullptr) {
            return;
        }
        if (!found) {
            printLowestCommonAncestor(node->left, key1, key2, found);
        }
        if (!found) {
            printLowestCommonAncestor(node->right, key1, key2, found);
        }
        if (!found && bothKeysAreInSubtree(node, key1, key2)) {
            found = true;
            cout << node->key << endl;
        }
    }


public:
    BinaryTree() {
        this->root = nullptr;
    }
    BinaryTree(Node<T> *root) {
        if (root == nullptr) {
            this->root = nullptr;
            return;
        }
        this->root = new Node<T>;
        this->root->key = root->key;
        copyTree(this->root, root->left, "left");
        copyTree(this->root, root->right, "right");
    }
    ~BinaryTree() {
        destroyTree(this->root);
    }

    bool insertKey(T key, T parentKey) {
        if (this->root == nullptr) {
            this->root = new Node<T>;
            this->root->key = key;
            return true;
        }
        bool success = false;
        insert(this->root, key, parentKey, success);
        return success;
    }

    void printTree() {
        printTree(this->root);
    }

    void printAncestors(T key) {
        bool found = false;
        printAncestors(this->root, key, found);
    }

    void printLowestCommonAncestor(T key1, T key2) {
        bool found = false;
        printLowestCommonAncestor(this->root, key1, key2, found);
    }
};


#endif //BINARYTREE_HPP
