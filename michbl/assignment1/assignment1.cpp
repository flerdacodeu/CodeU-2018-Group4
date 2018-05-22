#include <iostream>
#include <vector>
#include <list>

using namespace std;
#define ALPHABET_SIZE 128

//Question 1 - Anagrams

// Assumes that given words are without spaces
bool areWordsAnagrams(string word1, string word2, bool caseSensitive);

bool isUpperCase(char c) {
    return (c >= 'A' && c <= 'Z');
}

bool isLowerCase(char c) {
    return (c >= 'a' && c <= 'z');
}

// Check whether a character is an english letter
bool isLetter(char c) {
    return isUpperCase(c) || isLowerCase(c);
}

char toUpperCase(char c) {
    if (!isLetter(c)) {
        return 0;
    }
    else if (isLowerCase(c)) {
        return c - 'a' + 'A';
    }
    else // c is uppercase
        return c;
}

char toLowerCase(char c) {
    if (!isLetter(c)) {
        return 0;
    }
    else if (isUpperCase(c)) {
        return c - 'A' + 'a';
    }
    else // c is lowercase
        return c;
}

int countCaseInsensitiveLettersInHistogram(char c, const vector<int>& hist) {
    if (!isLetter(c) || hist.size() != ALPHABET_SIZE) {
        return -1;
    }
    if (isLowerCase(c)) {
        return hist[c] + hist[toUpperCase(c)];
    }
    else { // c is uppercase
        return hist[c] + hist[toLowerCase(c)];
    }
}

vector<string> splitSentenceToWords(const string& sentence) {
    vector<string> words;
    size_t pos = 0, found = sentence.find_first_of(' ', pos);
    while (found != string::npos) {
        words.push_back(sentence.substr(pos, found - pos));
        pos = found+1;
        found = sentence.find_first_of(' ', pos);
    }
    words.push_back(sentence.substr(pos));
    return words;
}

// Returns an iterator to a word in wordsList which is an anagram of wordToFind.
// Returns wordsList.end() if no anagram found.
vector<string>::const_iterator findAnagramInList (const vector<string>& wordsList, const string& wordToFind, bool caseSensitive) {
    for (vector<string>::const_iterator it = wordsList.begin(); it != wordsList.end(); it++) {
        if (areWordsAnagrams(*it, wordToFind, caseSensitive)) {
            return it;
        }
    }
    return wordsList.end();
}

// Assumes that given words are without spaces
bool areWordsAnagrams(string word1, string word2, bool caseSensitive) {
    vector<int> histogram(ALPHABET_SIZE);

    int len1 = word1.length();
    int len2 = word2.length();
    if (len1 != len2)
        return false;

    for (int i = 0; i < len1; i++) {
        histogram[word1[i]]++;
        histogram[word2[i]]--;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        char c = (char) i;
        if (caseSensitive || !isLetter(c)) {
            if (histogram[c] != 0) {
                return false;
            }
        }
        else { // case insensitive and i is the ascii value of a letter
            if (countCaseInsensitiveLettersInHistogram(c, histogram) != 0) {
                return false;
            }
        }
    }
    return true;
}

// check whether 2 sentences (strings with/without spaces) are anagrams of each other
bool areSentencesAnagrams(string sentence1, string sentence2, bool caseSensitive) {
    vector<string> words1 = splitSentenceToWords(sentence1);
    vector<string> words2 = splitSentenceToWords(sentence2);

    if (words1.size() != words2.size()) {
        return false;
    }

    // try to match each word from sentence1 to a word from sentence2
    while (!words1.empty()) {
        vector<string>::iterator it1 = words1.begin();
        vector<string>::const_iterator it2 = findAnagramInList(words2, *it1, caseSensitive);
        if (it2 == words2.end()) {
            return false;
        }
        else {
            words1.erase(it1);
            words2.erase(it2);
        }
    }
    return true;
}

//Question 2 - kth to last
template <typename T>
T kthToLast(list<T> l, unsigned int k) {
    int size = l.size();
    if (k < 0 || k >= size)
        throw runtime_error("k out of range");
    int idx = size - k - 1;
    typename list<T>::iterator it = l.begin();
    for (int i = 0; i < idx; i++) {
        it++;
    }
    return *it;
}