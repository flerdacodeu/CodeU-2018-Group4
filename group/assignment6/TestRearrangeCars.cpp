#include "TestRearrangeCars.h"

void TestRearrangeCars::runAllTests() {
	testValidRearrangingOfCars();
}

template<typename T>
void printSequence(vector<T> sequence){
	for (T &item : sequence)
		cout << item;
}

void TestRearrangeCars::testValidRearrangingOfCars() {
	vector<int> startStates = { 0, 1, -1, 2 };
	vector<int> endStates = {2, 0, 1, -1};
	vector<Move> sequenceOfMoves;

	RearrangeCars rearrangeCars(startStates);
	rearrangeCars.generateSequenceOfMoves(endStates, sequenceOfMoves);
	printSequence(sequenceOfMoves);

	for (Move &move : sequenceOfMoves){
		EXPECT_EQ(move.carId, startStates[move.startPosition]);
		EXPECT_EQ(-1, startStates[move.endPosition]);
		// Make a move
		startStates[move.endPosition] = move.carId;
		startStates[move.startPosition] = -1;
	}
	EXPECT_EQ(endStates, startStates); // Check if following this moves gives valid endStates
}