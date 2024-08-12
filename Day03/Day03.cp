/*
 *  Advent of Code 2020, Day 3
 *	Toboggan Trajectory
 */

#include <iostream>
#include <memory>
#include <algorithm>

#include "Day03.h"
#include "AoC.h"

using namespace std;  //introduces namespace std

int SolveDay03()
{
	cout << "Day 03: Toboggan Trajectory" << endl;

	vector<string> input = aoc::ReadInputFile(aoc::INPUT_PATH + "03.test.txt", true);
	auto_ptr<TobogganHill> theHill (new TobogganHill(input));
	
	cout << "size of int:  " << sizeof(int) << endl;
	cout << "size of long: " << sizeof(long) << endl;
	cout << "size of long long: " << sizeof(long long) << endl;
	
	// Need to traverse the hill
	// Part 1: fall 1, run 3
	// Count the trees you hit.
	string t = theHill->GetTraverse(1, 3);
	// cout << t << endl;
	int impacts = count_if(t.begin(), t.end(), TobogganHill::IsTree);
	cout << impacts << endl;

	// Part 2: [1,1], [1,3]*, [1,5], [1,7], [2,1] 
	// * - already done
	// Count the hit trees on each and multiply results
	vector<int> allImpacts = vector<int>();
	allImpacts.push_back(impacts);
	
	int fValues[] = { 1, 1, 1, 2 };
	int n = sizeof(fValues) / sizeof(fValues[0]);
	vector<int> falls(fValues, fValues + n);
	
	int rValues[] = { 1, 5, 7, 1 };
	n = sizeof(rValues) / sizeof(rValues[0]);
	vector<int> runs(rValues, rValues + n);
	
	for (int i = 0; i < falls.size(); i++) {
		int fall = falls[i];
		int run  = runs [i];
		t = theHill->GetTraverse(fall, run);
		impacts = count_if(t.begin(), t.end(), TobogganHill::IsTree);
		cout << impacts << endl;
		allImpacts.push_back(impacts);
	}
	
	long long product = 1;
	for (int i = 0; i < allImpacts.size(); i++) {
		product *= allImpacts[i];
	}
	
	cout << "The product for part 2: " << product << endl;
	
	cout << endl;
	return 0;
}

TobogganHill::TobogganHill() {
	mHill = vector<string>();
}

TobogganHill::TobogganHill(vector<string> data) {
	mHill = data;
}

TobogganHill::~TobogganHill() {

}

int TobogganHill::GetHillHeight() {
	return mHill.size();
}

bool TobogganHill::IsTree(char terrain) {
	return terrain == TobogganHill::TREE;
}

char TobogganHill::GetTerrain(int fall, int run) {
	char terrain = ' ';
	if (fall < mHill.size()) {
		int index = run;
		string theRow = mHill[fall];
		while (index >= theRow.size()) {
			index -= theRow.size();
		}
		terrain = theRow[index];
		//cout << "row: " << fall << " pos: " << index << " -> " << terrain << endl;
	}
	return terrain;
}

string TobogganHill::GetTraverse(int fall, int run) {
	string traverse = "";
	
	int j = 0; // start at the first letter
	for (int i = 0; i < mHill.size(); i += fall) {
		traverse.push_back(GetTerrain(i,j));
		j += run;
	}
	return traverse;
}
