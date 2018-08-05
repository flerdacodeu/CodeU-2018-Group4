#include "TestRearrangeCars.h"

// Print functions for sequences of objects saved in vectors.
template<typename T>
void printSequence(vector<T> sequence) {
	for (T &item : sequence)
		cout << item;
	cout << endl;
}

template<typename T>
void printAllSequences(vector<vector<T>> allSequences) {
	for (vector<T> &sequence : allSequences) {
		printSequence(sequence);
		cout << "End of sequence" << endl;
	}
}

void testInvalidInput(const vector<int> &startStates, const vector<int> &endStates, const vector<set<int>> &constraints) {
	vector<Move> sequenceOfMoves;
	vector<vector<Move>> allSequencesOfMoves;

	RearrangeCars rearrangeCars(startStates);
	EXPECT_EQ(false, rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints));
	EXPECT_EQ(0, sequenceOfMoves.size());
	EXPECT_EQ(false, rearrangeCars.generateAllSequencesOfMoves(endStates, allSequencesOfMoves, &constraints));
	EXPECT_EQ(0, allSequencesOfMoves.size());
}

void testValidInput(const vector<int> &startStates, const vector<int> &endStates, const vector<set<int>> &constraints, bool printResult = false) {
	vector<Move> sequenceOfMoves;
	vector<int> curStates(startStates);

	RearrangeCars rearrangeCars(startStates);
	EXPECT_EQ(true, rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints));
	if (printResult)
		printSequence(sequenceOfMoves);

	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, curStates[move.positions.first]);
		EXPECT_EQ(-1, curStates[move.positions.second]);
		for (int slot = 0; slot < curStates.size(); slot++)
			if (constraints[slot].find(move.carId) != constraints[slot].end())
				EXPECT_TRUE(move.positions.second != slot);
		curStates[move.positions.second] = move.carId;
		curStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, curStates);
}

void testValidInputAllSequences(const vector<int> &startStates, const vector<int> &endStates, bool printResult = false) {
	vector<vector<Move>> allSequencesOfMoves;

	RearrangeCars rearrangeCars(startStates);
	EXPECT_EQ(true, rearrangeCars.generateAllSequencesOfMoves(endStates, allSequencesOfMoves));
	if (printResult)
		printAllSequences(allSequencesOfMoves);

	for (vector<Move> &sequenceOfMoves : allSequencesOfMoves) {
		vector<int> curStates(startStates);
		for (Move &move : sequenceOfMoves) {
			EXPECT_EQ(move.carId, curStates[move.positions.first]);
			EXPECT_EQ(-1, curStates[move.positions.second]);
			curStates[move.positions.second] = move.carId;
			curStates[move.positions.first] = -1;
		}
		EXPECT_EQ(endStates, curStates);
	}
}

void TestRearrangeCars::runAllTests() {
	testDuplicateInStartStates();
	testDuplicateInEndStates();
	testMultpleEmptySlotsInStartStates();
	testMultpleEmptySlotsInEndStates();
	testNumberOfStatesMismatch();
	testEmptyInput();
	testEmptyInputWithInvalidConstraints();
	testNonEmptyOneSlot();
	testValidOneSlot();
	testValidOneSlotWithInvalidConstraints();
	testValidStatesWithEmptyConstraints();
	testValidStatesWithInvalidConstraints1();
	testValidStatesWithInvalidConstraints2();
	testValidStatesWithInvalidConstraints3();
	testValidStatesWithImpossibleConstraints1();
	testValidStatesWithImpossibleConstraints2();
	testValidStates1();
	testValidStates2();
	testValidStates3();
	testValidStatesAllSequences1();
	testValidStatesAllSequences2();
	testValidStatesAllSequences3();
	testValidStatesAllSequences4();
}

void TestRearrangeCars::testDuplicateInStartStates() {
	vector<int> startStates = { 0, 1, -1, 1 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testDuplicateInEndStates() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, 1, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testMultpleEmptySlotsInStartStates() {
	vector<int> startStates = { 0, -1, -1, 2 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testMultpleEmptySlotsInEndStates() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { -1, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testNumberOfStatesMismatch() {
	vector<int> startStates = { 0, 1, -1 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testEmptyInput() {
	vector<int> startStates = {};
	vector<int> endStates = {};
	vector<set<int>> constraints = {};

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testEmptyInputWithInvalidConstraints() {
	vector<int> startStates = {};
	vector<int> endStates = {};
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testNonEmptyOneSlot() {
	vector<int> startStates = { 0 };
	vector<int> endStates = { 0 };
	vector<set<int>> constraints = { {} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidOneSlot() {
	vector<int> startStates = { -1 };
	vector<int> endStates = { -1 };
	vector<set<int>> constraints = { {} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidOneSlotWithInvalidConstraints() {
	vector<int> startStates = { -1 };
	vector<int> endStates = { -1 };
	vector<set<int>> constraints = { { 0 } };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStatesWithEmptyConstraints() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{},{},{} };

	testValidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStatesWithInvalidConstraints1()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ -1 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStatesWithInvalidConstraints2()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { { 0 },{ 3 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStatesWithInvalidConstraints3()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { { 0 },{ 2 },{},{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStatesWithImpossibleConstraints1()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{ 1 },{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStatesWithImpossibleConstraints2()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{ 0, 1, 2 },{} };

	testInvalidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStates1() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };

	testValidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStates2() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { {},{},{ 0 },{} };

	testValidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStates3() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { { 2 },{},{ 0 },{} };

	testValidInput(startStates, endStates, constraints);
}

void TestRearrangeCars::testValidStatesAllSequences1() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };

	testValidInputAllSequences(startStates, endStates);
}

void TestRearrangeCars::testValidStatesAllSequences2() {
	vector<int> startStates = { 0, 1, -1 };
	vector<int> endStates = { 1, 0, -1 };

	testValidInputAllSequences(startStates, endStates);
}

void TestRearrangeCars::testValidStatesAllSequences3() {
	vector<int> startStates = { 0, -1 };
	vector<int> endStates = { -1, 0 };

	testValidInputAllSequences(startStates, endStates);
}

void TestRearrangeCars::testValidStatesAllSequences4() {
	vector<int> startStates = { 0, -1 };
	vector<int> endStates = { 0, -1 };

	testValidInputAllSequences(startStates, endStates);
}
