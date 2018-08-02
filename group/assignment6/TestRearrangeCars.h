#ifndef TESTREARRANGECARS_H
#define TESTREARRANGECARS_H

#include "RearrangeCars.h"
#include "codeu_test_lib.h"

class TestRearrangeCars {
public:
    void runAllTests();
private:
    void testNoConstraints();
    void testWithConstraints(); 
    void testAllPossibleSequences();
    
    void testDuplicateInStartStates(); 
    void testDuplicateInEndStates(); 
    void testMultpleEmptySlotsInStartStates(); 
    void testMultpleEmptySlotsInEndStates(); 
    void testNumberOfStatesMismatch(); 
    void testEmptyInput(); 
    void testNonEmptyOneSlot();
    void testValidOneSlot();
    void testValidStates();
	
    void testDuplicateInStartStatesWithValidConstraints(); 
    void testDuplicateInEndStatesWithValidConstraints(); 
    void testMultpleEmptySlotsInStartStatesWithValidConstraints(); 
    void testMultpleEmptySlotsInEndStatesWithValidConstraints(); 
    void testNumberOfStatesMismatchWithValidConstraints(); 
    void testEmptyInputWithInvalidConstraints(); 
    void testEmptyInputWithValidConstraints(); 
    void testNonEmptyOneSlotWithValidConstraints();
    void testValidOneSlotWithInvalidConstraints();
    void testValidOneSlotWithValidConstraints();
    void testValidStatesWithEmptyConstraints();
    void testValidStatesWithInvalidConstraints1();
    void testValidStatesWithInvalidConstraints2();
    void testValidStatesWithInvalidConstraints3();
    void testValidStatesWithImpossibleConstraints1();
    void testValidStatesWithImpossibleConstraints2();
    void testValidStatesWithValidConstraints1();
    void testValidStatesWithValidConstraints2();
    void testValidStatesWithValidConstraints3();
};

#endif
