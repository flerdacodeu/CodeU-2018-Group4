#ifndef REARRANGECARS_H
#define REARRANGECARS_H

#include "Move.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

#define EMPTY_SLOT_ID -1

class RearrangeCars {
private:
	vector<int> startSlot2CarId;
public:
	RearrangeCars(const vector<int> &startSlot2CarId);
	~RearrangeCars() = default;
	void setStartSlot2CarId(const vector<int> &startSlot2CarId);
	bool generateSequenceOfMoves(const vector<int> &endSlot2CarId, vector<Move> &sequenceOfMoves, const vector<set<int>> *constraints = nullptr);
	bool generateAllSequencesOfMoves(const vector<int> &endSlot2CarId, vector<vector<Move>> &allSequencesOfMoves, const vector<set<int>> *constraints = nullptr);
private:
	int findEmptySlotId();
	vector<int> findCarPositions(const vector<int> &currentSlot2CarId);
	int findMisplacedCar(vector<int> &carPositions, vector<int> &currentSlot2CarId, const vector<int> &endSlot2CarId, const vector<set<int>> *constraints, vector<Move> &sequenceOfMoves, int &emptySlotId, int &numOfCarsOnDesiredPosition);
	void moveCar(vector<int> &currentSlot2CarId, vector<int> &carPositions, int from, int to);
	bool validMove(int carId, int emptySlot, const vector<set<int>> *constraints);
	int numberOfCarsOnTheirDesiredPositions(const vector<int> &carPositions, const vector<int> &endSlot2CarId);
	void getAllSequencesFromCurrentPosition(vector<int> &currentSlot2CarId, const vector<int> &endSlot2CarId, vector<int> &carPositions, int emptySlotId, vector<Move> &sequenceOfMoves, vector<vector<Move>> &allSequencesOfMovess, set<vector<int>> &usedPositions, const vector<set<int>> *constraints = nullptr);
	bool isInputValid(const vector<int> &endSlot2CarId, const vector<set<int>> *constraints);
	bool isInputValidAux(const vector<int> &slot2CarId, const vector<set<int>> *constraints);
};

#endif
