/*
 *  Advent of Code 2020, Day 9
 *	Encoding Error
 */

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

#include "AoC.h"
#include "Day09.h"

using namespace std;  //introduces namespace std

const int BUFFER_SIZE = 25;

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day9_Input.txt", true);
	vector<string>::iterator it;
	
	vector<long long> buffer;
	long long value = 0;
	
	for (it = input.begin(); it != input.end(); it++) {
		value = aoc::stol(*it);
		
		if (buffer.size() >= BUFFER_SIZE) { //Only start eval after reading 25 numbers
			// Evaluate value
			if (FindFlaw(buffer, value) == false)
				break;
		}
		
		buffer.push_back(value);
	}
	
	cout << "The flaw: " << value << endl;
	
	long long weakness = GetWeakness(buffer, value);
	cout << "The weakness: " << weakness << endl;
	
	return 0;
}

bool FindFlaw(vector<long long> buffer, long long value) {
	int size = buffer.size();
	
	int start = size - BUFFER_SIZE;
	for (int i = start; i < size-1; i++) {
		for (int j = i+1; j < size; j++) {
			if (buffer[i] + buffer[j] == value) {
				//cout << buffer[i] << " + " << buffer[j] << " = " << value << endl;
				return true;
			}
		}
	}
	
	return false;
}

long long GetWeakness(vector<long long> buffer, long long value) {
	vector<long long>::iterator start_it;
	for (start_it = buffer.begin(); start_it != buffer.end(); start_it++) {
		// end iterator starts at 1 step beyond start iterator
		vector<long long>::iterator end_it(start_it);
		end_it++;
		
		for (; end_it != buffer.end(); end_it++) {
			if (accumulate(start_it, end_it, 0) == value) {
				// cout << "Numbers from " << *start_it << " to " << *end_it << " add to " << value << endl;
				// Sort the range of numbers so smallest is first, largest is last
				vector<long long> range = vector<long long>(start_it, end_it);
				sort(range.begin(), range.end());
				// Add the smallest and largest
				long long weakness = range.front() + range.back();
				return weakness;
			}
		}
	}	
	return 0;
}
