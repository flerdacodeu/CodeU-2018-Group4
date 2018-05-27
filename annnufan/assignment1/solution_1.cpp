#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

bool word_anagram(std::string word_1, std::string word_2, bool case_sens) {
	if (!case_sens) {
		std::transform(word_1.begin(), word_1.end(), word_1.begin(), ::tolower);
		std::transform(word_2.begin(), word_2.end(), word_2.begin(), ::tolower);
	}
	if (word_1.length() != word_2.length()) {
		return false;
	}

	std::vector<int> count(256, 0);
	
	//String used signed char. So, it needs to add 127 for each char for counting sort 
	for (unsigned char ch : word_1) {
		count[ch]++;
	}
	for (unsigned char ch : word_2) {
		if (count[ch] > 0) {
			count[ch]--;
		} else {
			return false;
		}
	}
	return true;
}

void solve_for_word(bool case_sens) {
	std::string word_1, word_2;
	std::cin >> word_1 >> word_2;
	if (word_anagram(word_1, word_2, case_sens)) {
		std::cout << "anagram\n";
	} else {
		std::cout << "not anagram\n";
	}
}

std::vector<std::string> line_to_words(std::string line) {
	std::string word = "";
	std::vector<std::string> words;
	for (int i = 0; i < (int)line.length(); i++) {
		if (line[i] == ' ' ) {
			if (word != "") {
				words.push_back(word);
				word = "";
			}
		} else {
			word += line[i];
		}
	}
	if (word != "") {
		words.push_back(word);
	}
	return words;
}

std::vector<std::string> sorted_words(std::vector<std::string> words) {
	std::vector<std::string> sorted_words;
	for (auto word: words) {
		std::sort(word.begin(), word.end());
		sorted_words.push_back(word);
	}
	return sorted_words;
}

bool sentence_anagram(std::string line_1, std::string line_2, bool case_sens) {
	if (!case_sens) {
		std::transform(line_1.begin(), line_1.end(), line_1.begin(), std::ptr_fun <int, int>(std::tolower));
		std::transform(line_2.begin(), line_2.end(), line_2.begin(), std::ptr_fun <int, int>(std::tolower));
	}
	if (line_1.length() != line_2.length()) {
		return false;
	}
	std::vector<std::string> words_1, words_2;
	words_1 = sorted_words(line_to_words(line_1));
	words_2 = sorted_words(line_to_words(line_2));
	if (words_1.size() != words_2.size()) {
		return false;
	}
	std::sort(words_1.begin(), words_1.end());
	std::sort(words_2.begin(), words_2.end());
	
	return words_1 == words_2;
}

void solve_for_sentence(bool case_sens) {
	std::string line_1, line_2;
	std::getline(std::cin, line_1);
	std::getline(std::cin, line_1);
	std::getline(std::cin, line_2);
	if (sentence_anagram(line_1, line_2, case_sens)) {
		std::cout << "anagram\n";
	} else {
		std::cout << "not anagram\n";
	}
}

int main() {
	int type_of_ask, case_sens;
	std::cout << "I need information about type of question: is it only one word or whole sentence?\n1 -- one word\n2 -- whole sentence\n";
	std::cin >> type_of_ask;
	std::cout << "Do you want case sensitive or case insensitive anagrams?\n1 -- case sensitive\n2 -- case insensitive\n";
	std::cin >> case_sens;
	if (type_of_ask == 1) {
		solve_for_word(case_sens == 1);
	} else {
		solve_for_sentence(case_sens == 1);
	}
	return 0;	
}
