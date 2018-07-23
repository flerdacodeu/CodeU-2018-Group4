#ifndef TEST__ALPHABETFROMDICTIONARY_HPP
#define TEST__ALPHABETFROMDICTIONARY_HPP

#include "AlphabetFromDictionary.hpp"
#include "codeu_test_lib.h"

class TestAlphabetFromDictionary {
public:
	void runAllTests();

private:
	void testEmptyDictionary();
	void testValidDictionary();
	void testValidDictionaryWithNonLatinLetters();
	void testValidDictionaryWithEmptyWords();
	void testInconsisntentDictionary();
	void testInconsisntentDictionaryWithEmptyWords();
	void testDictionaryWithComplexInconsistency();
	void testFindAllAlphabets();
	void testFindAllAlphabetsWithEmptyWords();
};

#endif //TEST__ALPHABETFROMDICTIONARY_HPP