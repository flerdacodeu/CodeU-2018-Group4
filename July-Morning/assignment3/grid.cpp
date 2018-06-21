#include "grid.hpp"

LetterGrid::LetterGrid() 
{
    width = 0;
    height = 0;
}

// Delete all data from grid
void LetterGrid::clear_all ()
{
    for (auto row : grid)
        row.clear();
    grid.clear(); 
    width = 0;
    height = 0;
}

// Check if coordinates are valid for current grid
bool LetterGrid::is_xy_valid (int x, int y)
{
    if ((x < 0) || (x >= width))
        return false;
    if ((y < 0) || (y >= height))
        return false;
    return true;    
}

std::unordered_set<std::string> LetterGrid::find_words_from_position (const Dictionary& dict, std::vector<std::vector<bool> > is_cell_visited, std::string cur_word, int x, int y)
{
    std::unordered_set<std::string> words_from_pos;
    if (!is_xy_valid(x, y))
        return words_from_pos;
    if (is_cell_visited[y][x])
        return words_from_pos;    
    cur_word += grid[y][x];
    is_cell_visited[y][x] = true;
    if (dict.is_word(cur_word))
        words_from_pos.insert(cur_word);
    if (dict.is_prefix(cur_word)) 
    {
        for (int dx : {-1, 0, 1}) 
        {
            for (int dy : {-1, 0, 1}) 
            {
                if (dx == 0 && dy == 0) 
                    continue;
                std::unordered_set<std::string> dxdy_words = find_words_from_position (dict, is_cell_visited, cur_word, x + dx, y + dy);
                words_from_pos.insert(dxdy_words.begin(), dxdy_words.end());
            }
        }    
    }
    return words_from_pos;
}
        
// Initialize grid
bool LetterGrid::init (std::vector<std::string> letter_rows) 
{
    height = letter_rows.size();
    if (height == 0)
        return false;
    width = letter_rows[0].size();    
    for (int j = 0; j < height; j++)
    {
        if (letter_rows[j].size() != width)
        {
            clear_all();
            return false;
        }    
        grid.emplace_back(letter_rows[j].begin(), letter_rows[j].end());    
    }
    return true;
}
        
// Find all words that can be found in grid
// Empty grid or dictionary are considered as valid inputs 
// Empty vector is returned in these cases
// Note that non-empty input vector will be cleared up, not appended
std::unordered_set<std::string> LetterGrid::find_all_words_from_dictionary (const Dictionary& dict)
{
    std::unordered_set<std::string> found_words;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            std::string empty_word("");
            std::vector<std::vector<bool> > is_cell_visited(height, std::vector<bool>(width, false));
            std::unordered_set<std::string> words_from_ij = find_words_from_position (dict, is_cell_visited, empty_word, i, j);
            found_words.insert(words_from_ij.begin(), words_from_ij.end());
        }
    }
    return found_words;
}