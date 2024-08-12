/*
	Advent of Code 2020, Day 1
	Report Repair
*/

#include <iostream>
#include <set>


#include "Day01.h"
#include "AoC.h"

using namespace std;  //introduces namespace std

const int TARGET_AMOUNT = 2020;

vector<int> ReadExpenseAmounts();
int SolveForTwo(vector<int> amounts);
int SolveForThree(vector<int> amounts);

int SolveDay01()
{
	cout << "Day 01: Report Repair" << endl;

	vector<int> amounts = ReadExpenseAmounts();
	
	int product2 = SolveForTwo(amounts);
	cout << "The product is " << product2 << endl;
	
	int product3 = SolveForThree(amounts);
	cout << "The product is " << product3 << endl;
	
	cout << endl;
	return 0;
}

int SolveForTwo(vector<int> amounts) {
	set<int> expenseLookup;
	
	vector<int>::iterator it;
	for (it = amounts.begin(); it != amounts.end(); it++) {
		expenseLookup.insert(*it);
	}
	
	set<int>::iterator it_int;
	for (it_int = expenseLookup.begin(); it_int != expenseLookup.end(); it_int++) {
		int amount = *it_int;
		int diff = TARGET_AMOUNT - amount;
		if (expenseLookup.find(diff) != expenseLookup.end()) {
			cout << diff << " and " << amount << " add to $" << TARGET_AMOUNT << endl;
			return diff*amount;
		}
	}
	return 0;
}

int SolveForThree(vector<int> amounts) {
	vector<int>::iterator it_1;
	vector<int>::iterator it_2;
	vector<int>::iterator it_3;
	
	for (it_1 = amounts.begin(); it_1 != amounts.end(); it_1++) {
		for (it_2 = amounts.begin(); it_2 != amounts.end(); it_2++) {
			for (it_3 = amounts.begin(); it_3 != amounts.end(); it_3++) {
				if (*it_1 + *it_2 + *it_3 == TARGET_AMOUNT) {
					cout << *it_1 << " + " << *it_2 << " + " << *it_3 << " add to $" << TARGET_AMOUNT << endl;
					return *it_1 * *it_2 * *it_3;
				}
			}
		}
	}
	
	return 0;
}

vector<int> ReadExpenseAmounts() {
	
	vector<string> input;
	input = aoc::ReadInputFile(aoc::INPUT_PATH + "01.challenge.txt", true);
	
	vector<int> amounts;
	vector<string>::iterator it;
	
	for (it = input.begin(); it != input.end(); it++) {
		amounts.push_back(aoc::stoi(*it));
	}
	
	return amounts;
}