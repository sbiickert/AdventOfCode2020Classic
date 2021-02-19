/*
 *  Advent of Code 2020, Day 5
 *	Binary Boarding
 */

#include <string>

struct Seat {
	int row;
	int col;
};

Seat ParseSeat(std::string code);