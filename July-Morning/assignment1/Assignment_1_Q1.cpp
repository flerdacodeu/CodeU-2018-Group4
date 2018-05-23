#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <locale> 
#include <unordered_map>
#include <algorithm>

// Check if two strings are anagrams (case sensitive algorithm)
// Return value:
// true - if strings are anagrams 
// false - if strings are not anagrams or at least one string is empty 
bool Is_Anagram (std::string s1, std::string s2)
{
    if ((s1.size() == 0) || (s2.size() == 0))
        return false;
    if (s1.size() != s2.size())
        return false;
    std::unordered_map<char, int> symbol_histogram;
    for (char sym : s1)
        symbol_histogram[sym]++;    
    for (char sym : s2)
        symbol_histogram[sym]--;    
    for (const auto& symbol_entry : symbol_histogram) 
        if (symbol_entry.second != 0)
            return false;
    return true;        
}

// Check if two strings are anagrams (case insensitive algorithm)
// Return value:
// true - if strings are anagrams 
// false - if strings are not anagrams or at least one string is empty
bool Is_Case_Insensitive_Anagram (std::string s1, std::string s2)
{
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    return Is_Anagram(s1, s2);
}

// Split sentence into words
// For now only whitespace is considered as separator 
// Empty words are ommited
void Split_Sentence_Into_Words (std::string s, std::vector<std::string>& s_words)
{
    std::istringstream iss(s);
    std::string next_s_word;
    while(iss >> next_s_word)
        s_words.push_back(next_s_word);
}

// Check if two sentences consist of anagrams (case sensitive algorithm)
// Return value:
// true - if sentences consist of anagrams 
// false - if sentences do not consist of anagrams or at least one sentence is empty
bool Is_Set_Of_Anagrams (std::string s1, std::string s2)
{
    std::vector<std::string> s1_words;
    std::vector<std::string> s2_words;
    Split_Sentence_Into_Words (s1, s1_words);
    Split_Sentence_Into_Words (s2, s2_words);
    if ((s1_words.size() == 0) || (s2_words.size() == 0))
        return false;
    if (s1_words.size() != s2_words.size()) 
        return false;
    for (auto word1 : s1_words)
    {
        bool word1_is_anagram = false;
        for (auto& word2 : s2_words)
        {
            if (Is_Anagram(word1, word2)) 
            {
                word2 = " ";
                word1_is_anagram = true;
                break;
            }
        }
        if (!word1_is_anagram)
            return false;
    }
    return true;
}

// Run test with given input strings and print result (case sensitive algorithm) 
void Test_Is_Anagram (std::string s1, std::string s2)
{
    if (Is_Anagram(s1, s2))
        std::cout << s1 << " and " << s2 << " are anagrams." << std::endl;
    else
        std::cout << s1 << " and " << s2 << " are not anagrams." << std::endl;
    return;    
}

// Run test with given input strings and print result (case insensitive algorithm) 
void Test_Is_Case_Insensitive_Anagram (std::string s1, std::string s2)
{
    if (Is_Case_Insensitive_Anagram(s1, s2))
        std::cout << s1 << " and " << s2 << " are anagrams." << std::endl;
    else
        std::cout << s1 << " and " << s2 << " are not anagrams." << std::endl;
    return;    
}

// Run test with given input sentences and print result (case sensitive algorithm) 
void Test_Is_Set_Of_Anagrams (std::string s1, std::string s2)
{
    if (Is_Set_Of_Anagrams(s1, s2))
        std::cout << s1 << " and " << s2 << " consist of anagrams." << std::endl;
    else
        std::cout << s1 << " and " << s2 << " do not consist of anagrams." << std::endl;
    return;    
}

int main ()
{
    std::cout << " **** Examples from assignment doc ****" << std::endl;
    Test_Is_Anagram ("listen", "silent");
    Test_Is_Anagram ("triangle", "integral");
    Test_Is_Anagram ("apple", "pabble");
    std::cout << " **** Tests with empty input **** " << std::endl;
    Test_Is_Anagram ("", "listen");
    Test_Is_Anagram ("silent", "");
    Test_Is_Anagram ("", "");
    std::cout << " **** General tests for correctness **** " << std::endl;
    Test_Is_Anagram ("late", "late");
    Test_Is_Anagram ("late", "Late");
    Test_Is_Anagram ("late", "tale");
    Test_Is_Anagram ("late", "TALE");
    Test_Is_Anagram ("late", "talk");
    Test_Is_Anagram ("late", "tall");
    Test_Is_Anagram ("late", "ta;k");
    Test_Is_Anagram ("late", "t.lk");
    std::cout << " **** Tests for case insensitive algorihtm **** " << std::endl;
    Test_Is_Case_Insensitive_Anagram ("", "listen");
    Test_Is_Case_Insensitive_Anagram ("silent", "");
    Test_Is_Case_Insensitive_Anagram ("", "");
    Test_Is_Case_Insensitive_Anagram ("late", "late");
    Test_Is_Case_Insensitive_Anagram ("late", "Late");
    Test_Is_Case_Insensitive_Anagram ("late", "tale");
    Test_Is_Case_Insensitive_Anagram ("late", "TALE");
    Test_Is_Case_Insensitive_Anagram ("late", "talk");
    Test_Is_Case_Insensitive_Anagram ("Late", "taLl");
    Test_Is_Case_Insensitive_Anagram ("late", "ta;k");
    Test_Is_Case_Insensitive_Anagram ("late", "t.lk");
    std::cout << " **** Tests for sentences **** " << std::endl;
    Test_Is_Set_Of_Anagrams ("", "listen to me");
    Test_Is_Set_Of_Anagrams ("listen to me", "");
    Test_Is_Set_Of_Anagrams ("", "");
    Test_Is_Set_Of_Anagrams ("hello world", "lehho dworl");
    Test_Is_Set_Of_Anagrams ("eleven plus two", "twelve plus one");
    Test_Is_Set_Of_Anagrams ("listen me me", "listen me to");
    Test_Is_Set_Of_Anagrams ("listen me me", "listen me me");
    Test_Is_Set_Of_Anagrams ("listen to me", "listen to me");
    Test_Is_Set_Of_Anagrams ("listen  to me", "listen to me");
    Test_Is_Set_Of_Anagrams ("listen to me", " listen to me");
    Test_Is_Set_Of_Anagrams ("listen to me ", " listen to me");
    Test_Is_Set_Of_Anagrams ("listen to me", "listen me to");
    Test_Is_Set_Of_Anagrams ("listen t me", "t em silent");
    Test_Is_Set_Of_Anagrams ("LiSten t me", "SiLent t me");
    Test_Is_Set_Of_Anagrams ("silence in the library", "teh lisence ni brilary");
    return 0;
}
