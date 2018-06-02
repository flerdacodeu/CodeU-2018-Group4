#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
using namespace std;

enum Side {LEFT, RIGHT};

// Assuming T is comparable, copyable and printable
// Assuming keys are unique

template <typename T>
struct Node {
    T key;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node(T key) {
        this->key = key;
    }
};

template <typename T>
class BinaryTree {
private:
    Node<T> *root;

    Node<T> *copyTree(const Node<T> *toCopy) {
        if (toCopy == nullptr) {
            return nullptr;
        }

        Node<T> *newNode = new Node<T>(toCopy->key);

        newNode->left = copyTree(toCopy->left);
        newNode->right = copyTree(toCopy->right);

        return newNode;
    }

    // insert a new node, return true on success, false on failure
    bool insert(Node<T> *node, const T &key, const  T &parentKey, const Side side) {
        if (node == nullptr) {
            return false;
        }
        if (node->key == parentKey) {
            if (side == LEFT && node->left == nullptr) {
                Node<T> *child = new Node<T>(key);
                node->left = child;
                return true;
            }
            else if (side == RIGHT && node->right == nullptr) {
                Node<T> *child = new Node<T>(key);
                node->right = child;
                return true;
            }
            else { // place is already taken
                return false;
            }
        }
        if (insert(node->left, key, parentKey, side)) {
            return true;
        }
        return insert(node->right, key, parentKey, side);
    }

    void destroyTree(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    // prints tree in post-order
    void printTree(const Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        printTree(node->left);
        printTree(node->right);
        cout << node->key << " ";
    }

    bool printAncestors(const Node<T> *node, const T &key) {
        if (node == nullptr) {
            return false;
        }
        if (node->key == key) {
            return true;
        }

        if (printAncestors(node->left, key) || printAncestors(node->right, key)) {
            if (node == this->root) {
                cout << node->key;
            }
            else {
                cout << node->key << ", ";
            }
        }
    }

    bool isAncestor(const Node<T> *node, const T &key1, const T &key2) {
        bool found1 = keyIsInSubtree(node->left, key1) || keyIsInSubtree(node->right, key1);
        bool found2 = keyIsInSubtree(node->left, key2) || keyIsInSubtree(node->right, key2);
        return  found1 && found2;
    }

    bool keyIsInSubtree(const Node<T> *node, T key) {
        if (node == nullptr) {
            return false;
        }
        if (node->key == key) {
            return true;
        }
        return keyIsInSubtree(node->left, key) || keyIsInSubtree(node->right, key);
    }

    // The return value denotes weather the LCA was already found or not
    bool printLowestCommonAncestor(const Node<T> *node, const T &key1, const T &key2) {
        if (node == nullptr) {
            return false;
        }
        bool foundInLeft = printLowestCommonAncestor(node->left, key1, key2);
        bool foundInRight = printLowestCommonAncestor(node->right, key1, key2);
        if (!foundInLeft && !foundInRight) {
            if (isAncestor(node, key1, key2)) {
                cout << node->key;
                return true;
            }
            else {
                return false;
            }
        }
        return (foundInLeft || foundInRight);
    }


public:
    BinaryTree() {
        this->root = nullptr;
    }
    BinaryTree(const BinaryTree &tree) {
        if (root == nullptr) {
            this->root = nullptr;
            return;
        }

        this->root = copyTree(tree.root);
    }
    ~BinaryTree() {
        destroyTree(this->root);
    }

    bool insertRoot(const T &key) {
        if (this->root == nullptr) {
            this->root = new Node<T>(key);
            return true;
        }
        return false;
    }

    bool insertKey(const T &key, const T &parentKey, const Side side) {
        return insert(this->root, key, parentKey, side);
    }

    void printTree() {
        printTree(this->root);
    }

    void printAncestors(const T &key) {
        printAncestors(this->root, key);
    }

    void printLowestCommonAncestor(const T &key1, const T &key2) {
        printLowestCommonAncestor(this->root, key1, key2);
    }
};

#endif //BINARYTREE_HPP
