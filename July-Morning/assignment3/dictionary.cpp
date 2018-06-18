#include "dictionary.hpp"

// Add word to dictionary
void Dictionary::add_word (std::string w)
{
    if (w.empty())
        return;
    if (!is_word(w))
        word_set.insert(w);
    for (int i = 1; i <= w.size(); i++)
    {
        std::string p = w.substr(0, i); 
        if (!is_prefix(p))
            prefix_set.insert(p);
    }    
    return;
}

// Check if word is in dictionary
bool Dictionary::is_word (std::string w) 
{
    return !(word_set.find(w) == word_set.end());
}
        
// Check if given string is prefix of at least one word of the dictionary
bool Dictionary::is_prefix (std::string p) 
{
    return !(prefix_set.find(p) == prefix_set.end());
}