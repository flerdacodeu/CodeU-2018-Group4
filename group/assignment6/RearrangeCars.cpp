#include "RearrangeCars.h"

RearrangeCars::RearrangeCars(const vector<int> &startStates) : startStates(startStates) {}

void RearrangeCars::setStartStates(const vector<int> &startStates) {
	this->startStates = startStates;
}

int RearrangeCars::findEmptySlotId() {
	for (int slotId = 0; slotId < this->startStates.size(); slotId++) {
		if (this->startStates[slotId] == -1) 
			return slotId;		// no car has -1 id, it is reserved for empty slot
	}

	return -1;	// This code should not be reached
}

vector<int> RearrangeCars::findCarPositions(const vector<int> &currentStates) {
	vector<int> carPositions(currentStates.size() - 1);
	for (int i = 0; i < currentStates.size(); i++) {
		if (currentStates[i] != -1)		// check for empty slot
			carPositions[currentStates[i]] = i;
	}

	return carPositions;
}

void RearrangeCars::moveCar(vector<int> &currentStates, vector<int> &carPosition, int from, int to) {
	currentStates[to] = currentStates[from];
	currentStates[from] = -1;
	carPosition[currentStates[to]] = to;
}

bool RearrangeCars::validMove(int carId, int emptySlotId, const vector<set<int>>* constrains) {
	if (!constrains)	// Constrains are not set
		return true;

	if (constrains[emptySlotId].size() == 0)	// There are no constraints for this parking space, any car can be moved here
		return true;

	if (((*constrains)[emptySlotId]).find(carId) == ((*constrains)[emptySlotId].end()))
		return true;

	return false;
}

int RearrangeCars::numberOfCarsOnTheirDesiredPositions (const vector<int>& carPosition, const vector<int>& endStates) {
	int count = 0;
	for (int i = 0; i < carPosition.size(); i++)
		if (endStates[carPosition[i]] == i)
			count++;

	return count;
}

int RearrangeCars::findMisplacedCar(vector<int> &carPosition, vector<int> &currentStates, const vector<int> &endStates, const vector<set<int>> *constraints, vector<Move> &sequenceOfMoves, int &emptySlotId, int &numOfCarsOnDisiredPosition) {
	int lastMovedCarId = -1;
	int currCarSlotId;

	while (true) {
		currCarSlotId = endStates[emptySlotId];
		if (lastMovedCarId != currCarSlotId && currCarSlotId != -1) {
			return currCarSlotId;
		}

		// Find a misplaced car that can be moved here
		bool foundMisplacedCar = false;
		for (int carId = 0; carId < carPosition.size(); carId++) {
			if (lastMovedCarId != carId && endStates[carPosition[carId]] != carId && validMove(carId, emptySlotId, constraints)) {
				currCarSlotId = carPosition[carId];
				lastMovedCarId = carId;

				foundMisplacedCar = true;
				break;
			}
		}

		// If misplaced car can't be moved to free slot, move a car that is on its position and can be moved here
		if (!foundMisplacedCar) {
			for (int carId = 0; carId < carPosition.size(); carId++) {
				if (validMove(carId, emptySlotId, constraints)) {
					currCarSlotId = carPosition[carId];
					lastMovedCarId = carId;

					numOfCarsOnDisiredPosition--;
					break;
				}
			}
		}

		// Make a move
		moveCar(currentStates, carPosition, currCarSlotId, emptySlotId);
		sequenceOfMoves.push_back(Move(lastMovedCarId, make_pair(currCarSlotId, emptySlotId)));
		emptySlotId = currCarSlotId;
	}

}

void RearrangeCars::generateSequenceOfMoves(const vector<int> &endStates, vector<Move> &sequenceOfMoves, const vector<set<int>> *constraints) {
	vector<int> currentStates = this->startStates; // startStates will remain unchanged
	vector<int> carPosition = findCarPositions(currentStates);

	int emptySlotId = findEmptySlotId();
	int currCarId, currCarSlotId;
	int numOfCarsOnDisiredPosition = numberOfCarsOnTheirDesiredPositions (carPosition, endStates);

	while (true) {
		currCarId = endStates[emptySlotId];
		if (currCarId == -1) // We have reached slot which should be empty in the end
			currCarId = findMisplacedCar(carPosition, currentStates, endStates, constraints, sequenceOfMoves, emptySlotId, numOfCarsOnDisiredPosition);

		currCarSlotId = carPosition[currCarId];
		moveCar(currentStates, carPosition, currCarSlotId, emptySlotId);
		numOfCarsOnDisiredPosition++;
		sequenceOfMoves.push_back(Move(currCarId, make_pair(currCarSlotId, emptySlotId)));
		emptySlotId = currCarSlotId;

		if (numOfCarsOnDisiredPosition == carPosition.size())
			break;
	}
}

void RearrangeCars::bruteForceAllSequence(vector<int>& currentStates, const vector<int>& endStates, vector<int>& carPosition, int emptySlotId, vector<Move>& sequenceOfMoves, vector<vector<Move>>& sequencesOfMoves, set<vector<int>>& usedPositions, const vector<set<int>> *constraints) {
	int numOfCarsOnDisiredPosition = numberOfCarsOnTheirDesiredPositions (carPosition, endStates);
	if (numOfCarsOnDisiredPosition == carPosition.size()) {
		sequencesOfMoves.push_back(sequenceOfMoves);
		return;
	}
	for (int currCarSlotId = 0; currCarSlotId < currentStates.size(); currCarSlotId++) {
		if (currCarSlotId != emptySlotId && validMove(currentStates[currCarSlotId], emptySlotId, constraints)) {

			// we swap car on our currCarSlotId and now this car on emptySlotId position
			moveCar(currentStates, carPosition, currCarSlotId, emptySlotId);

			if (usedPositions.find(carPosition) == usedPositions.end()) {
				usedPositions.insert(carPosition);
				sequenceOfMoves.push_back(Move(currentStates[emptySlotId], make_pair(currCarSlotId, emptySlotId)));
				bruteForceAllSequence(currentStates, endStates, carPosition, currCarSlotId, sequenceOfMoves, sequencesOfMoves, usedPositions, constraints);
				sequenceOfMoves.pop_back();
				usedPositions.erase(usedPositions.find(carPosition));
			}

			// we want to swap again and return to our currentStates for next try
			moveCar(currentStates, carPosition, emptySlotId, currCarSlotId);
		}
	}
}

void RearrangeCars::generateAllSequencesOfMoves(const vector<int> &endStates, vector<vector<Move>> &sequencesOfMoves, const vector<set<int>> *constraints) {
	vector<int> currentStates = this->startStates;
	vector<int> carPosition = findCarPositions(currentStates);

	int emptySlotId = findEmptySlotId();
	vector<Move> sequenceOfMoves;
	set<vector<int>> usedPositions;
	bruteForceAllSequence(currentStates, endStates, carPosition, emptySlotId, sequenceOfMoves, sequencesOfMoves, usedPositions, constraints);
}
