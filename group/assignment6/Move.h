#ifndef MOVE_H
#define MOVE_H

#include <iostream>

using namespace std;

struct Move {
	int carId;
	pair<int, int> positions;

	Move() {}
	Move(int carId, pair<int, int> positions) : carId(carId), positions(positions) {}

	friend ostream& operator<<(ostream& os, const Move& move) {
		os << "Move car #" << move.carId << " from space " << move.positions.first << " to " << move.positions.second << endl;
		return os;
	}
};

#endif
