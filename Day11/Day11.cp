/*
 *  Advent of Code 2020, Day 11
 *	Seating System
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "AoC.h"
#include "Day11.h"

//#include "Profiler.h"

using namespace std;  //introduces namespace std

vector<pair<int,int> > directions;

int main()
{	
	//OSErr err;
	//err = ProfilerInit(collectDetailed, bestTimeBase, 20, 5);
	vector<string> input = aoc::ReadInputFile("Day11_Input.txt", true);
	
	vector<string> seating(input);

	int occupiedSeatCount = CountOccupiedSeats(seating);
	int lastOccupiedSeatCount = -1;
	
	while (occupiedSeatCount != lastOccupiedSeatCount) {
		lastOccupiedSeatCount = occupiedSeatCount;
		seating = IterateSeating(seating, Logic1);
		occupiedSeatCount = CountOccupiedSeats(seating);
		cout << "Occupied seats: " << occupiedSeatCount << endl;
	}
	
	cout << "Part 1 occupied seats at stable count: " << occupiedSeatCount << endl;
	
	//err = ProfilerDump("\pDay11.prof");
	
	//return 0;
	GenerateDirections();
	seating = input;
	
	occupiedSeatCount = CountOccupiedSeats(seating);
	lastOccupiedSeatCount = -1;
	while (occupiedSeatCount != lastOccupiedSeatCount) {
		lastOccupiedSeatCount = occupiedSeatCount;
		seating = IterateSeating(seating, Logic2);
		occupiedSeatCount = CountOccupiedSeats(seating);
		cout << "Occupied seats: " << occupiedSeatCount << endl;
	}
	
	cout << "Part 2 occupied seats at stable count: " << occupiedSeatCount << endl;
	
	
	return 0;
}

vector<string> IterateSeating(vector<string>const &seating,
							  fn_eval logic) {
	vector<string> updated(seating);
	for (int row = 0; row < seating.size(); row++) {
		for (int col = 0; col < seating[row].size(); col++) {
			updated[row][col] = logic(seating, row, col);
		}
	}
	return updated;
}


char Logic1(vector<string>const &seating, int row, int col) {
	/*
	 * FLOOR: stays same
	 * EMPTY: becomes OCC if there are no adjacent OCC seats
	 * OCC:   becomes EMPTY if 4 or more adjacent OCC seats
	 */
	int occCount;
	switch (seating[row][col]) {
		case EMPTY:
			occCount = CountAdjacentOccupied(seating, row, col);
			if (occCount == 0)
				return OCC;
			return EMPTY;
		case OCC:
			occCount = CountAdjacentOccupied(seating, row, col);
			if (occCount >= 4)
				return EMPTY;
			return OCC;
	}
	return FLOOR;
}

bool IsValidSpot(int row, int col, int rmax, int cmax) {
	if (row >= 0 && row <= rmax && col >= 0 && col <= cmax) {
		return true;
	}
	return false;
}

int CountAdjacentOccupied(std::vector<std::string>const &seating, int row, int col) {
	int rmax = seating.size()-1;
	int cmax = seating[0].size()-1;
	
	int count = 0;
	for (int r = row-1; r <= row+1; r++) {
		for (int c = col-1; c <= col+1; c++) {
			if (IsValidSpot(r, c, rmax, cmax)) {
				if ((r == row && c == col) == false) {
					if (seating[r][c] == OCC) {
						count++;
					}
				}
			}
		}
	}
	return count;
}

void GenerateDirections() {
	directions.push_back(make_pair(-1, -1));
	directions.push_back(make_pair(-1,  0));
	directions.push_back(make_pair(-1,  1));
	directions.push_back(make_pair( 0, -1));
	directions.push_back(make_pair( 0,  1));
	directions.push_back(make_pair( 1, -1));
	directions.push_back(make_pair( 1,  0));
	directions.push_back(make_pair( 1,  1));
}

char Logic2(vector<string>const &seating, int row, int col) {
	/*
	 * FLOOR: stays same
	 * EMPTY: becomes OCC if there are no visible OCC seats
	 * OCC:   becomes EMPTY if 5 or more visible OCC seats
	 */
	int occCount;
	switch (seating[row][col]) {
		case EMPTY:
			occCount = CountVisibleOccupied(seating, row, col);
			if (occCount == 0)
				return OCC;
			return EMPTY;
		case OCC:
			occCount = CountVisibleOccupied(seating, row, col);
			if (occCount >= 5)
				return EMPTY;
			return OCC;
	}
	return FLOOR;
}


int CountVisibleOccupied(std::vector<std::string>const &seating, int row, int col) {
	int rmax = seating.size()-1;
	int cmax = seating[0].size()-1;
	
	int count = 0;
	vector<pair<int, int> >::iterator it;
	for (it = directions.begin(); it != directions.end(); it++) {
		int r, c = 0;
		r = row + it->first;
		c = col + it->second;
		while (IsValidSpot(r, c, rmax, cmax) && seating[r][c] == FLOOR) {
			r += it->first;
			c += it->second;
		}
		if (IsValidSpot(r, c, rmax, cmax) && seating[r][c] == OCC) {
			count++;
		}
	}
	return count;
}

bool IsOccupied(char spot) {
	return spot == OCC;
}

int CountOccupiedSeats(vector<string>const &seating) {
	int count = 0;
	
	vector<string>::const_iterator it;
	for (it = seating.begin(); it != seating.end(); it++) {
		string row = *it;
		int rowCount = count_if(row.begin(), row.end(), IsOccupied);
		count += rowCount;
	}
	return count;
}