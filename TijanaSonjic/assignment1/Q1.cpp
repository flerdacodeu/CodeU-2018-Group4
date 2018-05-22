#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool isWord(string word) {
	for each (char letter in word){
		if (!((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')))
			return false;
	}

	return true;
}

void makeSmallLetter(char* letter) {
	*letter = *letter + 'a' - 'A';
}

bool isUpperCase(char letter) {
	return letter >= 'A' && letter <= 'Z';
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

		if (!caseSensitive && isUpperCase(letter))
			makeSmallLetter(&letter);

		lettersDifCount[letter]++;
	}

	for (int i = 0; i < word2.length(); i++) {
		char letter = word2[i];
		
		if (!caseSensitive && isUpperCase(letter))
			makeSmallLetter(&letter);

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

void updateCounters(unordered_map<string, int>* wordsDifCount, string word, bool caseSensitive, int inc, bool* continueAlgorithm) {
	string key = generateKey(word, caseSensitive);
	(*wordsDifCount)[key] += inc;

	if ((*wordsDifCount)[key] < 0)
		*continueAlgorithm = false;
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
		updateCounters(&wordsDifCount, words1[i], caseSensitive, 1, &continueAlgorithm);
	}

	for (int i = 0; i < words2.size(); i++) {
		updateCounters(&wordsDifCount, words2[i], caseSensitive, -1, &continueAlgorithm);

		if (!continueAlgorithm)
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

	if (isAnagram(word1, word2, 1))
		cout << "Words " << word1 << " and " << word2 << " are anagrams." << endl;
	else
		cout << "Words " << word1 << " and " << word2 << " are not anagrams." << endl;

	if (areTwoSentencesAnagrams(sentence1, sentence2, 0))
		cout << "Sentences are anagrams." << endl;
	else
		cout << "Sentences are not anagrams." << endl;
	

	system("PAUSE");
	return 0;
}
