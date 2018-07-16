#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class WordDependencyGraph{
	unordered_map<char, vector<char>> graph;
public:
	WordDependencyGraph(vector<string>& dictionary) {
		generateGraph(dictionary);
	}
	
	vector<char> topologicalSort(){
		vector<char> lexicographicalOrder;

		set<char> visited;
		
		for (unordered_map<char, vector<char>>::iterator it = graph.begin(); it != graph.end(); it++) {
			char currentChar = it->first;
			if (visited.find(currentChar)==visited.end())
				topologicalSortUtil(currentChar, visited, lexicographicalOrder);
		}

		return reverseOrder(lexicographicalOrder);
	}

private:

	void topologicalSortUtil(char key, set<char>& visited, vector<char>& lexicographicalOrder) {
		visited.insert(key);
		vector<char> children = graph[key];

		for (char ch : children) {
			if (visited.find(ch) == visited.end())
				topologicalSortUtil(ch, visited, lexicographicalOrder);
		}

		lexicographicalOrder.push_back(key);
	}

	vector<char> reverseOrder(vector<char>& lexicographicalOrder) {
		vector<char> lexicographicalOrderReveresed;

		for (int i = lexicographicalOrder.size() - 1; i >= 0; i--)
			lexicographicalOrderReveresed.push_back(lexicographicalOrder[i]);

		return lexicographicalOrderReveresed;
	}

	void generateGraph(vector<string>& dictionary) {
		int maxWordLength = getMaxLength(dictionary);

		for (int s = 0; s < maxWordLength; s++) {
			for (int i = 0; i < dictionary.size(); i++) {
				string word1 = dictionary[i];
				for (int j = i + 1; j < dictionary.size(); j++) {
					string word2 = dictionary[j];

					if (word1.length() > s && word2.length() > s && haveTheSamePrefix(word1, word2, s)) {
						char ch1 = word1[s];
						char ch2 = word2[s];

						if (ch1 != ch2) {
							// ch1 should be ordered before ch2 => ch2 is dependent on ch1
							// insert ch2 as a child of ch1 node if it is not already inserted
							vector<char>& childrenOfChar1 = graph[ch1];

							if (childrenOfChar1.size() > 0) {
								// check if ch2 is already inserted as a child of ch1
								if (!containsChar(childrenOfChar1, ch2)) {
									childrenOfChar1.push_back(ch2);
								}
							}
							else {
								childrenOfChar1.push_back(ch2);
							}
						}
					}
				}
			}
		}
		// iteration for the last word in the dictionary
		string word1 = dictionary[dictionary.size()-1];
		for (char ch : word1) {
			// if graph does not contain pair with the first element as letter ch, letter ch will be inserted with an empty children list,
			// by just referencing it.
			vector<char> children = graph[ch];
		}
	}

	bool containsChar(vector<char>& chars, char ch2) {
		for (char c : chars) {
			if (c == ch2)
				return true;
		}

		return false;
	}

	bool haveTheSamePrefix(string& word1, string word2, int position) {
		return word1.substr(0, position).compare(word2.substr(0, position)) == 0;
	}

	int getMaxLength(vector<string>& dictionary) {
		int maxLength = 0;
		for (string& word : dictionary) {
			if (word.length() > maxLength)
				maxLength = word.length();
		}

		return maxLength;
	}
};

