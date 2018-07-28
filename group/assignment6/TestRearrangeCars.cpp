#include "TestRearrangeCars.h"

void TestRearrangeCars::runAllTests() {
	testValidRearrangingOfCars();
	testValidRearrangingOfCarsWithConstrains();
	testValidRearrangingOfCarsWithConstrainsWhenDisplacedCarsCanNotBeMovedToFreeSpace1();
	testValidRearrangingOfCarsWithConstrainsWhenDisplacedCarsCanNotBeMovedToFreeSpace2();
}

template<typename T>
void printSequence(vector<T> sequence) {
	for (T &item : sequence)
		cout << item;
	cout << endl;
}

void TestRearrangeCars::testValidRearrangingOfCars() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, 0, 1, -1 };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	printSequence(sequenceOfMoves);

	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		// Make a move
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates); // Check if following this moves gives valid endStates
}

void TestRearrangeCars::testValidRearrangingOfCarsWithConstrains() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 2, -1, 1, 0 };
	vector<set<int>> constraints = { {},{2},{},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMovesWithConstraints(endStates, sequenceOfMoves, constraints);
	printSequence(sequenceOfMoves);

	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		// Make a move
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates); // Check if following this moves gives valid endStates
}

void TestRearrangeCars::testValidRearrangingOfCarsWithConstrainsWhenDisplacedCarsCanNotBeMovedToFreeSpace1() {	// TODO: change function name
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { {},{},{0},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMovesWithConstraints(endStates, sequenceOfMoves, constraints);
	printSequence(sequenceOfMoves);

	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		// Make a move
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates); // Check if following this moves gives valid endStates
}

void TestRearrangeCars::testValidRearrangingOfCarsWithConstrainsWhenDisplacedCarsCanNotBeMovedToFreeSpace2() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = { 0, 2, -1, 1 };
	vector<set<int>> constraints = { {2},{},{0},{} };
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMovesWithConstraints(endStates, sequenceOfMoves, constraints);
	printSequence(sequenceOfMoves);

	for (Move &move : sequenceOfMoves) {
		EXPECT_EQ(move.carId, startStates[move.positions.first]);
		EXPECT_EQ(-1, startStates[move.positions.second]);
		// Make a move
		startStates[move.positions.second] = move.carId;
		startStates[move.positions.first] = -1;
	}
	EXPECT_EQ(endStates, startStates); // Check if following this moves gives valid endStates
}
