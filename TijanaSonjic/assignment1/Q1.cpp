#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool isWord(string word) {
	for (int i = 0; i < word.length(); i++)
		if (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')))
			return false;
	return true;
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

		if (!caseSensitive && letter < 'a')
			letter += 'a' - 'A';		
			
		auto it = lettersDifCount.find(letter);
		if (it != lettersDifCount.end())
			it->second++;
		else
			lettersDifCount.insert(lettersDifCount.end(), pair<char, int>(letter, 1));
	}

	for (int i = 0; i < word2.length(); i++) {
		char letter = word2[i];
		
		if (!caseSensitive && letter < 'a')
			letter += 'a' - 'A';

		auto it = lettersDifCount.find(letter);
		if (it != lettersDifCount.end() && it->second > 0)
			it->second--;
		else
			return false;
	}

	// if we come this far this means that those words are anagrams
	return true;
}

vector<string> splitWordsBySpace(string sentence) {
	istringstream iss(sentence);
	vector<string> words{ istream_iterator<string>{iss}, istream_iterator<string>{}};

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

	if (words1.size() != words2.size())
		return false;

	unordered_map<string, int> wordsDifCount;

	for (int i = 0; i < words1.size(); i++) {
		string key = generateKey(words1[i], caseSensitive);

		auto it = wordsDifCount.find(key);
		if (it != wordsDifCount.end())
			it->second++;
		else
			wordsDifCount.insert(wordsDifCount.end(), pair<string, int>(key, 1));
	}

	for (int i = 0; i < words2.size(); i++) {
		string key = generateKey(words2[i], caseSensitive);

		auto it = wordsDifCount.find(key);

		if (it != wordsDifCount.end() && it->second>0)
			it->second--;
		else
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

	if (isAnagram(word1, word2, 0))
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