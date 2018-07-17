#ifndef ALPHABETFROMDICTIONARY_HPP
#define ALPHABETFROMDICTIONARY_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class AlphabetFromDictionary {
private:
    vector<string> dictionary;
    unordered_map<char, set<char>> charPriorityGraph;
    unordered_map<char, int> numOfPriorCharacters;

public:
    AlphabetFromDictionary(vector<string> dictionary) : dictionary(dictionary) {};
    ~AlphabetFromDictionary() = default;
    bool findAlphabet(vector<char> &alphabet);
    void setDictionary(vector<string> dictionary);

private:
    void initializeClassVars();
    void updateNumOfPriorCharacters(const char origin);
    bool findNextOrigin(char &origin);
    bool topologicalSort(vector<char> &alphabet);
    void createCharPriorityGraph();
    static int findFirstMismatchIndex(string str1, string str2);
    vector<char> findAlphabetCharacters();
};


#endif //ALPHABETFROMDICTIONARY_HPP
