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
    vector<int> inDegree;

public:
    explicit AlphabetFromDictionary(const vector<string> &dictionary);;
    ~AlphabetFromDictionary() = default;
    void setDictionary(const vector<string> &dictionary);
    vector<char> getAlphabet();
    vector<string> makeDictionaryConsistent();
    bool isDictionaryConsistent();
    set<vector<char>> findAllAlphabets();

private:
    void initializeClassVars();
    void findAlphabetCharacters();
    int findFirstMismatchIndex(const string &str1, const string &str2);
    void createCharPriorityGraph();
    void findCyclesInGraph();
    void findCyclesInGraphUtil(char priorChar, vector<bool> &visited);
    void topologicalSortUtil(char letter, vector<bool> &visited, stack<char> &stack);
    void topologicalSort();
    void findAlphabet();
    void allTopologicalSortUtil(set<vector<char> > &allAlphabets, vector<char> &alphabet, vector<bool> &visited);
};


#endif //ALPHABETFROMDICTIONARY_HPP
