/*
 *  Advent of Code 2020, Day 10
 *	Adapter Array
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

#include "AoC.h"

using namespace std;  //introduces namespace std

const int MIN_DELTA = 1;
const int MAX_DELTA = 3;

vector<int> joltages; // Sorted list of adapter joltages

bool _IsOne(int i);
bool _IsThree(int i);
int CalcProduct();
long long CountCombinations();

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day10_Input.txt", true);
	vector<string>::iterator input_it;
	
	for (input_it = input.begin(); input_it != input.end(); input_it++) {
		joltages.push_back(aoc::stoi(*input_it));
	}
	sort(joltages.begin(), joltages.end());
	
	// The last diff is to the device, defined as MAX_DELTA
	joltages.push_back(joltages.back() + MAX_DELTA);
	
	int product = CalcProduct();
	
	cout << "The product for Part 1: " << product << endl;
	
	long long combinations = CountCombinations();
	
	cout << "The number of combinations for Part 2: " << combinations << endl;
	
	return 0;
}

// Would like these functions to be lambdas, but no such thing in C++98
bool _IsOne(int i) {
	return i == 1;
}

bool _IsThree(int i) {
	return i == 3;
}

int CalcProduct() {
	vector<int> diffs;
	
	int lastJoltage = 0;
	
	vector<int>::iterator it;
	for (it = joltages.begin(); it != joltages.end(); it++) {
		int diff = *it - lastJoltage;
		if (diff >= MIN_DELTA && diff <= MAX_DELTA) {
			diffs.push_back(diff);
		}
		lastJoltage = *it;
	}
	
	int countMinDeltas = count_if(diffs.begin(), diffs.end(), _IsOne);
	int countMaxDeltas = count_if(diffs.begin(), diffs.end(), _IsThree);
	
	return countMinDeltas * countMaxDeltas;
}

long long CountCombinations() {
	map<int,long long> sol;
	sol[0] = 1;
	
	vector<int>::iterator it;
	for (it = joltages.begin(); it != joltages.end(); it++) {
		int joltage = *it;
		sol[joltage] = 0;
		
		if (sol.count(joltage-1) == 1) {
			sol[joltage] += sol[joltage-1];
		}
		if (sol.count(joltage-2) == 1) {
			sol[joltage] += sol[joltage-2];
		}
		if (sol.count(joltage-3) == 1) {
			sol[joltage] += sol[joltage-3];
		}
	}
	
	return sol[joltages.back()];
}