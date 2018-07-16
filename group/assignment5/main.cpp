#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include "codeu_test_lib.h"

using namespace std;

vector<char> findAlphabetCharacters(const vector<string> &dictionary) {
    vector<bool> charsInDict((unsigned int)pow(2, CHAR_BIT), false);
    vector<char> alphabetChars;
    for (auto word : dictionary) {
        for (char c : word) {
            if (!charsInDict[c]) {
                charsInDict[c] = true;
                alphabetChars.push_back(c);
            }
        }
    }
    return alphabetChars;
}

bool createCharPriorityGraph(vector<string> &dictionary, unordered_map<char, vector<bool>> &charPriorityGraph, unordered_map<char, int> &numOfPriorCharacters) {
    while (dictionary.size() > 0 && dictionary[0].size() == 0) {
        dictionary.erase(dictionary.begin());
    }
    if (dictionary.size() < 2) {
        return true;
    }
    char prevChar = dictionary[0][0];
    unordered_map<char, vector<string>> suffixesByCharacters;
    suffixesByCharacters[prevChar] = vector<string>(0);
    for (string word : dictionary) {
        if (word.size() == 0) {
            continue;
        }
        char currentChar = word[0];
        if (currentChar != prevChar) {
            if (suffixesByCharacters.find(currentChar) != suffixesByCharacters.end()) { // found a circle in characters - inconsistent dictionary
                return false;
            }
            // mark prevChar as prior to currentChar and add new suffixes vector for current char
            charPriorityGraph[prevChar][currentChar] = true;
            suffixesByCharacters[currentChar] = vector<string>(0);
            numOfPriorCharacters[currentChar]++;
        }
        word.erase(0, 1);
        suffixesByCharacters[currentChar].push_back(word);
        prevChar = currentChar;
    }
    for (auto it : suffixesByCharacters) {
        vector<string> suffixes = it.second;
        createCharPriorityGraph(suffixes, charPriorityGraph, numOfPriorCharacters);
    }
    return true;
}

bool findNextOrigin(const unordered_map<char, int> &numOfPriorCharacters, char &origin) {
    for (auto it : numOfPriorCharacters) {
        if (it.second == 0) {
            origin = it.first;
            return true;
        }
    }
    // no origin -> circle in graph -> dictionary is inconsistent
    return false;
}

void updateNumOfPriorCharacters(const unordered_map<char, vector<bool>> &charPriorityGraph, unordered_map<char, int> &numOfPriorCharacters, const char origin) {
    const vector<bool> children = charPriorityGraph.at(origin);
    for (char c = 0; c < children.size(); c++) {
        if (children[c]) {
            numOfPriorCharacters[c]--;
        }
    }
    numOfPriorCharacters.erase(origin);
}

bool findAlphabet(vector<string> &dictionary, vector<char> &alphabet) {
    vector<char> alphabetCharacters = findAlphabetCharacters(dictionary);

    unordered_map<char, vector<bool>> charPriorityGraph;
    unordered_map<char, int> numOfPriorCharacters;
    for (auto c : alphabetCharacters) {
        charPriorityGraph[c] = vector<bool>((unsigned int)pow(2, CHAR_BIT), false);
        numOfPriorCharacters[c] = 0;
    }

    if (!createCharPriorityGraph(dictionary, charPriorityGraph, numOfPriorCharacters)) {
        alphabet.clear();
        return false;
    }

    // find topological sort of characters graph to find alphabet
    alphabet.clear();
    char nextChar;
    while(numOfPriorCharacters.size() > 0) {
        if (!findNextOrigin(numOfPriorCharacters, nextChar)) {
            alphabet.clear();
            return false;
        }
        alphabet.push_back(nextChar);
        updateNumOfPriorCharacters(charPriorityGraph, numOfPriorCharacters, nextChar);
    }
    return true;
}

int main() {
    vector<string> dictionary = {"ART", "RAT", "CAT", "CAR"};
    vector<char> alphabet;
    bool result;
    unordered_map<char, int> idxs;
    vector<bool> expectedChars;
    vector<bool> actualChars;

    // test 1 - assignment example
    idxs.clear();
    expectedChars = vector<bool>(pow(2, CHAR_BIT), false);
    actualChars = vector<bool>(pow(2, CHAR_BIT), false);
    result = findAlphabet(dictionary, alphabet);
    EXPECT_TRUE(result);
    EXPECT_EQ(4, alphabet.size());
    for (char c : {'A', 'R', 'C', 'T'}) {
        expectedChars[c] = true;
    }
    for (int i = 0; i < alphabet.size(); i++) {
        idxs[alphabet[i]] = i;
        actualChars[alphabet[i]] = true;
    }
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(idxs['A'] < idxs['R']);
    EXPECT_TRUE(idxs['R'] < idxs['C']);
    EXPECT_TRUE(idxs['T'] < idxs['R']);

    // test 2 - empty dictionary
    dictionary.clear();
    result = findAlphabet(dictionary, alphabet);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, alphabet.size());

    // test 3 - inconsistent dictionary
    dictionary = {"ART", "RAT", "ABS"};
    result = findAlphabet(dictionary, alphabet);
    EXPECT_FALSE(result);
    EXPECT_EQ(0, alphabet.size());

    // test 4
    dictionary = {"ABC", "DEFG", "HIJK", "LMN", "OPQRS", "TU", "VWXYZ"};
    expectedChars = vector<bool>(pow(2, CHAR_BIT), false);
    actualChars = vector<bool>(pow(2, CHAR_BIT), false);
    idxs.clear();
    result = findAlphabet(dictionary, alphabet);
    EXPECT_TRUE(result);
    EXPECT_EQ(26, alphabet.size());
    for (char c = 'A'; c <= 'Z'; c++) {
        expectedChars[c] = true;
    }
    for (int i = 0; i < alphabet.size(); i++) {
        idxs[alphabet[i]] = i;
        actualChars[alphabet[i]] = true;
    }
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(idxs['A'] < idxs['D']);
    EXPECT_TRUE(idxs['D'] < idxs['H']);
    EXPECT_TRUE(idxs['H'] < idxs['L']);
    EXPECT_TRUE(idxs['L'] < idxs['O']);
    EXPECT_TRUE(idxs['O'] < idxs['T']);
    EXPECT_TRUE(idxs['T'] < idxs['V']);

    // test 5
    dictionary = {"abd", "abc", "^pap", "^alk", "*$llo", "car", "01o"};
    expectedChars = vector<bool>(pow(2, CHAR_BIT), false);
    actualChars = vector<bool>(pow(2, CHAR_BIT), false);
    idxs.clear();
    result = findAlphabet(dictionary, alphabet);
    EXPECT_TRUE(result);
    EXPECT_EQ(14, alphabet.size());
    for (char c : {'a', 'b', 'c', 'd', 'p', '^', 'l', 'k', '*', '$', 'o', 'r', '0', '1'}) {
        expectedChars[c] = true;
    }
    for (int i = 0; i < alphabet.size(); i++) {
        idxs[alphabet[i]] = i;
        actualChars[alphabet[i]] = true;
    }
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(idxs['a'] < idxs['^']);
    EXPECT_TRUE(idxs['d'] < idxs['c']);
    EXPECT_TRUE(idxs['p'] < idxs['a']);
    EXPECT_TRUE(idxs['^'] < idxs['*']);
    EXPECT_TRUE(idxs['*'] < idxs['c']);
    EXPECT_TRUE(idxs['c'] < idxs['0']);

    return 0;
}