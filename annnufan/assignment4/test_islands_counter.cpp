#include "codeu_test_lib.h"
#include "islands_counter.cpp"
#include <iostream>

void test_for_example() {
	std::vector<std::vector<bool>> ex_map({{false, true, false, true}, {true, true, false, false}, {false, false, true, false}, {false, false, true, false}});
	int ans = 3;
	EXPECT_EQ(count_islands_on_map(ex_map), ans);
}

void test_empty_case() {
	std::vector<std::vector<bool>> empty_map({});
	int ans = 0;
	EXPECT_EQ(count_islands_on_map(empty_map), ans);
}

void test_empty_1_case() {
	std::vector<std::vector<bool>> empty_map({{}, {}, {}});
	int ans = 0;
	EXPECT_EQ(count_islands_on_map(empty_map), ans);
}

void test_map_without_islands() {
	std::vector<std::vector<bool>> map_without_islands({{false, false}, {false, false}, {false, false}});
	int ans = 0;
	EXPECT_EQ(count_islands_on_map(map_without_islands), ans);
}

void test_one_big_island() {
	std::vector<std::vector<bool>> map_with_one_islands({{true, true, true}, {true, true, true}});
	int ans = 1;
	EXPECT_EQ(count_islands_on_map(map_with_one_islands), ans);
}

void test_one_hard_island() {
	std::vector<std::vector<bool>> map_1({{false, true, false, true}, {true, true, false, true}, {true, false, true, true}, {true, true, true, false}});
	int ans = 1;
	EXPECT_EQ(count_islands_on_map(map_1), ans);
}

int main() {
	test_for_example();
	test_empty_case();
	test_empty_1_case();
	test_map_without_islands();
	test_one_big_island();
	test_one_hard_island();
}