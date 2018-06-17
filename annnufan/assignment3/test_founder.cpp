#include <iostream>
#include "codeu_test_lib.h"
#include "founder.cpp"

std::vector<std::vector<char>> ex_grid = {{'a', 'a', 'r'}, {'t', 'c', 'd'}};
std::vector<std::vector<char>> empty_grid;

dictionary ex_dict({"car", "card", "cart", "cat"});
dictionary empty_dict;

std::set<std::string> correct_ans = {"car", "card", "cat"};
std::set<std::string> empty_ans;


void test_from_example() {
	EXPECT_EQ(find_words_from_dict_on_grid(ex_dict, ex_grid), correct_ans);
}

void test_empty_dict() {
	EXPECT_EQ(find_words_from_dict_on_grid(empty_dict, ex_grid), empty_ans);
}

void test_empty_grid() {
	EXPECT_EQ(find_words_from_dict_on_grid(ex_dict, empty_grid), empty_ans);
}

int main() {
	test_empty_grid();
	test_empty_dict();
	test_from_example();
}