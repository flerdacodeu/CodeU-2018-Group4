#include <vector>
#include <iostream>
#include "dictionary.hpp"

// Case sensitive: a and A are different letters!
class LetterGrid 
{
    private:
        std::vector<std::vector<char> > grid;
        int width;
        int height;
        
        // Delete all data from grid
        void clear_all ();
        
        // Check if coordinates are valid for current grid
        bool is_xy_valid (int x, int y);
        
        // Find all words starting from given position in grid 
        std::unordered_set<std::string> find_words_from_position (const Dictionary& dict, std::vector<std::vector<bool> > is_cell_visited, std::string cur_word, int x, int y);
    
    public:
        LetterGrid();
        
        // Initialize grid
        bool init (std::vector<std::string> letter_rows); 
        
        // Find all words that can be found in grid
        // Empty grid or dictionary are considered as valid inputs 
        // Empty vector is returned in these cases
        // Note that non-empty input vector will be cleared up, not appended
        std::unordered_set<std::string> find_all_words_from_dictionary (const Dictionary& dict);
};