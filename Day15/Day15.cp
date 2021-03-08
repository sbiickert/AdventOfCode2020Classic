/*
 *  Advent of Code 2020, Day 15
 *  Rambunctious Recitation
 */

#include <iostream>
#include <map>

#include "AoC.h"
#include "Day15.h"

//#include "Profiler.h"

using namespace std;  //introduces namespace std

int main()
{	
	//OSErr err;
	//err = ProfilerInit(collectDetailed, bestTimeBase, 20, 5);

	string input = "15,5,1,4,7,0";
	vector<string> result = aoc::split(input, ",");
	
	int max_turns = 2020;
	int value_at_end = PlayMemoryGame(result, max_turns);
	cout << "Value at turn " << max_turns << ": " << value_at_end << endl;
	
	//err = ProfilerDump("\pDay15.prof");
	
	//return 0;
	
	max_turns = 30000000;	
	value_at_end = PlayMemoryGame(result, max_turns);
	cout << "Value at turn " << max_turns << ": " << value_at_end << endl;
	
	return 0;
}

int PlayMemoryGame(std::vector<std::string> const &input, int iterations)
{
	map<int, NumberHistory> gameState;
	int lastNumberPlayed = 0;
	
	for (int turn = 0; turn < iterations; turn++) {
		if (turn < input.size()) {
			// Reading the initial game input
			int val = aoc::stoi(input[turn]);
			NumberHistory nh(val, turn);
			gameState[val] = nh;
			lastNumberPlayed = val;
		}
		else {
			int val = 0; // default if the lastNumberPlayed is new
			if (gameState[lastNumberPlayed].HasBeenSpokenBefore()) {
				val = gameState[lastNumberPlayed].GetAge();
			}
			if (gameState.count(val) == 1) {
				gameState[val].SetMostRecentTurn(turn);
			}
			else {
				NumberHistory nh(val, turn);
				gameState[val] = nh;
			}
			lastNumberPlayed = val;
		}
		
		if (turn % 1000000 == 0)
			cout << turn << endl;
	}
	
	return lastNumberPlayed;
}

#pragma mark NumberHistory implementation

NumberHistory::NumberHistory() {
	number = -1;
	mostRecentTurn = -1;
	previousTurn = -1;
}

NumberHistory::NumberHistory(int num, int turn) {
	number = num;
	mostRecentTurn = turn;
	previousTurn = -1;
}

NumberHistory::~NumberHistory() {}

int NumberHistory::GetNumber() {
	return number;
}

int NumberHistory::GetMostRecentTurn() {
	return mostRecentTurn;
}

void NumberHistory::SetMostRecentTurn(int turn) {
	previousTurn = mostRecentTurn;
	mostRecentTurn = turn;
}

bool NumberHistory::HasBeenSpokenBefore() {
	return previousTurn >= 0;
}

int NumberHistory::GetAge() {
	return mostRecentTurn - previousTurn;
}
