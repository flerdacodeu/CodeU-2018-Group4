#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <vector>
#include <string>
#include <unordered_map>

#define END_OF_WORD -1

using namespace std;

// implementing dictionary as trie
class Dictionary {
private:
    struct Node {
        char c;
        unordered_map<char, Node *> children;

        Node(char c) : c(c) {}
    };

    void insertWord(const string &word) {
        unordered_map<char, Node *> *currentChildren = &this->root->children;

        for (char ch : word) {
            auto it = currentChildren->find(ch);
            if (it != currentChildren->end()) { // current node has a child ch
                currentChildren = &it->second->children;
                continue;
            }
            //current node doesn't have a child ch
            Node *newNode = new Node(ch);
            (*currentChildren)[ch] = newNode;

            currentChildren = &(newNode->children);// continue inserting word
        }
        (*currentChildren)[END_OF_WORD] = nullptr;
    }

    void destroyDict(Node *node) {
        if (node == nullptr) {
            return;
        }
        for (auto it = node->children.begin(); it != node->children.end(); it++) {
            destroyDict(it->second);
        }
        delete node;
    }

    Node *root;

public:
    Dictionary() {
        this->root = new Node(END_OF_WORD);
    }

    Dictionary(const vector<string> words) {
        this->root = new Node(END_OF_WORD);
        for (string word : words) {
            insertWord(word);
        }
    }

    ~Dictionary() {
        destroyDict(this->root);
    }

    bool isPrefix(const string &word, unordered_map<char, Node *> *lastNodeChildren = nullptr) const {
        unordered_map<char, Node *> currentChildren = this->root->children;
        unordered_map<char, Node *>::iterator it;

        for (char ch : word) {
            it = currentChildren.find(ch);
            if (it == currentChildren.end()) { // current node doesn't have a child ch
                return false;
            }
            currentChildren = it->second->children;
        }
        if (lastNodeChildren != nullptr) {
            *lastNodeChildren = currentChildren;
        }
        return true;
    }

    bool isWord(const string &word) const {
        unordered_map<char, Node *> lastNodeChildren;
        bool prefix = isPrefix(word, &lastNodeChildren);
        return prefix && lastNodeChildren.find(END_OF_WORD) != lastNodeChildren.end();
    }
};

#endif //DICTIONARY_HPP
