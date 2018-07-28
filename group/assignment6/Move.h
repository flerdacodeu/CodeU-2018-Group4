#ifndef MOVE_H
#define MOVE_H
#pragma once

struct Move
{
	int carId;
	std::pair<int, int> positions;

	Move() {}
	Move(int carId, std::pair<int, int> positions) : carId(carId), positions(positions){}

	friend std::ostream& operator<<(std::ostream& os, const Move& move) {
		os << "Move car #" << move.carId << " from space " << move.positions.first << " to " << move.positions.second << std::endl;
		return os;
	}
};

#endif
