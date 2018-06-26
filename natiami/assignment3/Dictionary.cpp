#include "Dictionary.h"

Dictionary::Dictionary(){
}

Dictionary::Dictionary(set<string>& words, set<string>& prefixes){
	this->words = words;
	this->prefixes = prefixes;
}

bool Dictionary::isWord(string& word) const {
	return words.find(word) != words.end();
}
bool Dictionary::isPrefix(string& prefix) const{
	return prefixes.find(prefix) != prefixes.end();
}
