#ifndef REARRANGECARS_H
#define REARRANGECARS_H

#include "Move.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class RearrangeCars {
private:
	vector<int> startStates;

public:
	RearrangeCars(const vector<int> &startStates);
	~RearrangeCars() = default;
	void setStartStates(const vector<int> &startStates);
	void generateSequenceOfMoves(const vector<int> &endStates, vector<Move> &sequenceOfMoves);
	void generateSequenceOfMovesWithConstraints(const vector<int> &endStates, vector<Move> &sequenceOfMoves, const vector<set<int>> &constraints);
	void generateAllSequencesOfMoves(const vector<int> &endStates, const vector<set<int>> &constraints, vector<vector<Move>> &sequencesOfMoves);

private:
	int findEmptySlotId();
	vector<int> findCarPositions(const vector<int> &currentStates);
	int findMisplacedCar(const vector<int> &carPosition, const vector<int> &endStates);
	int findMisplacedCarWithConstraints(vector<int> &carPosition, vector<int> &currentStates, const vector<int> &endStates, const vector<set<int>> &constraints, vector<Move> &sequenceOfMoves, int &emptySlotId, int &numOfCarsOnDisiredPosition);
	void moveCar(vector<int> &currentStates, vector<int> &carPosition, int from, int to);
	bool validMove(int carId, int emptySlot, const vector<set<int>>& constrains);
	int numberOfCarsOnDesiredPosition(const vector<int>& carPosition, const vector<int>& endPosition);
	void bruteForceAllSequence(vector<int>& currentStates, const vector<int>& endStates, const vector<set<int>> &constraints, vector<int>& carPosition, int emptySlotId, vector<Move>& sequenceOfMoves, vector<vector<Move>>& sequencesOfMoves, set<vector<int>>& usedPositions);
};

#endif
