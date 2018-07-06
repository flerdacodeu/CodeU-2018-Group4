#include <vector>
#include <utility>

class islands_counter {
	std::vector<std::vector<bool>> island_map;
	std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int n, m;
	int island_count;
	bool already_count;

	void mark_island(int i, int j) {
		island_map[i][j] = false;

		for (const auto& move : moves) {
			int i1 = move.first + i;
			int j1 = move.second + j;
			if (0 <= i1 && i1 < n && 0 <= j1 && j1 < m && island_map[i1][j1]) {
				mark_island(i1, j1);
			}
		}
	}

public:
	islands_counter(std::vector<std::vector<bool>>& i_m) : island_map(i_m), n(island_map.size()), m((n != 0) ? island_map[0].size() : 0), island_count(0), already_count(false) {}

	int count() {
		if (already_count) {
			return island_count;
		}
		already_count = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (island_map[i][j]) {
					mark_island(i, j);
					island_count++;
				}
			}
		}
		return island_count;
	}

};

int count_islands_on_map(std::vector<std::vector<bool>> island_map) {
	islands_counter counter(island_map);
	return counter.count();	
}