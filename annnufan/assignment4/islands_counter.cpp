#include <vector>
#include <utility>

class islands_counter {
	std::vector<std::vector<bool>> island_map;
	std::vector<std::pair<int, int>> moves;
	int n, m;
	int islands;
	bool is_count;

	void dfs(int i, int j) {
		island_map[i][j] = false;

		for (const auto& move : moves) {
			int i1 = move.first + i;
			int j1 = move.second + j;
			if (0 <= i1 && i1 < n && 0 <= j1 && j1 < m && island_map[i1][j1]) {
				dfs(i1, j1);
			}
		}
	}

public:
	islands_counter(std::vector<std::vector<bool>> i_m) : island_map(i_m) {
		n = island_map.size();
		m = (n != 0) ? island_map[0].size() : 0;
		islands = 0;
		is_count = false;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if ((i == 0) ^ (j == 0)) {
					moves.push_back({i, j});
				}
			}
		}
	}

	int count() {
		if (is_count) {
			return islands;
		}
		is_count = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (island_map[i][j]) {
					dfs(i, j);
					islands++;
				}
			}
		}
		return islands;
	}

};

int count_islands_on_map(std::vector<std::vector<bool>> island_map) {
	islands_counter counter(island_map);
	return counter.count();	
}