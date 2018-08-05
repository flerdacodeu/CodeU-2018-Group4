#ifndef TESTREARRANGECARS_H
#define TESTREARRANGECARS_H

#include "RearrangeCars.h"
#include "codeu_test_lib.h"

class TestRearrangeCars {
public:
    void runAllTests();
private:
    void testDuplicateInStartSlot2CarId(); 
    void testDuplicateInEndSlot2CarId(); 
    void testMultpleEmptySlotsInStartSlot2CarId(); 
    void testMultpleEmptySlotsInEndSlot2CarId(); 
    void testNumberOfSlot2CarIdMismatch(); 
    void testEmptyInput(); 
    void testEmptyInputWithInvalidConstraints(); 
    void testNonEmptyOneSlot();
    void testValidOneSlot();
    void testValidOneSlotWithInvalidConstraints();
    void testValidSlot2CarIdWithEmptyConstraints();
    void testValidSlot2CarIdWithInvalidConstraints1();
    void testValidSlot2CarIdWithInvalidConstraints2();
    void testValidSlot2CarIdWithInvalidConstraints3();
    void testValidSlot2CarIdWithInvalidConstraints4();
    void testValidSlot2CarIdWithImpossibleConstraints1();
    void testValidSlot2CarIdWithImpossibleConstraints2();
    void testValidSlot2CarId1();
    void testValidSlot2CarId2();
    void testValidSlot2CarId3();
    void testValidSlot2CarIdAllSequences1();
    void testValidSlot2CarIdAllSequences2();
    void testValidSlot2CarIdAllSequences3();
    void testValidSlot2CarIdAllSequences4();
};

#endif
