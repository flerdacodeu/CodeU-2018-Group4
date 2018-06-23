#pragma once

#include <set>

class Dictionary{
private:
	set<string> dictionary;
	set<string> prefixes;

	// This allows the search function to abort search paths which can never result in words.
	//
	void generateWordsPrefixes() {
		for (const string& word : dictionary) {
			for (int i = 0; i <= word.length(); i++) {
				prefixes.insert(word.substr(0, i));
			}
		}
	}
public:	
	Dictionary(set<string> words): dictionary(words) {
		generateWordsPrefixes();
	}

	bool isPrefix(string word) {
		return prefixes.find(word) != prefixes.end();
	}

	bool isWord(string word) {
		return dictionary.find(word) != dictionary.end();
	}

	bool isEmpty() {
		return dictionary.size() == 0;
	}
};

