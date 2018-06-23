#include "Dictionary.h"

Dictionary::Dictionary(){
	this->words = set<string>();
	this->prefixes = set<string>();
}

Dictionary::Dictionary(set<string> words, set<string> prefixes){
	this->words = words;
	this->prefixes = prefixes;
}

bool Dictionary::isWord(string word){
	return words.find(word) != words.end();
}
bool Dictionary::isPrefix(string prefix){
	return prefixes.find(prefix) != prefixes.end();
}
