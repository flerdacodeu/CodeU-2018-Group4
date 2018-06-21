#include "grid.hpp"
#include "test.hpp"

void test_empty_dictionary() 
{
    Dictionary empty_dict;
    EXPECT_FALSE(empty_dict.is_word("cat"));
    EXPECT_FALSE(empty_dict.is_word(""));
    EXPECT_FALSE(empty_dict.is_prefix("cat"));
    EXPECT_FALSE(empty_dict.is_prefix(""));
}

void test_valid_dictionary()
{
    Dictionary test_dict;
    test_dict.add_words(std::unordered_set<std::string>({"car", "card", "cart", "cat"}));
    EXPECT_FALSE(test_dict.is_word(""));
    EXPECT_FALSE(test_dict.is_word("at"));
    EXPECT_TRUE(test_dict.is_word("cat"));
    EXPECT_TRUE(test_dict.is_word("card"));
    EXPECT_FALSE(test_dict.is_prefix(""));
    EXPECT_FALSE(test_dict.is_prefix("cap"));
    EXPECT_TRUE(test_dict.is_prefix("cat"));
    EXPECT_TRUE(test_dict.is_prefix("car"));    
}

void test_empty_grid() 
{
    LetterGrid empty_grid;
    Dictionary empty_dict;
    Dictionary test_dict;
    test_dict.add_words(std::unordered_set<std::string>({"car", "card", "cart", "cat"}));
    std::unordered_set<std::string> empty_ref_list;
    EXPECT_EQ(empty_grid.find_all_words_from_dictionary (empty_dict), empty_ref_list);
    EXPECT_EQ(empty_grid.find_all_words_from_dictionary (test_dict), empty_ref_list);
}

void test_init_grid()
{
    LetterGrid test_grid;
    std::vector<std::string> empty_init_rows;
    EXPECT_FALSE(test_grid.init(empty_init_rows));
    std::vector<std::string> invalid_init_rows_1{"", "tcd"};
    EXPECT_FALSE(test_grid.init(invalid_init_rows_1));
    std::vector<std::string> invalid_init_rows_2{"aar", ""};
    EXPECT_FALSE(test_grid.init(invalid_init_rows_2));
    std::vector<std::string> invalid_init_rows_3{"a", "tcd"};
    EXPECT_FALSE(test_grid.init(invalid_init_rows_3));
    std::vector<std::string> valid_init_rows{"aar", "tcd"};
    EXPECT_TRUE(test_grid.init(valid_init_rows));
}

void test_valid_grid()
{
    LetterGrid test_grid;
    Dictionary empty_dict;
    Dictionary test_dict;
    test_dict.add_words(std::unordered_set<std::string>({"car", "card", "cart", "cat"}));
    std::unordered_set<std::string> empty_ref_list;
    std::unordered_set<std::string> ref_list{"car", "card", "cat"};
    std::vector<std::string> init_rows{"aar", "tcd"};
    test_grid.init(init_rows);
    EXPECT_EQ(test_grid.find_all_words_from_dictionary (empty_dict), empty_ref_list);
    EXPECT_EQ(test_grid.find_all_words_from_dictionary (test_dict), ref_list);
}

void test_grid_for_cell_revisiting()
{
    LetterGrid test_grid;
    Dictionary test_dict;
    test_dict.add_words(std::unordered_set<std::string>({"car", "card", "cart", "cat", "carat", "carr", "cata"}));
    std::unordered_set<std::string> ref_list{"car", "card", "cat", "cata"};
    std::vector<std::string> init_rows{"aar", "tcd"};
    test_grid.init(init_rows);
    EXPECT_EQ(test_grid.find_all_words_from_dictionary (test_dict), ref_list);
}

int main ()
{
    // Test dictionary class
    test_empty_dictionary();
    test_valid_dictionary();
    // Test grid class
    test_empty_grid();
    test_init_grid();
    test_valid_grid();
    test_grid_for_cell_revisiting();
    return 0;
}
