#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

/* -------------- Helper Methods -------------- */

// return true if c is one of ‘ ‘/’,’/’.’/’!’/’?’
bool is_punctuation_mark(char c){
	return c == ' ' || c == ',' || c == '.' || c == '!' || c == '?';
}

void lower_each_string(vector<string>& data){
	for (string& str: data){
		for (char& c; str){
			c = tolower(c);
		}
	}
}

void sort_each_string(vector<string>& data){
	for (string& str: data){
		sort(str.begin(), str.end());
	}
}

/* -------------- Main Methods -------------- */

vector<string> split_to_words(string str){
	vector<string> words;
	string curr_str;
	for (int i = 0; i<str.length() ; ++i){
		char curr_char = str[i];
		// Reaching a punctuation mark means an end of a word. Add the accumulated word to the vector.
		if (is_punctuation_mark(curr_char) && !curr_str.empty()){
			words.push_back(curr_str);
			curr_str.clear();
		}
    // add character to the current word
		else if (!is_punctuation_mark(curr_char)){
			curr_str += curr_char;
		}
	}
  // save the last word in the sentence, in case it ends with a word
	if (!curr_str.empty()){
		words.push_back(curr_str);
	}
	return words;
}

bool are_anagrams(string str1, string str2, bool case_sensitive = false){
	vector<string> words1 = split_to_words(str1);
	vector<string> words2 = split_to_words(str2);
	// compare number of words in each vector
	if (words1.size() != words2.size()){
		return false;
	}
	// lower all characters if we are handling case insensitive.
	if (!case_sensitive){
		lower_each_string(words1);
		lower_each_string(words2);
	}
	// sort each word in words1, words2 vectors
	sort_each_string(words1);
	sort_each_string(words2);
	sort(words1.begin(), words1.end());
	sort(words2.begin(), words2.end());
	return words1 == words2;
}
