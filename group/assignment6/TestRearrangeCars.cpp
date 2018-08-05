#include "TestRearrangeCars.h"

// Print functions for sequences of objects saved in vectors.
template<typename T>
void printSequence(vector<T> sequence) {
	for (T &item : sequence) {
		cout << item;
	}	
	cout << endl;
}

template<typename T>
void printAllSequences(vector<vector<T>> allSequences) {
	for (vector<T> &sequence : allSequences) {
		printSequence(sequence);
		cout << "End of sequence" << endl;
	}
}

void testInvalidInput(const vector<int> &startSlot2CarId, const vector<int> &endSlot2CarId, const vector<set<int>> &constraints) {
	vector<Move> sequenceOfMoves;
	vector<vector<Move>> allSequencesOfMoves;

	RearrangeCars rearrangeCars(startSlot2CarId);
	EXPECT_EQ(false, rearrangeCars.generateSequenceOfMoves(endSlot2CarId, sequenceOfMoves, &constraints));
	EXPECT_EQ(0, sequenceOfMoves.size());
	EXPECT_EQ(false, rearrangeCars.generateAllSequencesOfMoves(endSlot2CarId, allSequencesOfMoves, &constraints));
	EXPECT_EQ(0, allSequencesOfMoves.size());
}

void testValidInput(const vector<int> &startSlot2CarId, const vector<int> &endSlot2CarId, const vector<set<int>> &constraints, bool printResult = false) {
	vector<Move> sequenceOfMoves;
	vector<int> curSlot2CarId(startSlot2CarId);

	RearrangeCars rearrangeCars(startSlot2CarId);
	EXPECT_EQ(true, rearrangeCars.generateSequenceOfMoves(endSlot2CarId, sequenceOfMoves, &constraints));
	if (printResult) {
		printSequence(sequenceOfMoves);
	}
	
	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, curSlot2CarId[move.positions.first]);
		EXPECT_EQ(-1, curSlot2CarId[move.positions.second]);
		for (int slot = 0; slot < curSlot2CarId.size(); slot++) {
			if (constraints[slot].find(move.carId) != constraints[slot].end()) {
				EXPECT_TRUE(move.positions.second != slot);
			}
		}	
		curSlot2CarId[move.positions.second] = move.carId;
		curSlot2CarId[move.positions.first] = -1;
	}
	EXPECT_EQ(endSlot2CarId, curSlot2CarId);
}

void testValidInputAllSequences(const vector<int> &startSlot2CarId, const vector<int> &endSlot2CarId, const vector<set<int>> &constraints, bool printResult = false) {
	vector<vector<Move>> allSequencesOfMoves;

	RearrangeCars rearrangeCars(startSlot2CarId);
	EXPECT_EQ(true, rearrangeCars.generateAllSequencesOfMoves(endSlot2CarId, allSequencesOfMoves, &constraints));
	if (printResult) {
		printAllSequences(allSequencesOfMoves);
	}	

	for (vector<Move> &sequenceOfMoves : allSequencesOfMoves) {
		vector<int> curSlot2CarId(startSlot2CarId);
		for (Move &move : sequenceOfMoves) {
			EXPECT_EQ(move.carId, curSlot2CarId[move.positions.first]);
			EXPECT_EQ(-1, curSlot2CarId[move.positions.second]);
			for (int slot = 0; slot < curSlot2CarId.size(); slot++) {
			    if (constraints[slot].find(move.carId) != constraints[slot].end()) {
				    EXPECT_TRUE(move.positions.second != slot);
			    }
		    }
			curSlot2CarId[move.positions.second] = move.carId;
			curSlot2CarId[move.positions.first] = -1;
		}
		EXPECT_EQ(endSlot2CarId, curSlot2CarId);
	}
}

void TestRearrangeCars::runAllTests() {
	testDuplicateInStartSlot2CarId();
	testDuplicateInEndSlot2CarId();
	testMultpleEmptySlotsInStartSlot2CarId();
	testMultpleEmptySlotsInEndSlot2CarId();
	testNumberOfSlot2CarIdMismatch();
	testEmptyInput();
	testEmptyInputWithInvalidConstraints();
	testNonEmptyOneSlot();
	testValidOneSlot();
	testValidOneSlotWithInvalidConstraints();
	testValidSlot2CarIdWithEmptyConstraints();
	testValidSlot2CarIdWithInvalidConstraints1();
	testValidSlot2CarIdWithInvalidConstraints2();
	testValidSlot2CarIdWithInvalidConstraints3();
	testValidSlot2CarIdWithInvalidConstraints4();
	testValidSlot2CarIdWithImpossibleConstraints1();
	testValidSlot2CarIdWithImpossibleConstraints2();
	testValidSlot2CarId1();
	testValidSlot2CarId2();
	testValidSlot2CarId3();
	testValidSlot2CarIdAllSequences1();
	testValidSlot2CarIdAllSequences2();
	testValidSlot2CarIdAllSequences3();
	testValidSlot2CarIdAllSequences4();
}

void TestRearrangeCars::testDuplicateInStartSlot2CarId() {
	vector<int> startSlot2CarId = { 0, 1, -1, 1 };
	vector<int> endSlot2CarId = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testDuplicateInEndSlot2CarId() {
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, 1, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testMultpleEmptySlotsInStartSlot2CarId() {
	vector<int> startSlot2CarId = { 0, -1, -1, 2 };
	vector<int> endSlot2CarId = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testMultpleEmptySlotsInEndSlot2CarId() {
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { -1, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testNumberOfSlot2CarIdMismatch() {
	vector<int> startSlot2CarId = { 0, 1, -1 };
	vector<int> endSlot2CarId = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testEmptyInput() {
	vector<int> startSlot2CarId = {};
	vector<int> endSlot2CarId = {};
	vector<set<int>> constraints = {};

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testEmptyInputWithInvalidConstraints() {
	vector<int> startSlot2CarId = {};
	vector<int> endSlot2CarId = {};
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testNonEmptyOneSlot() {
	vector<int> startSlot2CarId = { 0 };
	vector<int> endSlot2CarId = { 0 };
	vector<set<int>> constraints = { {} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidOneSlot() {
	vector<int> startSlot2CarId = { -1 };
	vector<int> endSlot2CarId = { -1 };
	vector<set<int>> constraints = { {} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidOneSlotWithInvalidConstraints() {
	vector<int> startSlot2CarId = { -1 };
	vector<int> endSlot2CarId = { -1 };
	vector<set<int>> constraints = { { 0 } };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdWithEmptyConstraints() {
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{},{},{} };

	testValidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdWithInvalidConstraints1()
{
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ -1 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdWithInvalidConstraints2()
{
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { { 0 },{ 3 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdWithInvalidConstraints3()
{
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { { 0 },{ 2 },{},{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdWithInvalidConstraints4()
{
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { { 0 },{ 2 },{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdWithImpossibleConstraints1()
{
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{ 1 },{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdWithImpossibleConstraints2()
{
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{ 0, 1, 2 },{} };

	testInvalidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarId1() {
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testValidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarId2() {
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { {},{},{ 0 },{} };

	testValidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarId3() {
	vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { { 2 },{},{ 0 },{} };

	testValidInput(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdAllSequences1() {
    vector<int> startSlot2CarId = { 0, 1, -1, 2 };
	vector<int> endSlot2CarId = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{},{},{} };

	testValidInputAllSequences(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdAllSequences2() {
	vector<int> startSlot2CarId = { 0, 1, -1 };
	vector<int> endSlot2CarId = { 1, 0, -1 };
	vector<set<int>> constraints = { {},{},{ 0 } };

	testValidInputAllSequences(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdAllSequences3() {
	vector<int> startSlot2CarId = { 0, -1 };
	vector<int> endSlot2CarId = { -1, 0 };
	vector<set<int>> constraints = { {},{} };

	testValidInputAllSequences(startSlot2CarId, endSlot2CarId, constraints);
}

void TestRearrangeCars::testValidSlot2CarIdAllSequences4() {
	vector<int> startSlot2CarId = { 0, -1 };
	vector<int> endSlot2CarId = { 0, -1 };
	vector<set<int>> constraints = { {},{} };

	testValidInputAllSequences(startSlot2CarId, endSlot2CarId, constraints);
}
