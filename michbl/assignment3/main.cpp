#include <iostream>
#include "Dictionary.hpp"
#include "Grid.hpp"
#include "codeu_test_lib.h"

int main() {
    vector<char> g = {'A', 'A', 'R', 'T', 'C', 'D'};
    Grid grid(g, 2, 3);

    // test assignment example
    vector<string> words = {"CAR", "CARD", "CART", "CAT"};
    Dictionary dict1(words);
    set<string> result = dict1.wordSearch(grid);

    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.find("CAR") != result.end());
    EXPECT_TRUE(result.find("CARD") != result.end());
    EXPECT_TRUE(result.find("CAT") != result.end());

    // test empty word isn't found
    words = {"CAR", "CARD", "CART", "CAT", ""};
    Dictionary dict2(words);
    result = dict2.wordSearch(grid);

    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.find("CAR") != result.end());
    EXPECT_TRUE(result.find("CARD") != result.end());
    EXPECT_TRUE(result.find("CAT") != result.end());

    // test no word can be found
    words = {"HOUSE", "BIT", "FLUSH"};
    Dictionary dict3(words);
    result = dict3.wordSearch(grid);
    EXPECT_EQ(result.size(), 0);

    // test empty dictionary
    words = {};
    Dictionary dict4(words);
    result = dict4.wordSearch(grid);
    EXPECT_EQ(result.size(), 0);

    return 0;
}