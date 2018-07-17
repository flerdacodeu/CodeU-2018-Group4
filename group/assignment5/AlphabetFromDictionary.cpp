#include "AlphabetFromDictionary.hpp"

void AlphabetFromDictionary::setDictionary(vector<string> dictionary) {
    this->dictionary = dictionary;
}

void AlphabetFromDictionary::initializeClassVars() {
    vector<char> alphabetCharacters = findAlphabetCharacters();
    this->charPriorityGraph.clear();
    this->numOfPriorCharacters.clear();
    for (auto c : alphabetCharacters) {
        this->charPriorityGraph[c] = set<char>();
        this->numOfPriorCharacters[c] = 0;
    }
}

bool AlphabetFromDictionary::findAlphabet(vector<char> &alphabet) {
    this->initializeClassVars();
    this->createCharPriorityGraph();

    // find topological sort of characters graph to find alphabet
    return topologicalSort(alphabet);
}

void AlphabetFromDictionary::updateNumOfPriorCharacters(const char origin) {
    const set<char> followingChars = this->charPriorityGraph.at(origin);
    for (char c : followingChars) {
        this->numOfPriorCharacters[c]--;
    }
    this->numOfPriorCharacters.erase(origin);
}

bool AlphabetFromDictionary::findNextOrigin(char &origin) {
    for (auto it : this->numOfPriorCharacters) {
        if (it.second == 0) {
            origin = it.first;
            return true;
        }
    }
    // no origin -> circle in graph -> dictionary is inconsistent
    return false;
}

bool AlphabetFromDictionary::topologicalSort(vector<char> &alphabet) {
    alphabet.clear();
    char nextChar;
    while (this->numOfPriorCharacters.size() > 0) {
        if (!this->findNextOrigin(nextChar)) {
            alphabet.clear();
            return false;
        }
        alphabet.push_back(nextChar);
        this->updateNumOfPriorCharacters(nextChar);
    }
    return true;
}

void AlphabetFromDictionary::createCharPriorityGraph() {
    if (this->dictionary.empty()) return;
    int mismatchIndex;
    for (int i = 0; i < this->dictionary.size()-1; i++)
    {
        mismatchIndex = findFirstMismatchIndex(this->dictionary[i], this->dictionary[i+1]);
        if (mismatchIndex != -1) {
            char priorChar = this->dictionary[i][mismatchIndex], followingChar = this->dictionary[i + 1][mismatchIndex];
            this->charPriorityGraph[priorChar].insert(followingChar);
            this->numOfPriorCharacters[followingChar]++;
        }
    }
}

int AlphabetFromDictionary::findFirstMismatchIndex(string str1, string str2) {
    if (str1.size() == 0 || str2.size() == 0) {
        return -1;
    }
    int index = 0;
    while (index < str1.size() && index < str2.size() && str1[index] == str2[index])
        index++;
    return (index < str1.size() && index < str2.size()) ? index : -1;
}

vector<char> AlphabetFromDictionary::findAlphabetCharacters() {
    vector<bool> charsInDict((unsigned int) pow(2, CHAR_BIT), false);
    vector<char> alphabetChars;
    for (auto word : this->dictionary) {
        for (char c : word) {
            if (!charsInDict[c]) {
                charsInDict[c] = true;
                alphabetChars.push_back(c);
            }
        }
    }
    return alphabetChars;
}
