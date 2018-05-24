#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <algorithm>

using namespace std;


void makeLowerLetter(char* letter) {
	*letter = *letter + 'a' - 'A';
}

bool isUpperCase(char letter) {
	return letter >= 'A' && letter <= 'Z';
}

bool isLowerCase(char letter) {
	return letter >= 'a' && letter <= 'z';
}

bool isWord(string word) {
	for (char letter : word) {
		if (!isLowerCase(letter) && !isUpperCase(letter))
			return false;
	}

	return true;
}

void makeLowerLetterIfNeeded(char* letter, bool caseSensitive) {
	if (!caseSensitive && isUpperCase(*letter))
		makeLowerLetter(letter);
}

// Function that checks whether two words are anagram of each other.
// Both arguments must be words. It has better time complexity than function areTwoSentencesAnagrams.
// 
bool isAnagram(string word1, string word2, bool caseSensitive) {
	if (!isWord(word1) || !isWord(word2))
		return false;

	if (word1.length() != word2.length())
		return false;

	unordered_map<char, int> lettersDifCount;

	for (int i = 0; i < word1.length(); i++) {
		char letter = word1[i];

		makeLowerLetterIfNeeded(&letter, caseSensitive);
		
		lettersDifCount[letter]++;
	}

	for (int i = 0; i < word2.length(); i++) {
		char letter = word2[i];
		
		makeLowerLetterIfNeeded(&letter, caseSensitive);

		lettersDifCount[letter]--;

		if (lettersDifCount[letter] < 0)
			return false;
	}

	// if we come this far this means that those words are anagrams
	return true;
}

vector<string> splitWordsBySpace(string sentence) {
	istringstream iss(sentence);
	vector<string> words(istream_iterator<string>{iss}, istream_iterator<string>{});

	return words;
}

// This function generates key entry to hash map.
// Returning value is string sorted in alphabetic order.
// If you want to generate case insensitive key, then all letters will be converted to lower letters.
//
string generateKey(string word, bool caseSensitive) {
	if (!caseSensitive) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
	}

	sort(word.begin(), word.end());

	return word;
}

// This function checks whether two sentences are anagram of each other.
// With third argument you can choose if you want to handle case sensitive or case insensitive anagrams.
//
bool areTwoSentencesAnagrams(string sentence1, string sentence2, bool caseSensitive) {
	if (sentence1.length() != sentence2.length())
		return false;

	vector<string> words1 = splitWordsBySpace(sentence1);
	vector<string> words2 = splitWordsBySpace(sentence2);

	bool continueAlgorithm = true;

	if (words1.size() != words2.size())
		return false;

	unordered_map<string, int> wordsDifCount;

	for (int i = 0; i < words1.size(); i++) {
		string key = generateKey(words1[i], caseSensitive);
		wordsDifCount[key]++;
	}

	for (int i = 0; i < words2.size(); i++) {
		string key = generateKey(words2[i], caseSensitive);
		wordsDifCount[key]--;

		if (wordsDifCount[key] < 0)
			return false;
	}

	// if we come so far this means that those words are anagrams of each other
	return true;
}

// Test function
int main() {
	string word1 = "tijanatijana";
	string word2 = "tijanaTijana";

	string sentence1 = "Today is a great day";
	string sentence2 = "Is a treag toayd ayd";

	if (isAnagram(word1, word2, false))
		cout << "Words " << word1 << " and " << word2 << " are anagrams." << endl;
	else
		cout << "Words " << word1 << " and " << word2 << " are not anagrams." << endl;

	if (areTwoSentencesAnagrams(sentence1, sentence2, true))
		cout << "Sentences are anagrams." << endl;
	else
		cout << "Sentences are not anagrams." << endl;
	
	system("PAUSE");
	return 0;
}
