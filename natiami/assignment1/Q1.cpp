#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <algorithm>
#include <array> 

using namespace std;

bool checkAnagrams(string str1, string str2, bool caseSensitive){
	vector<int> letters(52, 0); // array for letters

	if (str1.length() != str2.length()) return false; // if size differs return false right away

	for (size_t i = 0; i < str1.length(); i++)
	{
		letters[int(str1[i]) - 65]++;
		letters[int(str2[i]) - 65]--;
	}

	// If algorithm is not case sensitive
	if (!caseSensitive){
		for (size_t i = 0; i < letters.size()/2; i++)
			if (letters[i] != 0 && letters[i + 32] == 0) return false;
		return true;
	}

	// If algorithm is case sensitive
	return !any_of(letters.begin(), letters.end(), [](int i){return i!=0; });
}

int main(){

	// Input
	string str1, str2;
	bool caseSensitive = true;

	cout << "Input 2 words or sentences"<<endl;
	cin >> str1 >> str2;

	cout << "Input 1 to check for case sensitivity 0 otherwise" << endl;
	cin >> caseSensitive;

	// check for anagrams
	cout << checkAnagrams(str1, str2, caseSensitive) << endl;

	return 0;
}