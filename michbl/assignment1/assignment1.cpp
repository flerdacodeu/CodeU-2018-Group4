#include <iostream>
#include <vector>
#include <list>

using namespace std;
#define ALPHABET_SIZE 128

//Question 1 - Anagrams

//check whether a character is an english letter
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//check whether 2 words (strings without whitespaces) are anagrams of each other
bool anagramsAux(string str1, string str2, bool caseSensitive) {
    vector<int> histogram(ALPHABET_SIZE);
    int len1 = str1.length();
    int len2 = str2.length();
    if (len1 != len2)
        return false;
    for (int i = 0; i < len1; i++) {
        histogram[str1[i]]++;
        histogram[str2[i]]--;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (caseSensitive || !isLetter((char)i)) {
            if (histogram[i] != 0) {
                return false;
            }
        }
        else { // case insensitive and i is the ascii value of a letter
            if (i >= 'a' && histogram[i] + histogram[i - 'a' + 'A'] != 0) {
                return false;
            }
            else if (i < 'a' && histogram[i] + histogram[i - 'A' + 'a'] != 0) {
                return false;
            }
        }
    }
    return true;
}

//check whether 2 sentences (strings with/without whitespaces) are anagrams of each other
bool anagrams(string str1, string str2, bool caseSensitive) {
    vector<string> words1;
    vector<string> words2;

    //split str1 into words
    size_t pos = 0, found = str1.find_first_of(' ', pos);
    while (found != string::npos) {
        words1.push_back(str1.substr(pos, found - pos));
        pos = found+1;
        found = str1.find_first_of(' ', pos);
    }
    words1.push_back(str1.substr(pos));

    //split str2 into words
    pos = 0;
    found = str2.find_first_of(' ', pos);
    while (found != string::npos) {
        words2.push_back(str2.substr(pos, found - pos));
        pos = found+1;
        found = str2.find_first_of(' ', pos);
    }
    words2.push_back(str2.substr(pos));

    if (words1.size() != words2.size()) {
        return false;
    }

    bool match;
    while (!words1.empty()) {
        match = false;
        vector<string>::iterator it1 = words1.begin();
        vector<string>::iterator it2 = words2.begin();
        while (it2 != words2.end()) {
            if (anagramsAux(*it1, *it2, caseSensitive)) {
                match = true;
                words1.erase(it1);
                words2.erase(it2);
                break;
            }
            it2++;
        }
        if (!match)
            return false;
    }
    return true;
}

//Question 2 - kth to last
template <typename T>
T kthToLast(list<T> l, unsigned int k) {
    int size = l.size();
    if (k > size - 1)
        throw runtime_error("k is too big");
    int idx = size - k - 1;
    typename list<T>::iterator it = l.begin();
    for (int i = 0; i < idx; i++) {
        it++;
    }
    return *it;
}