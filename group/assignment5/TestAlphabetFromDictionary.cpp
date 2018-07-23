#include "TestAlphabetFromDictionary.hpp"

void TestAlphabetFromDictionary::runAllTests() {
	testEmptyDictionary();
	testValidDictionary();
	testValidDictionaryWithNonLatinLetters();
	testValidDictionaryWithEmptyWords();
	testInconsisntentDictionary();
	testInconsisntentDictionaryWithEmptyWords();
	testDictionaryWithComplexInconsistency();
	testFindAllAlphabets();
	testFindAllAlphabetsWithEmptyWords();
}

void TestAlphabetFromDictionary::testEmptyDictionary() {
    vector<string> dictionary;
    AlphabetFromDictionary alphabetFromDictionary(dictionary);
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    EXPECT_EQ(0, alphabetFromDictionary.getAlphabet().size());    
}

void TestAlphabetFromDictionary::testValidDictionary() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"ART", "RAT", "CAT", "CAR"}));
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    vector<char> alphabet = alphabetFromDictionary.getAlphabet();
    set<char> actualChars(alphabet.begin(), alphabet.end());
    set<char> expectedChars({'A', 'R', 'C', 'T'});
    unordered_map<char, int> charSequentialNumber;
    EXPECT_EQ(4, alphabet.size());
    for (int i = 0; i < alphabet.size(); i++) 
        charSequentialNumber[alphabet[i]] = i;
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(charSequentialNumber['A'] < charSequentialNumber['R']);
    EXPECT_TRUE(charSequentialNumber['R'] < charSequentialNumber['C']);
    EXPECT_TRUE(charSequentialNumber['T'] < charSequentialNumber['R']);
}

void TestAlphabetFromDictionary::testValidDictionaryWithNonLatinLetters() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"abd", "abc", "^pap", "^alk", "*$llo", "car", "01o"}));
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    vector<char> alphabet = alphabetFromDictionary.getAlphabet();
    set<char> actualChars(alphabet.begin(), alphabet.end());
    set<char> expectedChars({'a', 'b', 'c', 'd', 'p', '^', 'l', 'k', '*', '$', 'o', 'r', '0', '1'});
    unordered_map<char, int> charSequentialNumber;
    EXPECT_EQ(14, alphabet.size());
    for (int i = 0; i < alphabet.size(); i++)
        charSequentialNumber[alphabet[i]] = i;
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(charSequentialNumber['a'] < charSequentialNumber['^']);
    EXPECT_TRUE(charSequentialNumber['d'] < charSequentialNumber['c']);
    EXPECT_TRUE(charSequentialNumber['p'] < charSequentialNumber['a']);
    EXPECT_TRUE(charSequentialNumber['^'] < charSequentialNumber['*']);
    EXPECT_TRUE(charSequentialNumber['*'] < charSequentialNumber['c']);
    EXPECT_TRUE(charSequentialNumber['c'] < charSequentialNumber['0']);
}

void TestAlphabetFromDictionary::testValidDictionaryWithEmptyWords() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"ART", "RAT", "", "CAR"}));
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    vector<char> alphabet = alphabetFromDictionary.getAlphabet();
    set<char> actualChars(alphabet.begin(), alphabet.end());
    set<char> expectedChars( {'A', 'R', 'C', 'T'});
    unordered_map<char, int> charSequentialNumber;
    EXPECT_EQ(4, alphabet.size());
    for (int i = 0; i < alphabet.size(); i++) 
        charSequentialNumber[alphabet[i]] = i;
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(charSequentialNumber['A'] < charSequentialNumber['R']);
    EXPECT_TRUE(charSequentialNumber['R'] < charSequentialNumber['C']);
}

void TestAlphabetFromDictionary::testInconsisntentDictionary() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"ART", "RAT", "CAC", "CAR"}));
    EXPECT_FALSE(alphabetFromDictionary.isDictionaryConsistent());
    vector<string> consistentSubDictionary = alphabetFromDictionary.makeDictionaryConsistent();
    alphabetFromDictionary.setDictionary(consistentSubDictionary);
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    vector<char> alphabet = alphabetFromDictionary.getAlphabet();
    set<char> actualChars(alphabet.begin(), alphabet.end());
    set<char> expectedChars( {'A', 'R', 'C', 'T'});
    unordered_map<char, int> charSequentialNumber;
    EXPECT_EQ(4, alphabet.size());
    for (int i = 0; i < alphabet.size(); i++) 
        charSequentialNumber[alphabet[i]] = i;
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(charSequentialNumber['A'] < charSequentialNumber['R']);
    EXPECT_TRUE(charSequentialNumber['C'] < charSequentialNumber['R']);
}

void TestAlphabetFromDictionary::testInconsisntentDictionaryWithEmptyWords() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"", "ART", "RAT", "CAC", "", "CAR", ""}));
    EXPECT_FALSE(alphabetFromDictionary.isDictionaryConsistent());
    vector<string> consistentSubDictionary = alphabetFromDictionary.makeDictionaryConsistent();
    alphabetFromDictionary.setDictionary(consistentSubDictionary);
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    vector<char> alphabet = alphabetFromDictionary.getAlphabet();
    set<char> actualChars(alphabet.begin(), alphabet.end());
    set<char> expectedChars( {'A', 'R', 'C', 'T'});
    unordered_map<char, int> charSequentialNumber;
    EXPECT_EQ(4, alphabet.size());
    for (int i = 0; i < alphabet.size(); i++) 
        charSequentialNumber[alphabet[i]] = i;
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(charSequentialNumber['A'] < charSequentialNumber['R']);
    EXPECT_TRUE(charSequentialNumber['C'] < charSequentialNumber['R']);
}

void TestAlphabetFromDictionary::testDictionaryWithComplexInconsistency() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"ART", "RAT", "CAC", "CAR", "RRC", "RRA"}));
    EXPECT_FALSE(alphabetFromDictionary.isDictionaryConsistent());
    vector<string> consistentSubDictionary = alphabetFromDictionary.makeDictionaryConsistent();
    alphabetFromDictionary.setDictionary(consistentSubDictionary);
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    vector<char> alphabet = alphabetFromDictionary.getAlphabet();
    set<char> actualChars(alphabet.begin(), alphabet.end());
    set<char> expectedChars( {'A', 'R', 'C'});
    unordered_map<char, int> charSequentialNumber;
    EXPECT_EQ(3, alphabet.size());
    for (int i = 0; i < alphabet.size(); i++) 
        charSequentialNumber[alphabet[i]] = i;
    EXPECT_EQ(expectedChars, actualChars);
    EXPECT_TRUE(charSequentialNumber['C'] < charSequentialNumber['A']);
    EXPECT_TRUE(charSequentialNumber['C'] < charSequentialNumber['R']);
}

void TestAlphabetFromDictionary::testFindAllAlphabets() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"ART", "RAT", "CAT", "CAR"}));
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    set<vector<char>> allAlphabetsFromDictionary = alphabetFromDictionary.findAllAlphabets();
    EXPECT_EQ(2, allAlphabetsFromDictionary.size());
    for (auto& alphabet :allAlphabetsFromDictionary) {
        set<char> actualChars(alphabet.begin(), alphabet.end());
        set<char> expectedChars( {'A', 'R', 'C', 'T'});
        unordered_map<char, int> charSequentialNumber;
        EXPECT_EQ(4, alphabet.size());
        for (int i = 0; i < alphabet.size(); i++) 
            charSequentialNumber[alphabet[i]] = i;
        EXPECT_EQ(expectedChars, actualChars);
        EXPECT_TRUE(charSequentialNumber['A'] < charSequentialNumber['R']);
        EXPECT_TRUE(charSequentialNumber['R'] < charSequentialNumber['C']);
        EXPECT_TRUE(charSequentialNumber['T'] < charSequentialNumber['R']);
    }    
}

void TestAlphabetFromDictionary::testFindAllAlphabetsWithEmptyWords() {
    AlphabetFromDictionary alphabetFromDictionary(vector<string> ({"", "Doo", "", "Dee", "Daa", ""}));
    EXPECT_TRUE(alphabetFromDictionary.isDictionaryConsistent());
    set<vector<char>> allAlphabetsFromDictionary = alphabetFromDictionary.findAllAlphabets();
    EXPECT_EQ(4, allAlphabetsFromDictionary.size());
    for (auto& alphabet :allAlphabetsFromDictionary) {
        set<char> actualChars(alphabet.begin(), alphabet.end());
        set<char> expectedChars( {'D', 'o', 'e', 'a'});
        unordered_map<char, int> charSequentialNumber;
        EXPECT_EQ(4, alphabet.size());
        for (int i = 0; i < alphabet.size(); i++) 
            charSequentialNumber[alphabet[i]] = i;
        EXPECT_EQ(expectedChars, actualChars);
        EXPECT_TRUE(charSequentialNumber['o'] < charSequentialNumber['e']);
        EXPECT_TRUE(charSequentialNumber['e'] < charSequentialNumber['a']);
    }    
}