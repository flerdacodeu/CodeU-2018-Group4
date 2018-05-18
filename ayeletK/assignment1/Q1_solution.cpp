#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

/**
    Determine if a character is a punctuation mark
	  from the next list: ‘ ‘/’,’/’.’/’!’/’?’
    @param c - the character to be checked
    @return true if the character is a punctuation mark,
	    false otherwise.
    
    example:
    c = "!"
    ------------------
    true
*/
bool is_punctuation_mark(char c){
    if (c == ' ' || c == ',' || c == '.' ||
        c == '!' || c == '?'){
            return true;
        }
    return false;
}

/**
    Split a sentence by white spaces and punctuation marks
    [',','.','!','?'] into a vector and sort each word 
    ("aba" --> "aab")

    @param str - the sentence to be splitted
    @param case_sensitive - a flag determins if we are 
      working in a case sensitive mode or not.
      if not 'case_sensitive' then all letters will be 
      lowered to lower case.
    @return a vector of strings, each string in the result
      vector represent a sorted word from the original
      sentence.
    
    example:
    str = "Like a G6"
    case_sensitive = false
    ------------------
    words: <"eikl", "a", "6g">
*/
vector<string> split_to_words(string str, bool case_sensitive){
    vector<string> words;
    string curr_str = "";
    for (int i = 0; i<str.length() ; ++i){
    // add new word to words vector when reaching to a punctuation mark
		if (is_punctuation_mark(str[i]) && !curr_str.empty()){
		    sort(curr_str.begin(), curr_str.end());
			words.push_back(curr_str);
			curr_str.clear();
			while (i+1<str.length() && is_punctuation_mark(str[i+1])){
			    ++i;
			}
		}
    // add character to the current word
		else {
		    char curr_char = str[i];
		    if (!case_sensitive){
		        curr_char = tolower(curr_char);
		    }
		    curr_str += curr_char;
		}
	}
  // save the last word in the sentence, in case it ends with a word
	if (!curr_str.empty()){
	    sort(curr_str.begin(), curr_str.end());
		words.push_back(curr_str);
	}
	return words;
}

/**
    check if two strings are anagrams.
    if the input strings are sentences - check each word in
        one sentence is an anagram of a word in the other
        sentence.

    @param str1 - first string
    @param str2 - second string
    @param case_sensitive - a flag determins if we are 
            working in a case sensitive mode or not.
    @return true if the strings are anagrams, false otherwise
    
    example:
    str1 = "Good morning, world"
    str1 = "doog world mornign!"
    case_sensitive = false
    ------------------
    true
*/
bool are_anagrams(string str1, string str2, bool case_sensitive = false){
    // 	split the string to words
    vector<string> words1 = split_to_words(str1, case_sensitive);
	vector<string> words2 = split_to_words(str2, case_sensitive);
    // 	compare number of words in each
    if (words1.size() != words2.size()){
	    return false;
	}
	// sorting the vectors
	sort(words1.begin(), words1.end());
	sort(words2.begin(), words2.end());
	// compare vectors
	if (words1 == words2){
	    return true;
	}
	return false;
}
