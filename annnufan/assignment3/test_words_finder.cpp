#include <iostream>
#include "codeu_test_lib.h"
#include "words_finder.cpp"

void test_from_example() {
	dictionary ex_dict({"car", "card", "cart", "cat"});
	std::vector<std::vector<char>> ex_grid({{'a', 'a', 'r'}, {'t', 'c', 'd'}});
	std::set<std::string> ex_ans({"car", "card", "cat"});

	EXPECT_EQ(find_words_from_dict_on_grid(ex_dict, ex_grid), ex_ans);
}

void test_empty_dict() {
	dictionary empty_dict;
	std::vector<std::vector<char>> ex_grid({{'a', 'a', 'r'}, {'t', 'c', 'd'}});
	std::set<std::string> empty_ans;

	EXPECT_EQ(find_words_from_dict_on_grid(empty_dict, ex_grid), empty_ans);
}

void test_empty_grid() {
	dictionary ex_dict({"car", "card", "cart", "cat"});
	std::vector<std::vector<char>> empty_grid;
	std::set<std::string> empty_ans;

	EXPECT_EQ(find_words_from_dict_on_grid(ex_dict, empty_grid), empty_ans);
}

void test_double_usage_cell() {
	dictionary dict_1({"tree", "cart", "bee", "bed", "cider", "beer", "teer", "dinner", "baobab", "vine", "tear", "horse", "bob"});
	std::vector<std::vector<char>> grid_1({{'a', 'o', 'b', 'e', 'r'}, {'c', 'a', 'd', 'e', 't'}, {'b', 'i', 'v', 'i', 'n'}});
	std::set<std::string> ans_1({"tree", "bee", "bed", "cider", "beer", "teer", "vine"});

	EXPECT_EQ(find_words_from_dict_on_grid(dict_1, grid_1), ans_1);
}

int main() {
	test_empty_grid();
	test_empty_dict();
	test_from_example();
	test_double_usage_cell();
}