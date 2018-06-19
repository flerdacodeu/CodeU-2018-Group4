#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

class Dictionary{
    set<string> _words;
    set<string> _prefixes;
public:
    Dictionary(set<string> words): _words(words) {
        vector<char> curr_prefix;
        for (string word: _words){
            for (char c: word){
                curr_prefix.push_back(c);
                _prefixes.insert(string(curr_prefix.begin(), curr_prefix.end()));
            }
            curr_prefix.clear();
        }
    }
    bool is_word(string word){
        return _words.find(word) != _words.end();
    }
    bool is_prefix(string prefix){
        return _prefixes.find(prefix) != _prefixes.end();
    }
};
