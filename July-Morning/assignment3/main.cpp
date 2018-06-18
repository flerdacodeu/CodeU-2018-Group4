#include<vector>
#include "dictionary.hpp"
#include "test.hpp"

// Case sensitive: a and A are different letters!
class LetterGrid 
{
    private:
        std::vector<std::vector<char> > grid;
        int width;
        int height;
        
        // Find all words starting from given position in grid 
        void find_words_from_position (Dictionary dict, std::vector<std::string>& found_words, std::vector<std::vector<bool> > is_cell_visited, std::string cur_word, int x, int y)
        {
            if ((x < 0) || (x >= width))
                return;
            if ((y < 0) || (y >= height))
                return;
            if (is_cell_visited[y][x])
                return;    
            cur_word += grid[y][x];
            is_cell_visited[y][x] = true;
            if (dict.is_word(cur_word))
            {
                bool is_already_found = false;
                for (std::string w : found_words)
                    if (w == cur_word)
                        is_already_found = true;
                if (!is_already_found)
                    found_words.push_back(cur_word);
            }    
            if (dict.is_prefix(cur_word)) 
            {
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x + 1, y - 1);
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x, y - 1);
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x - 1, y - 1);
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x + 1, y);
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x - 1, y);
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x + 1, y + 1);
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x, y + 1);
                find_words_from_position (dict, found_words, is_cell_visited, cur_word, x - 1, y + 1);
            }
            return;
        }
        
         
    public:
        LetterGrid() 
        {
            width = 0;
            height = 0;
        }
        
        // Initialize grid
        bool init (int w, int h, std::vector<std::string> letter_rows) 
        {
            if ((h == 0) || (w == 0))
                return false;
            if (letter_rows.size() != h)
                return false;
            for (int j = 0; j < h; j++)
            {
                if (letter_rows[j].size() != w)
                {
                    for (auto row : grid)
                        row.clear();
                    grid.clear();    
                    return false;
                }    
                std::vector<char> row;
                for (char letter : letter_rows[j])
                    row.push_back(letter);
                grid.push_back(row);    
            }
            width = w;
            height = h;
            return true;
        }
        
        // Find all words that can be found in grid
        // Empty grid or dictionary are considered as valid inputs 
        // Empty vector is returned in these cases
        // Note that non-empty input vector will be cleared up, not appended
        void find_all_words_from_dictionary (Dictionary dict, std::vector<std::string>& words)
        {
            words.clear();
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    std::string empty_word("");
                    std::vector<std::vector<bool> > is_cell_visited(height, std::vector<bool>(width, false));
                    find_words_from_position (dict, words, is_cell_visited, empty_word, i, j);
                }
            }    
        }
};

int main ()
{
    // Test dictionary class
    Dictionary empty_dict;
    EXPECT_FALSE(empty_dict.is_word("cat"));
    EXPECT_FALSE(empty_dict.is_word(""));
    EXPECT_FALSE(empty_dict.is_prefix("cat"));
    EXPECT_FALSE(empty_dict.is_prefix(""));
    Dictionary test_dict;
    test_dict.add_word("car");
    test_dict.add_word("card");
    test_dict.add_word("cart");
    test_dict.add_word("cat");
    EXPECT_FALSE(test_dict.is_word(""));
    EXPECT_FALSE(test_dict.is_word("at"));
    EXPECT_TRUE(test_dict.is_word("cat"));
    EXPECT_TRUE(test_dict.is_word("card"));
    EXPECT_FALSE(test_dict.is_prefix(""));
    EXPECT_FALSE(test_dict.is_prefix("cap"));
    EXPECT_TRUE(test_dict.is_prefix("cat"));
    EXPECT_TRUE(test_dict.is_prefix("car"));
    // Test grid class
    std::vector<std::string> word_list;
    std::vector<std::string> ref_list;
    LetterGrid empty_grid;
    empty_grid.find_all_words_from_dictionary (empty_dict, word_list);
    EXPECT_EQ(word_list, ref_list);
    empty_grid.find_all_words_from_dictionary (test_dict, word_list);
    EXPECT_EQ(word_list, ref_list);
    LetterGrid test_grid;
    std::vector<std::string> init_rows;
    EXPECT_FALSE(test_grid.init(0, 0, init_rows));
    EXPECT_FALSE(test_grid.init(1, 0, init_rows));
    EXPECT_FALSE(test_grid.init(0, 1, init_rows));
    init_rows.push_back("aar");
    EXPECT_FALSE(test_grid.init(2, 1, init_rows));
    EXPECT_FALSE(test_grid.init(3, 2, init_rows));
    init_rows.push_back("tcd");
    EXPECT_FALSE(test_grid.init(3, 1, init_rows));
    EXPECT_FALSE(test_grid.init(2, 2, init_rows));
    EXPECT_TRUE(test_grid.init(3, 2, init_rows));
    test_grid.find_all_words_from_dictionary (empty_dict, word_list);
    EXPECT_EQ(word_list, ref_list);
    ref_list.push_back("car");
    ref_list.push_back("card");
    ref_list.push_back("cat");
    test_grid.find_all_words_from_dictionary (test_dict, word_list);
    EXPECT_EQ(word_list, ref_list);
    test_dict.add_word("carat");
    test_dict.add_word("carr");
    test_dict.add_word("cata");
    ref_list.push_back("cata");
    test_grid.find_all_words_from_dictionary (test_dict, word_list);
    EXPECT_EQ(word_list, ref_list);
    return 0;
}