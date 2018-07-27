#ifndef REARRANGECARS_H
#define REARRANGECARS_H

#include<iostream>
#include<vector>
#include<queue>
#include"Move.h"
using namespace std;

class RearrangeCars{
private:
	vector<int> startStates;

public:
	RearrangeCars(const vector<int> &startStates);
	~RearrangeCars() = default;
	void setStartStates(const vector<int> &startStates);
	void generateSequenceOfMoves(const vector<int> &endStates, vector<Move> &sequenceOfMoves);

private:
	int findEmptySlotId();
	vector<int> findCarPositions(const vector<int> &currentStates);
	int findMisplacedCar(const vector<int> &carPosition, const vector<int> &endStates);
	void RearrangeCars::moveCar(vector<int> &currentStates, vector<int> &carPosition, int from, int to);
};

#endif