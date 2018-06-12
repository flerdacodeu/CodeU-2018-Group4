#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include "Grid.hpp"

#define END_OF_WORD -1

using namespace std;

// implementing dictionary as trie
class Dictionary {
private:
    struct Node {
        char c;
        unordered_map<char, Node *> children;

        Node(char c) : c(c) {
            this->children.clear();
        }
    };

    Node *root;
    vector<Node *> nodes; // for memory release

    void wordSearchBT(Grid &grid, int row, int col, set<string> &res, string word) {
        char c;
        if (!grid.getChar(row, col, c)) {
            return;
        }
        word += c;
        if (isWord(word)) {
            res.insert(word);
        }
        if (isPrefix(word)) {
            Direction dirs[8] = {LEFT, RIGHT, UP, DOWN, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
            int nextRow, nextCol;
            for (Direction dir : dirs) {
                grid.getNextIdxs(row, col, nextRow, nextCol, dir);
                wordSearchBT(grid, nextRow, nextCol, res, word);
            }
        }
    }

public:
    Dictionary() {
        this->root = new Node(END_OF_WORD);
        nodes.push_back(this->root);
    }

    Dictionary(const vector<string> words) {
        this->root = new Node(END_OF_WORD);
        nodes.push_back(this->root);
        for (string word : words) {
            insertWord(word);
        }
    }

    ~Dictionary() {
        for (auto node : this->nodes) {
            delete node;
        }
    }

    void insertWord(const string &word) {
        unordered_map<char, Node *> *currentChildren = &(this->root->children);
        unordered_map<char, Node *>::iterator it;

        for (char ch : word) {
            it = currentChildren->find(ch);
            if (it != currentChildren->end()) { // current node has a child ch
                currentChildren = &((*it).second->children);
                continue;
            }
            //current node doesn't have a child ch
            Node *newNode = new Node(ch);
            (*currentChildren)[ch] = newNode;

            currentChildren = &(newNode->children);// continue inserting word
            this->nodes.push_back(newNode); // for memory release
        }
        (*currentChildren)[END_OF_WORD] = nullptr;
    }

    bool isPrefix(const string &word, unordered_map<char, Node *> *lastNodeChildren = nullptr) {
        unordered_map<char, Node *> currentChildren = this->root->children;
        unordered_map<char, Node *>::iterator it;

        for (char ch : word) {
            it = currentChildren.find(ch);
            if (it == currentChildren.end()) { // current node doesn't have a child ch
                return false;
            }
            currentChildren = (*it).second->children;
        }
        if (lastNodeChildren != nullptr) {
            *lastNodeChildren = currentChildren;
        }
        return true;
    }

    bool isWord(const string &word) {
        unordered_map<char, Node *> lastNodeChildren;
        lastNodeChildren.clear();
        bool prefix = isPrefix(word, &lastNodeChildren);
        return prefix && lastNodeChildren.find(END_OF_WORD) != lastNodeChildren.end();
    }

    set<string> wordSearch(Grid grid) {
        int h = grid.getHeight();
        int w = grid.getWidth();
        set<string> result;
        result.clear();
        for (int row = 0; row < h; row++) {
            for (int col = 0; col < w; col++) {
                wordSearchBT(grid, row, col, result, "");
            }
        }
        return result;
    }
};


#endif //DICTIONARY_HPP
