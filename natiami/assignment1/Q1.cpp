#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<array> 

using namespace std;

int letterToIndex(char letter){
	// substracting 65 to start indexing from 0, integer value of A symbol is 65
	return int(letter) - 65; 
}

int indexToLowerCase(int index){
	return index + ('a' - 'A');
}

bool checkAllZeros(vector<int> letters_histogram){
	return all_of(letters_histogram.begin(), letters_histogram.end(), [](int letter_count){return letter_count == 0; });
}

bool checkAnagrams(string str1, string str2, bool caseSensitive){
	int nr_symbols = 58; // number of symbols from A to z
	vector<int> letters_histogram(nr_symbols, 0);

	if (str1.length() != str2.length()) return false; // Different size words cannot be anagrams

	for (size_t i = 0; i < str1.length(); i++)
	{
		letters_histogram[letterToIndex(str1[i])]++;
		letters_histogram[letterToIndex(str2[i])]--;
	}

	// Case insensitive anagrams check
	if (!caseSensitive){
		const int A_index = 0;
		const int Z_index = 26; // english language has 26 letters

		for (size_t i = A_index; i < Z_index; i++){
			if (letters_histogram[i] != 0){
				if (abs(letters_histogram[i]) != abs(letters_histogram[indexToLowerCase(i)]))
					return false;
				else{
					letters_histogram[indexToLowerCase(i)] = 0;
					letters_histogram[i] = 0;
				}
			}
		}
		return checkAllZeros(letters_histogram);
	}

	//Case sensitive anagram check
	return checkAllZeros(letters_histogram);
}

int main(){

	// Input
	string str1, str2;
	bool caseSensitive = true;

	cout << "Input 2 words or sentences" << endl;
	cin >> str1 >> str2;

	cout << "Input 1 to check for case sensitivity 0 otherwise" << endl;
	cin >> caseSensitive;

	// check for anagrams
	cout << checkAnagrams(str1, str2, caseSensitive) << endl;

	return 0;
}
