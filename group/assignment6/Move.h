#ifndef MOVE_H
#define MOVE_H
#pragma once

struct Move
{
	int carId;
	int startPosition;
	int endPosition;

	Move() {}
	Move(int carId, int startPosition, int endPosition) : carId(carId), startPosition(startPosition), endPosition(endPosition){}

	friend std::ostream& operator<<(std::ostream& os, const Move& move) {
		os << "Move car #" << move.carId << " from space " << move.startPosition << " to " << move.endPosition << std::endl;
		return os;
	}
};

#endif