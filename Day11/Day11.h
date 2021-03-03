/*
 *  Advent of Code 2020, Day 11
 *	Seating System
 */

#include <vector>
#include <string>

const char FLOOR = '.';
const char EMPTY = 'L';
const char OCC   = '#';

typedef char fn_eval(std::vector<std::string>const &, int, int);

std::vector<std::string> IterateSeating(std::vector<std::string>const &seating,
										fn_eval logic);

fn_eval Logic1;
fn_eval Logic2;

int CountAdjacentOccupied(std::vector<std::string>const &seating, int row, int col);
int CountVisibleOccupied(std::vector<std::string>const &seating, int row, int col);

bool IsOccupied(char spot);
bool IsValidSpot(int row, int col, int rmax, int cmax);
int CountOccupiedSeats(std::vector<std::string>const &seating);

void GenerateDirections();