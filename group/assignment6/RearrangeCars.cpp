#include "RearrangeCars.h"

RearrangeCars::RearrangeCars(const vector<int> &startStates) : startStates(startStates) {}

void RearrangeCars::setStartStates(const vector<int> &startStates) {
      this->startStates = startStates;
}

int RearrangeCars::findEmptySlotId() {
      for (int slotId = 0; slotId < this->startStates.size(); slotId++) {
            if (this->startStates[slotId] == EMPTY_SLOT_ID)
                  return slotId;                // no car has EMPTY_SLOT_ID id, it is reserved for empty slot
      }

      return -1;        // This code should not be reached
}

vector<int> RearrangeCars::findCarPositions(const vector<int> &currentStates) {
      vector<int> carPositions(currentStates.size() - 1);
      for (int i = 0; i < currentStates.size(); i++) {
            if (currentStates[i] != EMPTY_SLOT_ID)                // check for empty slot
                  carPositions[currentStates[i]] = i;
      }

      return carPositions;
}

void RearrangeCars::moveCar(vector<int> &currentStates, vector<int> &carPosition, int from, int to) {
      currentStates[to] = currentStates[from];
      currentStates[from] = EMPTY_SLOT_ID;
      carPosition[currentStates[to]] = to;
}

bool RearrangeCars::validMove(int carId, int emptySlotId, const vector<set<int>> *constraints) {
      if (!constraints)        // Constraints are not set
            return true;

      if (constraints[emptySlotId].empty()) // There are no constraints for this parking space, any car can be moved here
            return true;

      if (((*constraints)[emptySlotId]).find(carId) == ((*constraints)[emptySlotId].end()))
            return true;

      return false;
}

int RearrangeCars::numberOfCarsOnTheirDesiredPositions(const vector<int> &carPosition, const vector<int> &endStates) {
      int count = 0;
      for (int i = 0; i < carPosition.size(); i++)
            if (endStates[carPosition[i]] == i)
                  count++;

      return count;
}

int RearrangeCars::findMisplacedCar(vector<int> &carPosition, vector<int> &currentStates, const vector<int> &endStates,
                                    const vector<set<int>> *constraints, vector<Move> &sequenceOfMoves,
                                    int &emptySlotId, int &numOfCarsOnDisiredPosition) {
      int lastMovedCarId = -1;
      int currCarSlotId;

      while (true) {
            currCarSlotId = endStates[emptySlotId];
            if (lastMovedCarId != currCarSlotId && currCarSlotId != EMPTY_SLOT_ID) {
                  return currCarSlotId;
            }

            // Find a misplaced car that can be moved here
            bool foundMisplacedCar = false;
            for (int carId = 0; carId < carPosition.size(); carId++) {
                  if (lastMovedCarId != carId && endStates[carPosition[carId]] != carId &&
                      validMove(carId, emptySlotId, constraints)) {
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

bool RearrangeCars::generateSequenceOfMoves(const vector<int> &endStates, vector<Move> &sequenceOfMoves,
                                            const vector<set<int>> *constraints) {
      sequenceOfMoves.clear();
      if (!isInputValid(endStates, constraints)) {
            return false;
      }
      vector<int> currentStates = this->startStates; // startStates will remain unchanged
      vector<int> carPosition = findCarPositions(currentStates);

      int emptySlotId = findEmptySlotId();
      int currCarId, currCarSlotId;
      int numOfCarsOnDisiredPosition = numberOfCarsOnTheirDesiredPositions(carPosition, endStates);

      while (true) {
            currCarId = endStates[emptySlotId];
            if (currCarId == EMPTY_SLOT_ID) // We have reached slot which should be empty in the end
                  currCarId = findMisplacedCar(carPosition, currentStates, endStates, constraints,
                                               sequenceOfMoves, emptySlotId, numOfCarsOnDisiredPosition);

            currCarSlotId = carPosition[currCarId];
            moveCar(currentStates, carPosition, currCarSlotId, emptySlotId);
            numOfCarsOnDisiredPosition++;
            sequenceOfMoves.push_back(Move(currCarId, make_pair(currCarSlotId, emptySlotId)));
            emptySlotId = currCarSlotId;

            if (numOfCarsOnDisiredPosition == carPosition.size())
                  break;
      }
      return true;
}

void
RearrangeCars::bruteForceAllSequence(vector<int> &currentStates, const vector<int> &endStates, vector<int> &carPosition,
                                     int emptySlotId, vector<Move> &sequenceOfMoves,
                                     vector<vector<Move>> &sequencesOfMoves, set<vector<int>> &usedPositions,
                                     const vector<set<int>> *constraints) {
      int numOfCarsOnDisiredPosition = numberOfCarsOnTheirDesiredPositions(carPosition, endStates);
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
                        sequenceOfMoves.push_back(
                              Move(currentStates[emptySlotId], make_pair(currCarSlotId, emptySlotId)));
                        bruteForceAllSequence(currentStates, endStates, carPosition, currCarSlotId,
                                              sequenceOfMoves, sequencesOfMoves, usedPositions, constraints);
                        sequenceOfMoves.pop_back();
                        usedPositions.erase(usedPositions.find(carPosition));
                  }

                  // we want to swap again and return to our currentStates for next try
                  moveCar(currentStates, carPosition, emptySlotId, currCarSlotId);
            }
      }
}

bool RearrangeCars::generateAllSequencesOfMoves(const vector<int> &endStates, vector<vector<Move>> &sequencesOfMoves,
                                                const vector<set<int>> *constraints) {
      sequencesOfMoves.clear();
      if (!isInputValid(endStates, constraints)) {
            return false;
      }
      vector<int> currentStates = this->startStates;
      vector<int> carPosition = findCarPositions(currentStates);

      int emptySlotId = findEmptySlotId();
      vector<Move> sequenceOfMoves;
      set<vector<int>> usedPositions;
      usedPositions.insert(carPosition);
      bruteForceAllSequence(currentStates, endStates, carPosition, emptySlotId, sequenceOfMoves, sequencesOfMoves,
                            usedPositions, constraints);
      return true;
}

bool RearrangeCars::isInputValid(const vector<int> &endStates, const vector<set<int>> *constraints) {
      bool atLeastOneCar = endStates.size() >= 2 && this->startStates.size() >= 2;
      bool stateVectorsHaveSameSize = endStates.size() == this->startStates.size();
      bool startStatesValid = isInputValidAux(this->startStates, constraints);
      bool endStatesValid = isInputValidAux(endStates, constraints);

      return atLeastOneCar && stateVectorsHaveSameSize && startStatesValid && endStatesValid;
}

bool RearrangeCars::isInputValidAux(const vector<int> &states, const vector<set<int>> *constraints) {
      bool foundEmptySlot = false;
      set<int> carIdHistogram;
      for (int slotId = 0; slotId < states.size(); slotId++) {
            int carId = states[slotId];

            // make sure there is not more than one empty slot
            if (carId == EMPTY_SLOT_ID) {
                  if (foundEmptySlot) {
                        return false;
                  } else {
                        foundEmptySlot = true;
                  }
            }

            // make sure there are no duplicates in car IDs
            if (carIdHistogram.find(carId) != carIdHistogram.end()) { // this carId already exists
                  return false;
            }
            carIdHistogram.insert(carId);

            // make sure states follows constraints
            if (!validMove(carId, slotId, constraints)) {
                  return false;
            }
      }

      // make sure there is an empty slot
      return foundEmptySlot;
}