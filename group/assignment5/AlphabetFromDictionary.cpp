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
    this->inDegree = vector<int>(NUM_OF_NATIVE_CHARS, 0);
}

void AlphabetFromDictionary::findAlphabetCharacters() {
    this->alphabetCharacters.clear();
    vector<bool> isCharInDictionary(NUM_OF_NATIVE_CHARS, false);
    for (string &word : this->dictionary) {
        for (char c : word) {
            if (!isCharInDictionary[c]) {
                isCharInDictionary[c] = true;
                this->alphabetCharacters.push_back(c);
            }
        }
    }
}

int AlphabetFromDictionary::findFirstMismatchIndex(const string &str1, const string &str2) {
    int index = 0;
    while (index < str1.size() && index < str2.size() && str1[index] == str2[index]) {
        index++;
    }
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
            if (!this->charPriorityGraph[priorChar][followingChar]) {
                this->inDegree[followingChar]++;
            }
            this->charPriorityGraph[priorChar][followingChar] = true;
        }
        lastNonEmptyWord = word;
    }
}

// challenge 2
void AlphabetFromDictionary::findCyclesInGraphUtil(char priorChar, vector<bool> &visited) {
    visited[priorChar] = true;
    vector<bool> isCharAdjacent = this->charPriorityGraph[priorChar];
    for (char c = 0; c < isCharAdjacent.size(); c++) {
        if (isCharAdjacent[c]) {
            if (visited[c]) { // found cycle
                this->isGraphCyclic = true;
                return;
            } else {
                this->findCyclesInGraphUtil(c, visited);
            }
        }
    }
    visited[priorChar] = false;
}

// challenge 2
void AlphabetFromDictionary::findCyclesInGraph() {
    vector<bool> visited(NUM_OF_NATIVE_CHARS, false);
    for (auto it : this->charPriorityGraph) {
        this->findCyclesInGraphUtil(it.first, visited);
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
    this->findCyclesInGraph();
    if (!this->isGraphCyclic) {
        // find topological sort of characters graph to find ordered alphabet
        this->topologicalSort();
    }
}

// challenge 3
vector<string> AlphabetFromDictionary::makeDictionaryConsistent() {
    vector<string> subsetOfWords;
    vector<string> copyOfOriginalDictionary = this->dictionary;

    // Run counter i from 111..1 to 000..0
    for (int i = (int) pow(2, copyOfOriginalDictionary.size()) - 1; i >= 0; i--) {
        // consider each element in the set
        for (int j = 0; j < copyOfOriginalDictionary.size(); j++) {
            // If j-th bit is 1 then add j-th word from dictionary to the subsetOfWords of words
            if ((i & (1 << j)) != 0)
                subsetOfWords.push_back(copyOfOriginalDictionary[j]);
        }

        this->setDictionary(subsetOfWords);
        if (this->isDictionaryConsistent())
            return this->dictionary;

        subsetOfWords.clear();
    }

    return this->dictionary;
}

// part of challenge 1
void AlphabetFromDictionary::allTopologicalSortUtil(set<vector<char> > &allAlphabets,
                                                    vector<char> &alphabet,
                                                    vector<bool> &visited) {
    bool notEndOfAlphabet = false;

    for (char alphabetChar : this->alphabetCharacters) {
        if (this->inDegree[alphabetChar] == 0 && !visited[alphabetChar]) {
            vector<bool> isCharAdjacent = this->charPriorityGraph[alphabetChar];
            for (char c = 0; c < isCharAdjacent.size(); c++) {
                if (isCharAdjacent[c])
                    this->inDegree[c]--;
            }

            alphabet.push_back(alphabetChar);
            visited[alphabetChar] = true;
            this->allTopologicalSortUtil(allAlphabets, alphabet, visited);

            visited[alphabetChar] = false;
            alphabet.erase(alphabet.end() - 1);
            for (char c = 0; c < isCharAdjacent.size(); c++) {
                if (isCharAdjacent[c])
                    this->inDegree[c]++;
            }

            notEndOfAlphabet = true;
        }
    }
    if (!notEndOfAlphabet)
        allAlphabets.insert(alphabet);
}

// challenge 1
set<vector<char> > AlphabetFromDictionary::findAllAlphabets() {
    set<vector<char>> allAlphabets;
    if (this->dictionary.empty()) return allAlphabets;

    vector<bool> visited(NUM_OF_NATIVE_CHARS, false);
    vector<char> alphabet;

    allTopologicalSortUtil(allAlphabets, alphabet, visited);
    return allAlphabets;
}