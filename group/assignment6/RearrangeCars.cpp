#include "RearrangeCars.h"

RearrangeCars::RearrangeCars(const vector<int> &startSlot2CarId) : startSlot2CarId(startSlot2CarId) {}

void RearrangeCars::setStartSlot2CarId(const vector<int> &startSlot2CarId) {
	this->startSlot2CarId = startSlot2CarId;
}

int RearrangeCars::findEmptySlotId() {
	for (int slotId = 0; slotId < this->startSlot2CarId.size(); slotId++) {
		if (this->startSlot2CarId[slotId] == EMPTY_SLOT_ID) {
			return slotId;  // No car has EMPTY_SLOT_ID id, it is reserved for empty slot.
		}	
	}

	return -1;  // This code should not be reached.
}

vector<int> RearrangeCars::findCarPositions(const vector<int> &currentSlot2CarId) {
	vector<int> carPositions(currentSlot2CarId.size() - 1);
	for (int i = 0; i < currentSlot2CarId.size(); i++) {
		if (currentSlot2CarId[i] != EMPTY_SLOT_ID) {  // Check for empty slot.
			carPositions[currentSlot2CarId[i]] = i;
		}	
	}

	return carPositions;
}

void RearrangeCars::moveCar(vector<int> &currentSlot2CarId, vector<int> &carPosition, int from, int to) {
	currentSlot2CarId[to] = currentSlot2CarId[from];
	currentSlot2CarId[from] = EMPTY_SLOT_ID;
	carPosition[currentSlot2CarId[to]] = to;
}

bool RearrangeCars::validMove(int carId, int emptySlotId, const vector<set<int>> *constraints) {
	if (!constraints) {  // Constraints are not set.
		return true;
	}	

	if (constraints[emptySlotId].empty()) {  // There are no constraints for this parking space, any car can be moved here.
		return true;
	}	

	if (((*constraints)[emptySlotId]).find(carId) == ((*constraints)[emptySlotId].end())) {
		return true;
	}	

	return false;
}

int RearrangeCars::numberOfCarsOnTheirDesiredPositions(const vector<int> &carPosition, const vector<int> &endSlot2CarId) {
	int count = 0;
	for (int i = 0; i < carPosition.size(); i++) {
		if (endSlot2CarId[carPosition[i]] == i) {
			count++;
		}
	}	

	return count;
}

int RearrangeCars::findMisplacedCar(vector<int> &carPosition, vector<int> &currentSlot2CarId, const vector<int> &endSlot2CarId,
				     const vector<set<int>> *constraints, vector<Move> &sequenceOfMoves,
				     int &emptySlotId, int &numOfCarsOnDisiredPosition) {
	int lastMovedCarId = -1;
	int currCarSlotId;

	while (true) {
		currCarSlotId = endSlot2CarId[emptySlotId];
		if (lastMovedCarId != currCarSlotId && currCarSlotId != EMPTY_SLOT_ID) {
			return currCarSlotId;
		}

		// Find a misplaced car that can be moved here.
		bool foundMisplacedCar = false;
		for (int carId = 0; carId < carPosition.size(); carId++) {
			if (lastMovedCarId != carId && endSlot2CarId[carPosition[carId]] != carId &&
				validMove(carId, emptySlotId, constraints)) {
				currCarSlotId = carPosition[carId];
				lastMovedCarId = carId;

				foundMisplacedCar = true;
				break;
			}
		}

		// If misplaced car can't be moved to free slot, move a car that is on its position and can be moved here.
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

		// Make a move.
		moveCar(currentSlot2CarId, carPosition, currCarSlotId, emptySlotId);
		sequenceOfMoves.push_back(Move(lastMovedCarId, make_pair(currCarSlotId, emptySlotId)));
		emptySlotId = currCarSlotId;
	}

}

bool RearrangeCars::generateSequenceOfMoves(const vector<int> &endSlot2CarId, vector<Move> &sequenceOfMoves, const vector<set<int>> *constraints) {
	sequenceOfMoves.clear();

	if (!isInputValid(endSlot2CarId, constraints)) {
		return false;
	}

	vector<int> currentSlot2CarId = this->startSlot2CarId;  // startSlot2CarId will remain unchanged.
	vector<int> carPosition = findCarPositions(currentSlot2CarId);

	int emptySlotId = findEmptySlotId();
	int currCarId, currCarSlotId;
	int numOfCarsOnDesiredPositions = numberOfCarsOnTheirDesiredPositions(carPosition, endSlot2CarId);

	while (true) {
		currCarId = endSlot2CarId[emptySlotId];
		if (currCarId == EMPTY_SLOT_ID) {  // We have reached slot which should be empty in the end.
			currCarId = findMisplacedCar(carPosition, currentSlot2CarId, endSlot2CarId, constraints,
				sequenceOfMoves, emptySlotId, numOfCarsOnDesiredPositions);
		}		

		currCarSlotId = carPosition[currCarId];
		moveCar(currentSlot2CarId, carPosition, currCarSlotId, emptySlotId);
		numOfCarsOnDesiredPositions++;
		sequenceOfMoves.push_back(Move(currCarId, make_pair(currCarSlotId, emptySlotId)));
		emptySlotId = currCarSlotId;

		if (numOfCarsOnDesiredPositions == carPosition.size()) {
			break;
		}	
	}
      
	return true;
}

void
RearrangeCars::getAllSequencesFromCurrentPosition(vector<int> &currentSlot2CarId, const vector<int> &endSlot2CarId, vector<int> &carPosition,
				      int emptySlotId, vector<Move> &sequenceOfMoves,
			              vector<vector<Move>> &allSequencesOfMoves, set<vector<int>> &usedPositions,
				      const vector<set<int>> *constraints) {
	int numOfCarsOnDesiredPositions = numberOfCarsOnTheirDesiredPositions(carPosition, endSlot2CarId);

	if (numOfCarsOnDesiredPositions == carPosition.size()) {
		allSequencesOfMoves.push_back(sequenceOfMoves);
		return;
	}

	for (int currCarSlotId = 0; currCarSlotId < currentSlot2CarId.size(); currCarSlotId++) {
		if (currCarSlotId != emptySlotId && validMove(currentSlot2CarId[currCarSlotId], emptySlotId, constraints)) {

			// We swap car on our currCarSlotId and now this car on emptySlotId position.
			moveCar(currentSlot2CarId, carPosition, currCarSlotId, emptySlotId);

			if (usedPositions.find(carPosition) == usedPositions.end()) {
				usedPositions.insert(carPosition);
				sequenceOfMoves.push_back(
					Move(currentSlot2CarId[emptySlotId], make_pair(currCarSlotId, emptySlotId)));
				getAllSequencesFromCurrentPosition(currentSlot2CarId, endSlot2CarId, carPosition, currCarSlotId,
					sequenceOfMoves, allSequencesOfMoves, usedPositions, constraints);
				sequenceOfMoves.pop_back();
				usedPositions.erase(usedPositions.find(carPosition));
			}

			// We want to swap again and return to our currentSlot2CarId for next try.
			moveCar(currentSlot2CarId, carPosition, emptySlotId, currCarSlotId);
		}
	}
}

bool RearrangeCars::generateAllSequencesOfMoves(const vector<int> &endSlot2CarId, vector<vector<Move>> &allSequencesOfMoves, const vector<set<int>> *constraints) {
	allSequencesOfMoves.clear();
	
	if (!isInputValid(endSlot2CarId, constraints)) {
		return false;
	}
	
	vector<int> currentSlot2CarId = this->startSlot2CarId;
	vector<int> carPosition = findCarPositions(currentSlot2CarId);

	int emptySlotId = findEmptySlotId();
	vector<Move> sequenceOfMoves;
	set<vector<int>> usedPositions;
	usedPositions.insert(carPosition);
	getAllSequencesFromCurrentPosition(currentSlot2CarId, endSlot2CarId, carPosition, emptySlotId, sequenceOfMoves, allSequencesOfMoves, usedPositions, constraints);
	
    return true;
}

bool RearrangeCars::isInputValid(const vector<int> &endSlot2CarId, const vector<set<int>> *constraints) {
	bool atLeastOneCar = endSlot2CarId.size() >= 2 && this->startSlot2CarId.size() >= 2;
	bool slot2CarIdVectorsHaveSameSize = endSlot2CarId.size() == this->startSlot2CarId.size();
	bool constraintsSizeIsValid = constraints ? constraints->size() == this->startSlot2CarId.size() : true;  // Constraints should be either empty or have equal to number of slots size.
	bool startSlot2CarIdValid = isInputValidAux(this->startSlot2CarId, constraints);
	bool endSlot2CarIdValid = isInputValidAux(endSlot2CarId, constraints);

	return atLeastOneCar && slot2CarIdVectorsHaveSameSize && constraintsSizeIsValid && startSlot2CarIdValid && endSlot2CarIdValid;
}

bool RearrangeCars::isInputValidAux(const vector<int> &Slot2CarId, const vector<set<int>> *constraints) {
	bool foundEmptySlot = false;
	set<int> carIdHistogram;
	for (int slotId = 0; slotId < Slot2CarId.size(); slotId++) {
		int carId = Slot2CarId[slotId];

		// Make sure there is no more than one empty slot.
		if (carId == EMPTY_SLOT_ID) {
			if (foundEmptySlot) {
				return false;
			}
			else {
				foundEmptySlot = true;
			}
		}

		// Make sure that there are no duplicates in car IDs.
		if (carIdHistogram.find(carId) != carIdHistogram.end()) {  // This carId already exists.
			return false;
		}
		carIdHistogram.insert(carId);

		// Make sure that Slot2CarId follow constraints.
		if (!validMove(carId, slotId, constraints)) {
			return false;
		}
	}

	// Make sure there is an empty slot.
	return foundEmptySlot;
}
