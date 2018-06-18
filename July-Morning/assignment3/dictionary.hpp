#include <string>
#include <unordered_set>

class Dictionary 
{
    private:
        std::unordered_set<std::string> word_set;
        std::unordered_set<std::string> prefix_set;
        
    public:
        Dictionary() {}
        
        // Add word to dictionary
        void add_word (std::string w);
        
        // Check if word is in dictionary
        bool is_word (std::string w);
        
        // Check if given string is prefix of at least one word of the dictionary
        bool is_prefix (std::string p);
};