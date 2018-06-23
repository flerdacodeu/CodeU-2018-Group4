#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

class Dictionary{
public:
	set<string> words;
	set<string> prefixes;

	Dictionary();
	Dictionary(set<string> words, set<string> prefixes);

	bool isWord(string word);
	bool isPrefix(string prefix);
};