/*  all tests methods return true when the test passes, false if fails */

// -------------- Test split_to_words --------------

bool test_num_of_words(string sentence, int expected_n_words){
  vector<string> words = split_to_words(sentence);
  return words.size() == expected_n_words;
}

bool test_output_words(string sentence, vector<string> expected_result){
  vector<string> words = split_to_words(sentence);
  return words == expected_result;
}

bool test_split_to_words(){
  string test_str = "This, sentence    contains. 5?!?! words";
  vector<string> expected_result = {"This","sentence","contains","5","words"};
  return test_num_of_words && test_output_words;
}

// -------------- Test lower_each_string --------------
bool test_strings_were_lowered(vector<string> input_vec, vector<string> expected_result){
  bool equal_before = input_vec == expected_result;
  lower_each_string(input_vec);
  bool equal_after = input_vec == expected_result;
  return !equal_before && equal_after;
}

bool test_lower_each_string(){
  vector<string> test_vec = {"ABC","aB6Kmf","983","","qazwsx"};
  vector<string> expected_result = {"abc","ab6kmf","983","","qazwsx"};
  return test_strings_were_lowered(test_vec,expected_result);
}

// -------------- Test sort_each_string --------------
bool test_strings_were_sorted(vector<string> input_vec, vector<string> expected_result){
  bool equal_before = input_vec == expected_result;
  sort_each_string(input_vec);
  bool equal_after = input_vec == expected_result;
  return !equal_before && equal_after;
}

bool test_sort_each_string(){
  vector<string> test_vec = {"aABb","9za","983","","XPXF"};
  vector<string> expected_result = {"ABab","9az","389","","FPXX"};
  return test_strings_were_sorted(test_vec,expected_result);
}

// -------------- Test are_anagrams --------------
bool test_words_anagrams(){
  string word1 = "Listen";
  string word2 = "siLent";
  string word3 = "Nestil";
  bool case_sensitive1 = are_anagrams(word1, word2, true); //expected true
  bool case_sensitive2 = are_anagrams(word1, word3, true); //expected false
  bool case_insensitive1 = are_anagrams(word1, word2, false); //expected true
  bool case_insensitive2 = are_anagrams(word2, word3, false); //expected true
  return case_sensitive1 && !case_sensitive2 && case_insensitive1 && case_insensitive2;
}

bool test_words_not_anagrams(){
  string word1 = "apple";
  string word2 = "pAbble";
  bool case_sensitive = are_anagrams(word1, word2, true); //expected false
  bool case_insensitive = are_anagrams(word1, word2, false); //expected false
  return !case_sensitive && !case_insensitive;
}

bool test_are_anagrams_on_words(){
  bool test_anagrams = test_words_anagrams();
  bool test_not_anagrams = test_words_not_anagrams();
  return test_anagrams && test_not_anagrams;
}

bool test_sentences_anagrams(){
  string sentence1 = "Good Morning, World";
  string sentence2 = "roWld. ngnMoir?doGo!";
  string sentence3 = "doog mornign wordl!";
  bool case_sensitive1 = are_anagrams(sentence1, sentence2, true); //expected true
  bool case_sensitive2 = are_anagrams(sentence1, sentence3, true); //expected false
  bool case_insensitive1 = are_anagrams(sentence1, sentence2, false); //expected true
  bool case_insensitive2 = are_anagrams(sentence2, sentence3, false); //expected true
  return case_sensitive1 && !case_sensitive2 && case_insensitive1 && case_insensitive2;
}

bool test_sentences_not_anagrams(){
  string sentence1 = "tale as old as TIME....";
  string sentence2 = "old tale as TIME....";
  string sentence3 = "song as old as rime?";
  bool case_sensitive = are_anagrams(sentence1, sentence2, true); //expected false
  bool case_insensitive1 = are_anagrams(sentence1, sentence2, false); //expected false
  bool case_insensitive2 = are_anagrams(sentence1, sentence3, false); //expected false
  return !case_sensitive && !case_insensitive1 && !case_insensitive2;
}

bool test_are_anagrams_on_sentences(){
  bool test_anagrams = test_sentences_anagrams();
  bool test_not_anagrams = test_sentences_not_anagrams();
  return test_anagrams && test_not_anagrams;
}

bool test_are_anagrams(){
  bool test_on_words = test_are_anagrams_on_words();
  bool test_on_sentences = test_are_anagrams_on_sentences();
  return test_on_words && test_on_sentences;
}
