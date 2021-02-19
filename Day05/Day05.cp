/*
 *  Advent of Code 2020, Day 5
 *	Binary Boarding
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "Day05.h"
#include "AoC.h"

using namespace std;  //introduces namespace std

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day5_Input.txt", true);
	
	vector<Seat> seats;
	vector<string>::iterator it;
	for (it = input.begin(); it != input.end(); it++) {
		seats.push_back(ParseSeat(*it));
	}
	
	cout << "Parsed seats: " << seats.size() << endl;
	
	vector<int> ids;
	vector<Seat>::iterator s_it;
	for (s_it = seats.begin(); s_it != seats.end(); s_it++) {
		ids.push_back(s_it->row * 8 + s_it->col);
	}
	
	sort(ids.begin(), ids.end());
	
	int lastID = ids[ids.size()-1];
	cout << "Highest id: " << lastID << endl;
	
	set<int> idSet(ids.begin(), ids.end());
	// We aren't the first seat, so start at the second id
	for (int i = ids[1]; i < lastID; i++) {
		if (idSet.find(i) == idSet.end()) {
			cout << "My seat is: " << i << endl;
			break;
		}
	}
	
	return 0;
}

Seat ParseSeat(string code) {
	// First 7 characters are F, B (i.e. 0 and 1)
	// Last 3 characters are L, R (i.e. 0 and 1)
	Seat s;

	for (int i = 0; i < code.size(); i++) {
		if (code[i] == 'F') {
			code[i] = '0';
		}
		if (code[i] == 'B') {
			code[i] = '1';
		}
		if (code[i] == 'L') {
			code[i] = '0';
		}
		if (code[i] == 'R') {
			code[i] = '1';
		}
	}
	
	char * pEnd;
	s.row = strtol(code.substr(0, 7).c_str(), &pEnd, 2);
	s.col = strtol(code.substr(7, 3).c_str(), &pEnd, 2);
	
	return s;
}