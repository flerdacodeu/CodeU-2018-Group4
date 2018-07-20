#include "AlphabetFromDictionary.hpp"

AlphabetFromDictionary::AlphabetFromDictionary(const vector<string> &dictionary) : dictionary(dictionary) {
    this->setDictionary(dictionary);
}

void AlphabetFromDictionary::setDictionary(const vector<string> &dictionary) {
    this->dictionary = dictionary;
    this->initializeClassVars();
    this->findAlphabet();
}

vector<char> AlphabetFromDictionary::getAlphabet() {
    return this->orderedAlphabet;
}

bool AlphabetFromDictionary::isDictionaryConsistent() {
    return !this->isGraphCyclic;
}

void AlphabetFromDictionary::initializeClassVars() {
    this->findAlphabetCharacters();
    this->isGraphCyclic = false;
    this->orderedAlphabet.clear();
    this->charPriorityGraph.clear();
    for (auto c : this->alphabetCharacters) {
        this->charPriorityGraph[c] = vector<bool>(NUM_OF_NATIVE_CHARS, false);
    }
}

void AlphabetFromDictionary::findAlphabetCharacters() {
    this->alphabetCharacters.clear();
    vector<bool> isCharInDictionary(NUM_OF_NATIVE_CHARS, false);
    for (auto word : this->dictionary) {
        for (char c : word) {
            if (!isCharInDictionary[c]) {
                isCharInDictionary[c] = true;
                this->alphabetCharacters.push_back(c);
            }
        }
    }
}

int AlphabetFromDictionary::findFirstMismatchIndex(string str1, string str2) {
    int index = 0;
    while (index < str1.size() && index < str2.size() && str1[index] == str2[index])
        index++;
    return (index < str1.size() && index < str2.size()) ? index : -1;
}

void AlphabetFromDictionary::createCharPriorityGraph() {
    int mismatchIndex;
    string lastNonEmptyWord;

    // find first non-empty word in dictionary
    for (string &word : this->dictionary) {
        if (!word.empty()) {
            lastNonEmptyWord = word;
            break;
        }
    }

    for (string &word : this->dictionary) {
        if (word.empty()) {
            continue;
        }
        mismatchIndex = findFirstMismatchIndex(lastNonEmptyWord, word);
        if (mismatchIndex != -1) {
            char priorChar = lastNonEmptyWord[mismatchIndex], followingChar = word[mismatchIndex];
            if (charPriorityGraph[followingChar][priorChar]) { // cycle in graph
                this->isGraphCyclic = true;
                this->orderedAlphabet = this->alphabetCharacters;
                return;
            }
            this->charPriorityGraph[priorChar][followingChar] = true;
        }
        lastNonEmptyWord = word;
    }
}

void AlphabetFromDictionary::topologicalSortUtil(char priorChar, vector<bool> &visited, stack<char> &stack) {
    visited[priorChar] = true;
    vector<bool> isCharAdjacent = this->charPriorityGraph[priorChar];

    for (char c = 0; c < isCharAdjacent.size(); c++) {
        if (isCharAdjacent[c] && !visited[c]) {
            topologicalSortUtil(c, visited, stack);
        }
    }

    stack.push(priorChar);
}

void AlphabetFromDictionary::topologicalSort() {
    stack<char> stack;
    vector<bool> visited(NUM_OF_NATIVE_CHARS, false);

    for (auto it : this->charPriorityGraph) {
        if (!visited[it.first]) {
            this->topologicalSortUtil(it.first, visited, stack);
        }
    }

    while (!stack.empty()) {
        this->orderedAlphabet.push_back(stack.top());
        stack.pop();
    }
}

void AlphabetFromDictionary::findAlphabet() {
    if (dictionary.empty()) {
        return;
    }

    this->createCharPriorityGraph();
    if (!this->isGraphCyclic) {
        // find topological sort of characters graph to find ordered alphabet
        this->topologicalSort();
    }
}
