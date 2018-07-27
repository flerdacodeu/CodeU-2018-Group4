#include"RearrangeCars.h"

RearrangeCars::RearrangeCars(const vector<int> &startStates) : startStates(startStates){}

void RearrangeCars::setStartStates(const vector<int> &startStates){
	this->startStates = startStates;
}

int RearrangeCars::findEmptySlotId(){
	for (int slotId = 0; slotId < this->startStates.size(); slotId++){
		if (this->startStates[slotId] == -1) return slotId; // no car has -1 id, it is reserved for empty slot
	}
	return -1; // This code should not be reached
}

vector<int> RearrangeCars::findCarPositions(const vector<int> &currentStates){
	vector<int> carPositions(currentStates.size() - 1);
	for (int i = 0; i < currentStates.size(); i++)
	{
		if (currentStates[i] != -1) // check for empty slot
			carPositions[currentStates[i]] = i;
	}
	return carPositions;
}

int RearrangeCars::findMisplacedCar(const vector<int> &carPosition, const vector<int> &endStates){
	for (int carId = 0; carId < carPosition.size(); carId++){
		if (endStates[carPosition[carId]] != carId) return carId;
	}
	return -1; // If every car is on its slot
}

void RearrangeCars::moveCar(vector<int> &currentStates, vector<int> &carPosition, int from, int to){
	currentStates[to] = currentStates[from];
	currentStates[from] = -1;
	carPosition[currentStates[to]] = to;
}

void RearrangeCars::generateSequenceOfMoves(const vector<int> &endStates, vector<Move> &sequenceOfMoves){
	vector<int> currentStates = this->startStates; // startStates will remain unchanged
	vector<int> carPosition = findCarPositions(currentStates);
	
	int emptySlotId = findEmptySlotId();
	int currCarId, currCarSlotId;
	
	while (true){
		currCarId = endStates[emptySlotId];
		if (currCarId == -1) // We reached slot which should be empty in the end
			currCarId = findMisplacedCar(carPosition, endStates);
		if (currCarId == -1) break; 
		currCarSlotId = carPosition[currCarId];
		moveCar(currentStates, carPosition, currCarSlotId, emptySlotId);
		sequenceOfMoves.push_back(Move(currCarId, currCarSlotId, emptySlotId));
		emptySlotId = currCarSlotId;
	}
}