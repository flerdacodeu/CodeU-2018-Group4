#ifndef ALPHABETFROMDICTIONARY_HPP
#define ALPHABETFROMDICTIONARY_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <set>
#include <stack>

#define NUM_OF_NATIVE_CHARS pow(2, CHAR_BIT)

using namespace std;

class AlphabetFromDictionary {
private:
    vector<string> dictionary;
    unordered_map<char, vector<bool>> charPriorityGraph;
    vector<char> orderedAlphabet;
    vector<char> alphabetCharacters;
    bool isGraphCyclic;

public:
    explicit AlphabetFromDictionary(const vector<string> &dictionary);;
    ~AlphabetFromDictionary() = default;
    void setDictionary(const vector<string> &dictionary);
    vector<char> getAlphabet();
    bool isDictionaryConsistent();

private:
    void initializeClassVars();
    void findAlphabetCharacters();
    int findFirstMismatchIndex(string str1, string str2);
    void createCharPriorityGraph();
    void topologicalSortUtil(char letter, vector<bool> &visited, stack<char> &stack);
    void topologicalSort();
    void findAlphabet();
};


#endif //ALPHABETFROMDICTIONARY_HPP
