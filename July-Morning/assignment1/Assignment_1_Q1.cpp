#include <iostream>
#include <string>
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
    std::unordered_map<char, int> symbol_counter;
    for (auto& sym : s1)
        symbol_counter[sym]++;    
    for (auto& sym : s2)
        symbol_counter[sym]--;    
    for (auto& sym : s2)
        if (symbol_counter[sym] != 0)
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
    return (Is_Anagram(s1, s2));
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
    return 0;
}
