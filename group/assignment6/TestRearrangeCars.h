#ifndef TESTREARRANGECARS_H
#define TESTREARRANGECARS_H

#include "RearrangeCars.h"
#include "codeu_test_lib.h"

class TestRearrangeCars {
public:
    void runAllTests();
private:
    void testDuplicateInStartStates(); 
    void testDuplicateInEndStates(); 
    void testMultpleEmptySlotsInStartStates(); 
    void testMultpleEmptySlotsInEndStates(); 
    void testNumberOfStatesMismatch(); 
    void testEmptyInput(); 
    void testEmptyInputWithInvalidConstraints(); 
    void testNonEmptyOneSlot();
    void testValidOneSlot();
    void testValidOneSlotWithInvalidConstraints();
    void testValidStatesWithEmptyConstraints();
    void testValidStatesWithInvalidConstraints1();
    void testValidStatesWithInvalidConstraints2();
    void testValidStatesWithInvalidConstraints3();
    void testValidStatesWithImpossibleConstraints1();
    void testValidStatesWithImpossibleConstraints2();
    void testValidStates1();
    void testValidStates2();
    void testValidStates3();
    void testValidStatesAllSequences1();
    void testValidStatesAllSequences2();
    void testValidStatesAllSequences3();
    void testValidStatesAllSequences4();
};

#endif
