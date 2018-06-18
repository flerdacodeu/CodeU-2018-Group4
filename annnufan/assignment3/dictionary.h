#include <set>
#include <string>
#include <algorithm>
#include <iostream>

class dictionary{
	std::set<std::string> words, prefixes;
	
	void compute_all_prefixes() {
		std::string prefix = "";
		for (std::string word : words) {
			prefix = "";
			for (char c : word) {
				prefix += c;
				prefixes.insert(prefix);
			}
		}
	}
	
public:
	dictionary(std::set<std::string> w) : words(w) {
		compute_all_prefixes();
	}

	dictionary() {}

	bool is_word(std::string word) {
		return words.find(word) != words.end();
	}
	
	bool is_prefix(std::string word) {
		return prefixes.find(word) != prefixes.end();	
	}
	
};
