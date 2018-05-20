#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

void word_anagram(bool case_sens) {
	std::string word_1, word_2;
	std::cin >> word_1 >> word_2;
	if (!case_sens) {
		std::transform(word_1.begin(), word_1.end(), word_1.begin(), std::ptr_fun <int, int> (std::tolower));
		std::transform(word_2.begin(), word_2.end(), word_2.begin(), std::ptr_fun <int, int> (std::tolower));
	}
	if (word_1.length() != word_2.length()) {
		std::cout << "Second word isn't anagram of first\n";
		return;
	}

	std::vector<int> count(256, 0);
	for (auto ch : word_1) {
		count[ch]++;
	}
	for (auto ch : word_2) {
		if (count[ch] > 0) {
			count[ch]--;
		} else {
			std::cout << "Second word isn't anagram of first\n";
			return;
		}
	}

	std::cout << "Yes, second word is anagram of first\n";
	return;
}

std::vector<std::string> line_to_words(std::string line) {
	std::string word = "";
	std::vector<std::string> words;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ' ) {
			if (word != "") {
				std::sort(word.begin(), word.end());
				words.push_back(word);
				word = "";
			}
		} else {
			word += line[i];
		}
	}
	if (word != "") {
		std::sort(word.begin(), word.end());
		words.push_back(word);
	}
	return words;
}

void sentence_anagram(bool case_sens) {
	std::string line_1, line_2;
	std::getline(std::cin, line_1);
	std::getline(std::cin, line_1);
	std::getline(std::cin, line_2);
	if (!case_sens) {
		std::transform(line_1.begin(), line_1.end(), line_1.begin(), std::ptr_fun <int, int>(std::tolower));
		std::transform(line_2.begin(), line_2.end(), line_2.begin(), std::ptr_fun <int, int>(std::tolower));
	}
	if (line_1.length() != line_2.length()) {
		std::cout << "Second sentence isn't anagram of first\n";
		return;
	}
	std::vector<std::string> words_1, words_2;
	words_1 = line_to_words(line_1);
	words_2 = line_to_words(line_2);
	if (words_1.size() != words_2.size()) {
		std::cout << "Second sentence isn't anagram of first\n";
		return;
	}
	std::sort(words_1.begin(), words_1.end());
	std::sort(words_2.begin(), words_2.end());
	for (int i = 0; i < words_1.size(); i++) {
		if (words_1[i] != words_2[i]) {
			std::cout << "Second sentence isn't anagram of first\n";
			return;
		}
	}
	
	std::cout << "Yes, second word is anagram of first\n";
	return;
}

int main() {
	int type_of_ask, case_sens;
	std::cout << "I need information about type of question: is it only one word or whole sentence?\n1 -- one word\n2 -- whole sentence\n";
	std::cin >> type_of_ask;
	std::cout << "Do you want case sensitive or case insensitive anagrams?\n1 -- case sensitive\n2 -- case insensitive\n";
	std::cin >> case_sens;
	if (type_of_ask == 1) {
		word_anagram((case_sens == 1)?true:false);
	} else {
		sentence_anagram((case_sens == 1)?true:false);
	}
	return 0;	
}
