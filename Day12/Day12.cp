/*
 *  Advent of Code 2020, Day 12
 *  Rain Risk
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "AoC.h"
#include "Day12.h"

using namespace std;  //introduces namespace std

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day12_Input.txt", true);
	vector<Instruction> instructions = ParseInstructions(input);
	
	Boat boat;
	vector<Instruction>::iterator it;
	
	cout << "Part 1 - applying instructions to boat directly." << endl;
	for (it = instructions.begin(); it != instructions.end(); it++) {
		boat.Apply(*it);
	}
	
	cout << "Boat ended at (" << boat.GetX() << "," << boat.GetY() << ") facing " << boat.GetDir() << endl;
	cout << "Manhattan distance: " << ManhattanDistance(boat.GetX(), boat.GetY()) << endl;
	
	boat.Reset();
	
	cout << "Part 2 - applying instructions to waypoint." << endl;
	for (it = instructions.begin(); it != instructions.end(); it++) {
		boat.ApplyWithWaypoint(*it);
	}
	
	cout << "Boat ended at (" << boat.GetX() << "," << boat.GetY() << ")" << endl;
	cout << "Manhattan distance: " << ManhattanDistance(boat.GetX(), boat.GetY()) << endl;	
	
	return 0;
}

vector<Instruction> ParseInstructions(vector<string> const &input) {
	vector<Instruction> instructions;
	
	vector<string>::const_iterator it;
	for (it = input.begin(); it != input.end(); it++) {
		instructions.push_back(ParseInstruction(*it));
	}
	
	return instructions;
}

Instruction ParseInstruction(string const &line) {
	Instruction i;
	
	i.action = line[0];
	i.val = aoc::stoi(line.substr(1, string::npos));
	
	return i;
}

int ManhattanDistance(int x, int y) {
	return abs(x) + abs(y);
}

#pragma mark Boat Class Implementation

Boat::Boat() {
	Reset();
}

Boat::~Boat() {}

void Boat::Apply(Instruction i) {
	switch (i.action) {
		case 'N':
		case 'S':
		case 'E':
		case 'W':
			Move(i.action, i.val);
			break;
		case 'L':
			 // number of turns
			for (int n = i.val / 90; n > 0; n--)
				TurnLeft();
			break;
		case 'R':
			for (int n = i.val / 90; n > 0; n--)
				TurnRight();
			break;
		case 'F':
			Move(dir, i.val);
			break;
	}
}

void Boat::ApplyWithWaypoint(Instruction i) {
	switch (i.action) {
		case 'F':
			for (int n = 0; n < i.val; n++) {
				MoveBy(w.GetX(), w.GetY());
			}
			break;
		default:
			w.Apply(i);
	}
}

void Boat::TurnLeft() {
	switch (dir) {
		case 'N':
			dir = 'W';
			break;
		case 'W':
			dir = 'S';
			break;
		case 'S':
			dir = 'E';
			break;
		case 'E':
			dir = 'N';
			break;
	}
}

void Boat::TurnRight() {
	switch (dir) {
		case 'N':
			dir = 'E';
			break;
		case 'E':
			dir = 'S';
			break;
		case 'S':
			dir = 'W';
			break;
		case 'W':
			dir = 'N';
			break;
	}
}

void Boat::Move(char dir, int val) {
	switch (dir) {
		case 'N':
			y += val;
			break;
		case 'S':
			y -= val;
			break;
		case 'E':
			x += val;
			break;
		case 'W':
			x -= val;
			break;
	}
}

void Boat::MoveBy(int dx, int dy) {
	x += dx;
	y += dy;
}

int Boat::GetX() { return x; }

int Boat::GetY() { return y; }

char Boat::GetDir() { return dir; }

void Boat::Reset() {
	x = 0;
	y = 0;
	dir = 'E';
}

#pragma mark Waypoint Class Implementation

WayPoint::WayPoint() {
	x = 10;
	y = 1;
}

WayPoint::~WayPoint() {}

void WayPoint::Apply(Instruction i) {
	switch (i.action) {
		case 'N':
		case 'S':
		case 'E':
		case 'W':
			Move(i.action, i.val);
			break;
		case 'L':
			 // number of turns
			for (int n = i.val / 90; n > 0; n--)
				RotateLeft();
			break;
		case 'R':
			for (int n = i.val / 90; n > 0; n--)
				RotateRight();
			break;
	}
}

int WayPoint::GetX() { return x; }

int WayPoint::GetY() { return y; }

void WayPoint::RotateRight() {
	int temp = y;
	y = x * -1;
	x = temp;
}

void WayPoint::RotateLeft() {
	int temp = x;
	x = y * -1;
	y = temp;
}

void WayPoint::Move(char dir, int val) {
	switch (dir) {
		case 'N':
			y += val;
			break;
		case 'S':
			y -= val;
			break;
		case 'E':
			x += val;
			break;
		case 'W':
			x -= val;
			break;
	}
}
