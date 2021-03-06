#include "dictionary.h"
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class words_finder {
	dictionary dict;
	std::vector<std::vector<char>> grid;
	std::set<std::string> words_from_grid;
	bool find_before;
	int n, m;
	std::vector<std::pair<int, int>> moves;

	void go_from_cell(int i, int j, std::vector<std::vector<bool>> used, std::string word) {
		word += grid[i][j];
		used[i][j] = true;
		if (!dict.is_prefix(word)) {
			return;
		}
		if (dict.is_word(word)) {
			words_from_grid.insert(word);
		}
		for (const auto& move : moves) {
			int i1 = move.first + i;
			int j1 = move.second + j;
			if (0 <= i1 && i1 < n && 0 <= j1 && j1 < m && !used[i1][j1]) {
				go_from_cell(i1, j1, used, word);
			}
		}
	}

public:
	
	words_finder(dictionary d, std::vector<std::vector<char>> g) : dict(d), grid(g), find_before(false) {
		words_from_grid.clear();
		n = (int)grid.size();
		m = (n != 0) ? (int)grid[0].size() : 0;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i != 0 || j != 0) {
					moves.push_back({i, j});
				}
			}
		}
	}
	
	std::set<std::string> find() {
		if (find_before) {
			return words_from_grid;
		}
		find_before = true;
		if (n == 0 || m == 0) {
			return words_from_grid;
		}
		std::vector<std::vector<bool>> used(n, std::vector<bool>(m, false));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				go_from_cell(i, j, used, "");
			}
		}
		return words_from_grid;
	}
	
};


std::set<std::string> find_words_from_dict_on_grid(dictionary dict, std::vector<std::vector<char>> grid) {
	words_finder fnd(dict, grid);
	return fnd.find();	
}


