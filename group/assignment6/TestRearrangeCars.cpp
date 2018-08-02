#include "TestRearrangeCars.h"

// Print function for sequences of objects saved in vectors.
template<typename T>
void printSequence(vector<T> sequence) {
	for (T &item : sequence)
		cout << item;
	cout << endl;
}

void TestRearrangeCars::runAllTests() {
	testNoConstraints();
	testWithConstraints();
	testAllPossibleSequences();
}

void TestRearrangeCars::testNoConstraints() {
	//testDuplicateInStartStates(); 
	//testDuplicateInEndStates(); 
	//testMultpleEmptySlotsInStartStates(); 
	//testMultpleEmptySlotsInEndStates(); 
	//testNumberOfStatesMismatch(); 
	//testEmptyInput(); 
	//testNonEmptyOneSlot();
	//testValidOneSlot();
	testValidStates();
}

void TestRearrangeCars::testWithConstraints() {
	//testDuplicateInStartStatesWithValidConstraints(); 
	//testDuplicateInEndStatesWithValidConstraints(); 
	//testMultpleEmptySlotsInStartStatesWithValidConstraints(); 
	//testMultpleEmptySlotsInEndStatesWithValidConstraints(); 
	//testNumberOfStatesMismatchWithValidConstraints(); 
	//testEmptyInputWithInvalidConstraints();
	//testEmptyInputWithValidConstraints(); 
	//testNonEmptyOneSlotWithValidConstraints();
	//testValidOneSlotWithInvalidConstraints();
	//testValidOneSlotWithValidConstraints();
	//testValidStatesWithEmptyConstraints();
	//testValidStatesWithInvalidConstraints1();
	//testValidStatesWithInvalidConstraints2();
	//testValidStatesWithInvalidConstraints3();
	//testValidStatesWithImpossibleConstraints1();
	//testValidStatesWithImpossibleConstraints2();
	testValidStatesWithValidConstraints1();
	testValidStatesWithValidConstraints2();
	testValidStatesWithValidConstraints3();
}

void TestRearrangeCars::testAllPossibleSequences() {
	//TODO: tests for all possible sequences challenge
}

void TestRearrangeCars::testDuplicateInStartStates() {
	vector<int> startStates = { 0, 1, -1, 1 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testDuplicateInEndStates() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, 1, 1, -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testMultpleEmptySlotsInStartStates() {
	vector<int> startStates = { 0, -1, -1, 2 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testMultpleEmptySlotsInEndStates() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { -1, 0, 1, -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testNumberOfStatesMismatch() {
	vector<int> startStates = { 0, 1, -1 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testEmptyInput() {
	vector<int> startStates = {};
	vector<int> endStates = {};
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testNonEmptyOneSlot() {
	vector<int> startStates = { 0 };
	vector<int> endStates = { 0 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testValidOneSlot() {
	vector<int> startStates = { -1 };
	vector<int> endStates = { -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testValidStates() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	//printSequence(sequenceOfMoves);
	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates);
}

void TestRearrangeCars::testDuplicateInStartStatesWithValidConstraints() {
	vector<int> startStates = { 0, 1, -1, 1 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testDuplicateInEndStatesWithValidConstraints() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, 1, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testMultpleEmptySlotsInStartStatesWithValidConstraints() {
	vector<int> startStates = { 0, -1, -1, 2 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testMultpleEmptySlotsInEndStatesWithValidConstraints() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { -1, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testNumberOfStatesMismatchWithValidConstraints() {
	vector<int> startStates = { 0, 1, -1 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testEmptyInputWithValidConstraints() {
	vector<int> startStates = {};
	vector<int> endStates = {};
	vector<set<int>> constraints = {};
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testEmptyInputWithInvalidConstraints() {
	vector<int> startStates = {};
	vector<int> endStates = {};
	vector<set<int>> constraints = { {},{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testNonEmptyOneSlotWithValidConstraints() {
	vector<int> startStates = { 0 };
	vector<int> endStates = { 0 };
	vector<set<int>> constraints = { {} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testValidOneSlotWithInvalidConstraints() {
	vector<int> startStates = { -1 };
	vector<int> endStates = { -1 };
	vector<set<int>> constraints = { { 0 } };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testValidOneSlotWithValidConstraints() {
	vector<int> startStates = { -1 };
	vector<int> endStates = { -1 };
	vector<set<int>> constraints = { {} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testValidStatesWithEmptyConstraints() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{},{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	//printSequence(sequenceOfMoves);
	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates);
}

void testValidStatesWithInvalidConstraints1()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ -1 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void testValidStatesWithInvalidConstraints2()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { { 0 },{ 3 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void testValidStatesWithInvalidConstraints3()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { { 0 },{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void testValidStatesWithImpossibleConstraints1()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{ 1 },{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void testValidStatesWithImpossibleConstraints2()
{
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{ 0, 1, 2 },{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	EXPECT_EQ(0, sequenceOfMoves.size());
}

void TestRearrangeCars::testValidStatesWithValidConstraints1() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{ 2 },{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	//printSequence(sequenceOfMoves);
	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		for (int slot = 0; slot < startStates.size(); slot++)
			if (constraints[slot].find(move.carId) != constraints[slot].end())
				EXPECT_TRUE(move.positions.second != slot);
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates);
}

void TestRearrangeCars::testValidStatesWithValidConstraints2() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { {},{},{ 0 },{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	//printSequence(sequenceOfMoves);
	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		for (int slot = 0; slot < startStates.size(); slot++)
			if (constraints[slot].find(move.carId) != constraints[slot].end())
				EXPECT_TRUE(move.positions.second != slot);
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates);
}

void TestRearrangeCars::testValidStatesWithValidConstraints3() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { { 2 },{},{ 0 },{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves, &constraints);
	//printSequence(sequenceOfMoves);
	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		for (int slot = 0; slot < startStates.size(); slot++)
			if (constraints[slot].find(move.carId) != constraints[slot].end())
				EXPECT_TRUE(move.positions.second != slot);
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates);
}
