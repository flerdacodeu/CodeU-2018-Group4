#include "AlphabetFromDictionary.hpp"
#include "codeu_test_lib.h"

int main() {
    vector<string> dictionary;
    vector<char> alphabet;
    bool result;
    unordered_map<char, int> idxs;
    vector<bool> expectedChars;
    vector<bool> actualChars;

    // test 1 - assignment example
    dictionary = {"ART", "RAT", "CAT", "CAR"};
    AlphabetFromDictionary afd(dictionary);
    idxs.clear();
    expectedChars = vector<bool>(pow(2, CHAR_BIT), false);
    actualChars = vector<bool>(pow(2, CHAR_BIT), false);
    result = afd.findAlphabet(alphabet);
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
    afd.setDictionary(dictionary);
    result = afd.findAlphabet(alphabet);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, alphabet.size());

    // test 3 - inconsistent dictionary
    dictionary = {"ART", "RAT", "ABS"};
    afd.setDictionary(dictionary);
    result = afd.findAlphabet(alphabet);
    EXPECT_FALSE(result);
    EXPECT_EQ(0, alphabet.size());

    // test 4
    dictionary = {"ABC", "DEFG", "HIJK", "LMN", "OPQRS", "TU", "VWXYZ"};
    afd.setDictionary(dictionary);
    expectedChars = vector<bool>(pow(2, CHAR_BIT), false);
    actualChars = vector<bool>(pow(2, CHAR_BIT), false);
    idxs.clear();
    result = afd.findAlphabet(alphabet);
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
    afd.setDictionary(dictionary);
    expectedChars = vector<bool>(pow(2, CHAR_BIT), false);
    actualChars = vector<bool>(pow(2, CHAR_BIT), false);
    idxs.clear();
    result = afd.findAlphabet(alphabet);
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