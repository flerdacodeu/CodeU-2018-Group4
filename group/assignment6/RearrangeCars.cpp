#include "RearrangeCars.h"

RearrangeCars::RearrangeCars(const vector<int> &startStates) : startStates(startStates) {}

void RearrangeCars::setStartStates(const vector<int> &startStates) {
	this->startStates = startStates;
}

int RearrangeCars::findEmptySlotId() {
	for (int slotId = 0; slotId < this->startStates.size(); slotId++) {
		if (this->startStates[slotId] == -1) return slotId; // no car has -1 id, it is reserved for empty slot
	}
	return -1; // This code should not be reached
}

vector<int> RearrangeCars::findCarPositions(const vector<int> &currentStates) {
	vector<int> carPositions(currentStates.size() - 1);
	for (int i = 0; i < currentStates.size(); i++) {
		if (currentStates[i] != -1) // check for empty slot
			carPositions[currentStates[i]] = i;
	}
	return carPositions;
}

int RearrangeCars::findMisplacedCar(const vector<int> &carPosition, const vector<int> &endStates) {
	for (int carId = 0; carId < carPosition.size(); carId++) {
		if (endStates[carPosition[carId]] != carId) return carId;
	}
	return -1; // If every car is on its slot
}

void RearrangeCars::moveCar(vector<int> &currentStates, vector<int> &carPosition, int from, int to) {
	currentStates[to] = currentStates[from];
	currentStates[from] = -1;
	carPosition[currentStates[to]] = to;
}

void RearrangeCars::generateSequenceOfMoves(const vector<int> &endStates, vector<Move> &sequenceOfMoves) {
	vector<int> currentStates = this->startStates; // startStates will remain unchanged
	vector<int> carPosition = findCarPositions(currentStates);

	int emptySlotId = findEmptySlotId();
	int currCarId, currCarSlotId;

	while (true) {
		currCarId = endStates[emptySlotId];
		if (currCarId == -1)	// We reached slot which should be empty in the end
			currCarId = findMisplacedCar(carPosition, endStates);
		if (currCarId == -1) break;
		currCarSlotId = carPosition[currCarId];
		moveCar(currentStates, carPosition, currCarSlotId, emptySlotId);
		sequenceOfMoves.push_back(Move(currCarId, make_pair(currCarSlotId, emptySlotId)));
		emptySlotId = currCarSlotId;
	}
}

bool RearrangeCars::validMove(int carId, int emptySlotId, const vector<set<int>>& constrains) {
	if (constrains[emptySlotId].size() == 0)	// There are no constraints for this parking space, any car can be moved here
		return true;

	if ((constrains[emptySlotId]).find(carId) != (constrains[emptySlotId].end()))
		return true;

	return false;
}

int RearrangeCars::findMisplacedCarWithConstraints(vector<int> &carPosition, vector<int> &currentStates, const vector<int> &endStates, const vector<set<int>> &constraints, vector<Move> &sequenceOfMoves, int &emptySlotId, int &numOfCarsOnDisiredPosition) {
	int lastMovedCarId = -1;
	int currCarSlotId;

	while (true) {
		currCarSlotId = endStates[emptySlotId];
		if (lastMovedCarId != currCarSlotId && currCarSlotId != -1) {
			return currCarSlotId;
		}

		// Find a displaced car that can be moved here
		bool foundDisplacedCar = false;
		for (int carId = 0; carId < carPosition.size(); carId++) {
			if (lastMovedCarId != carId && endStates[carPosition[carId]] != carId && validMove(carId, emptySlotId, constraints)) {
				currCarSlotId = carPosition[carId];
				lastMovedCarId = carId;

				foundDisplacedCar = true;
				break;
			}
		}

		// If displaced car can't be moved to free slot, move a car that is on its position and can be moved here
		if (!foundDisplacedCar) {
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

int RearrangeCars::numberOfCarsOnDesiredPosition(const vector<int>& carPosition, const vector<int>& endStates) {
	int num = 0;
	for (int i = 0; i < carPosition.size(); i++)
		if (endStates[carPosition[i]] == i)
			num++;

	return num;
}

void RearrangeCars::generateSequenceOfMovesWithConstraints(const vector<int> &endStates, vector<Move> &sequenceOfMoves, const vector<set<int>> &constraints) {
	vector<int> currentStates = this->startStates; // startStates will remain unchanged
	vector<int> carPosition = findCarPositions(currentStates);

	int emptySlotId = findEmptySlotId();
	int currCarId, currCarSlotId;
	int numOfCarsOnDisiredPosition = numberOfCarsOnDesiredPosition(carPosition, endStates);

	while (true) {
		currCarId = endStates[emptySlotId];
		if (currCarId == -1) // We have reached slot which should be empty in the end
			currCarId = findMisplacedCarWithConstraints(carPosition, currentStates, endStates, constraints, sequenceOfMoves, emptySlotId, numOfCarsOnDisiredPosition);

		currCarSlotId = carPosition[currCarId];
		moveCar(currentStates, carPosition, currCarSlotId, emptySlotId);
		numOfCarsOnDisiredPosition++;
		sequenceOfMoves.push_back(Move(currCarId, make_pair(currCarSlotId, emptySlotId)));
		emptySlotId = currCarSlotId;

		if (numOfCarsOnDisiredPosition == carPosition.size())
			break;
	}
}
