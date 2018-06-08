#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <vector>

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

    bool findAncestors(const Node<T> *node, const T &key, vector<T> &ancestors) {
        if (node == nullptr) {
            return false;
        }
        if (node->key == key) {
            return true;
        }
        if (findAncestors(node->left, key, ancestors) || findAncestors(node->right, key, ancestors)) {
            ancestors.push_back(node->key);
        }
    }

    bool isAncestor(const Node<T> *node, const T &key) {
        return  keyIsInSubtree(node->left, key) || keyIsInSubtree(node->right, key);
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
    bool findLowestCommonAncestor(const Node<T> *node, const T &key1, const T &key2, T &lca) {
        if (node == nullptr) {
            return false;
        }
        bool foundInLeft = findLowestCommonAncestor(node->left, key1, key2, lca);
        bool foundInRight = findLowestCommonAncestor(node->right, key1, key2, lca);
        if (foundInLeft || foundInRight) { // node is a common ancestor, but not the lowest one
            return true;
        }
        if (isAncestor(node, key1) && isAncestor(node, key2)) { // node is the lowest common ancestor
            lca = node->key;
            return true;
        }
        else { // node is not a common ancestor
            return false;
        }
    }


public:
    BinaryTree() {
        this->root = nullptr;
    }
    BinaryTree(const BinaryTree &tree) {
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

    vector<T> findAncestors(const T &key) {
        vector<T> ancestors;
        findAncestors(this->root, key, ancestors);
        return ancestors;
    }

    T findLowestCommonAncestor(const T &key1, const T &key2, const T defaultValue) {
        T lca = defaultValue; // if no lca is found (one of keys is root) return defaultValue
        findLowestCommonAncestor(this->root, key1, key2, lca);
        return lca;
    }
};

#endif //BINARYTREE_HPP
