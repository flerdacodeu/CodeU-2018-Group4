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
	void generateSequenceOfMoves(const vector<int> &endStates, vector<Move> &sequenceOfMoves, const vector<set<int>> *constraints = nullptr);
	void generateAllSequencesOfMoves(const vector<int> &endStates, vector<vector<Move>> &sequencesOfMoves, const vector<set<int>> *constraints = nullptr);
private:
	int findEmptySlotId();
	vector<int> findCarPositions(const vector<int> &currentStates);
	int findMisplacedCar(vector<int> &carPosition, vector<int> &currentStates, const vector<int> &endStates, const vector<set<int>> *constraints, vector<Move> &sequenceOfMoves, int &emptySlotId, int &numOfCarsOnDisiredPosition);
	void moveCar(vector<int> &currentStates, vector<int> &carPosition, int from, int to);
	bool validMove(int carId, int emptySlot, const vector<set<int>> *constraints);
	int numberOfCarsOnDesiredPosition(const vector<int> &carPosition, const vector<int> &endPosition);
	void bruteForceAllSequence(vector<int> &currentStates, const vector<int> &endStates, vector<int> &carPosition, int emptySlotId, vector<Move> &sequenceOfMoves, vector<vector<Move>> &sequencesOfMoves, set<vector<int>> &usedPositions, const vector<set<int>> *constraints = nullptr);
};

#endif
