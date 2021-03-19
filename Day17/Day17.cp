/*
 *  Advent of Code 2020, Day 17
 *  Conway Cubes
 */

#include <iostream>
#include <algorithm>
#include <cmath>

#include "AoC.h"
#include "Day17.h"

using namespace std;  //introduces namespace std

const int ITER_COUNT = 6;
const char ACTIVE = '#';
const char INACTIVE = '.';

int main()
{
	vector< vector< string > > inputs = aoc::ReadGroupedInputFile("Day17_Input.txt");
	
	ConwayPocket pocket(3);
	
	pocket.LoadData(inputs[1]);
	
	int activeCount = 0;
	for (int iter = 0; iter < ITER_COUNT; iter++) {
		activeCount = pocket.Iterate();
		cout << iter << ": Active count: " << activeCount << endl;
	}
		
	return 0;
}

// --------------------------------------------------
#pragma mark ConwayPocket
// --------------------------------------------------

ConwayPocket::ConwayPocket() {
	mDimensionCount = 3;
}

ConwayPocket::ConwayPocket(int n_dimensions = 0) {
	mDimensionCount = n_dimensions;
}

ConwayPocket::~ConwayPocket() {}

bool ConwayPocket::IsActive(vector<int> key) {
	if (mState.find(key) == mState.end()) {
		// Does not exist. Return false.
		return false;
	}
	return mState[key];
}

int ConwayPocket::Iterate() {	
	// Fill in all the cells around expanded bounds
	vector< vector<int> > borderKeys;
	
	map< vector<int>, bool >::iterator it;
	for (it = mState.begin(); it != mState.end(); it++) {
		vector<int> key = it->first;
		vector< vector<int> > nKeys = GetNeighbourKeys(key);
		vector< vector<int> >::iterator nit;
		for (nit = nKeys.begin(); nit != nKeys.end(); nit++) {
			vector<int> nKey = *nit;
			if (mState.find(nKey) == mState.end()) {
				// This wasn't a pre-existing key
				borderKeys.push_back(nKey);
			}
		}
	}
	
	// Add the border keys to mState
	vector< vector<int> >::iterator bkit;
	for (bkit = borderKeys.begin(); bkit != borderKeys.end(); bkit++) {
		vector<int> key = *bkit;
		mState[key] = false;
	}
	
	cout << "Key count: " << mState.size() << endl;
	
	// Create a new map with the new cell states
	map< vector<int>, bool > nextGenState;
	for (it = mState.begin(); it != mState.end(); it++) {
		int activeCount = 0;
		vector<int> key = it->first;
		vector< vector<int> > nKeys = GetNeighbourKeys(key);
		vector< vector<int> >::iterator nit;
		for (nit = nKeys.begin(); nit != nKeys.end(); nit++) {
			vector<int> nKey = *nit;
			if (IsActive(nKey)) {
				activeCount++;
			}
		}
		
		if (IsActive(key)) {
			if (activeCount < 2 || activeCount > 3) {
				//cout << "activeCount for " << key << " is " << activeCount << " flipping to inactive." << endl;
				nextGenState[key] = false;
			}
			else {
				nextGenState[key] = true;
			}
		}
		else {
			if (activeCount == 3) {
				//cout << "activeCount for " << key << " is " << activeCount << " flipping to active." << endl;
				nextGenState[key] = true;
			}
			else {
				nextGenState[key] = false;
			}
		}
	}
	
	mState = nextGenState;
	
	return CountActive();
}

int ConwayPocket::CountActive() {
	int count = 0;
	map< vector<int>, bool >::iterator it;
	for (it = mState.begin(); it != mState.end(); it++) {
		bool isActive = it->second;
		if (isActive)
			count++;
	}
	return count;
}

void ConwayPocket::LoadData(vector<string> data) {
	mState.empty();
		
	for (int y = 0; y < data.size(); y++) {
		for (int x = 0; x < data[y].size(); x++) {
			int arr[] = {x,y};
			vector<int> coords (arr, arr + sizeof(arr) / sizeof(int));
			
			// Add as many dimensions beyond as needed
			while (coords.size() < mDimensionCount) {
				coords.push_back(0);
			}
			
			if (data[y][x] == ACTIVE) {
				mState[coords] = true;
			}
			else {
				mState[coords] = false;
			}
		}
	}
	
}


// --------------------------------------------------
#pragma mark Utility functions
// --------------------------------------------------

map<int, vector<int> > _offsets;

vector<int> NumToTernary(int num, int pad) {
	if (_offsets.find(num) != _offsets.end()) {
		return _offsets[num];
	}
	
	vector<int> ternaryNum;
	
	while (num > 0) {
		ternaryNum.push_back(num % 3);
		num = num / 3;
	}
	
	while (ternaryNum.size() < pad) {
		ternaryNum.push_back(0);
	}
	
	reverse(ternaryNum.begin(), ternaryNum.end());
	for (int j = 0; j < ternaryNum.size(); j++) {
		if (ternaryNum[j] == 2) {
			ternaryNum[j] = -1;
		}
	}
	
	_offsets[num] = ternaryNum;
	
	return ternaryNum;
}

vector< vector<int> > GetNeighbourKeys(vector<int> const &coords) {
	vector< vector<int> > nkeys;
	for (int i = 0; i < pow(3, coords.size()); i++) {
		vector<int> offsets = NumToTernary(i, coords.size());
		
		vector<int> offsetCoords;
		for (int k = 0; k < coords.size(); k++) {
			offsetCoords.push_back(coords[k] + offsets[k]);
		}

		if (offsetCoords != coords) {
			nkeys.push_back(offsetCoords);
		}
	}
	return nkeys;
}
