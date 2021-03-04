/*
 *  Advent of Code 2020, Day 13
 *  Shuttle Search
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "AoC.h"

using namespace std;  //introduces namespace std

const int NONE = -1;

vector<int> ParseBusSchedule(string);
vector<int> SortedBusIDs(vector<int> schedule);
long long CalcTimeSinceDepart(int);
void Part1(vector<int> const&);
void Part2(vector<int> const&);

int earliestDepartTime;

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day13_Input.txt", true);
	
	earliestDepartTime = aoc::stoi(input[0]);
	vector<int> busSched = ParseBusSchedule(input[1]);
	
	vector<int> busIDs = SortedBusIDs(busSched);
	Part1(busIDs);
	Part2(busSched);
	
	return 0;
}

vector<int> ParseBusSchedule(string csv) {
	// Comma-separated string of bus ids and x's.
	// Make space-separated
	size_t pos = csv.find(",");
	while (pos != string::npos) {
		csv.replace(pos, 1, " ");
		pos = csv.find(",", pos+1);
	}
	
	istringstream iss(csv);
	vector<string> result((istream_iterator<string>(iss)), istream_iterator<string>());
	
	vector<int> sched;
	vector<string>::iterator it;
	
	for(it = result.begin(); it != result.end(); it++) {
		string value = *it;
		if (value[0] != 'x') {
			sched.push_back(aoc::stoi(value));
		}
		else {
			sched.push_back(NONE);
		}
	}
	
	return sched;
}

vector<int> SortedBusIDs(vector<int> schedule) {
	vector<int> ids;
	vector<int>::iterator it;
	
	for(it = schedule.begin(); it != schedule.end(); it++) {
		int value = *it;
		if (value != NONE) {
			ids.push_back(value);
		}
	}
	sort(ids.begin(), ids.end());
	
	return ids;
}

long long delay;
long long CalcTimeSinceDepart(int i) {
	return (earliestDepartTime + delay) % i;
};

void Part1(vector<int> const &busIDs) {
	cout << aoc::vtos(busIDs) << endl;
	
	delay = 0;
	
	vector<long long> timesSinceDepart(busIDs.begin(), busIDs.end());
	transform(timesSinceDepart.begin(), timesSinceDepart.end(),
			  timesSinceDepart.begin(), CalcTimeSinceDepart);
	cout << aoc::vtos(timesSinceDepart) << endl;

	while (count(timesSinceDepart.begin(), timesSinceDepart.end(), 0) == 0) {
		delay++;
		timesSinceDepart = vector<long long>(busIDs.begin(), busIDs.end());
		transform(timesSinceDepart.begin(), timesSinceDepart.end(),
				  timesSinceDepart.begin(), CalcTimeSinceDepart);
		cout << aoc::vtos(timesSinceDepart) << endl;
	}
	
	long long *ptr = find(timesSinceDepart.begin(), timesSinceDepart.end(), 0);
	int busIndex = ptr - timesSinceDepart.begin();
	
	cout << "Bus " << busIDs[busIndex] << " is the first to depart with a delay of " << delay << endl;
	cout << "Part 1 answer: " << busIDs[busIndex] * delay << endl << endl;
}

void Part2(vector<int> const &busSched) {

	vector<int> busIDs;
	vector<int> offsets;
	vector<int> lookingFor;
	
	for (int offset = 0; offset < busSched.size(); offset++) {
		int id = busSched[offset];
		if (id != NONE) {
			busIDs.push_back(id);
			offsets.push_back(offset);
			int lf = id - offset;
			while (lf <= 0) {
				lf += id; //avoid negative numbers
			}
			lookingFor.push_back(lf);
		}
	}
	
	lookingFor[0] = 0;
	cout << "busIDs: " << aoc::vtos(busIDs) << endl;
	cout << "offsets: " << aoc::vtos(offsets) << endl;
	cout << "lookingFor: " << aoc::vtos(lookingFor) << endl;
	
	/*
	After bus1 and bus2 sync up, the time to their next sync is (bus1*bus2). So, we only have to
	check those times. After bus3 syncs up, the time to the sync up is (bus1*bus2*bus3), etc.
	*/
	
	delay = 0;
	earliestDepartTime = 0; // Overwriting global
	
	vector<long long> timesSinceDepart(busIDs.begin(), busIDs.end());
	transform(timesSinceDepart.begin(), timesSinceDepart.end(),
			  timesSinceDepart.begin(), CalcTimeSinceDepart);
	cout << delay << ": " << aoc::vtos(timesSinceDepart) << endl;
	int maxSync = 0;
	long long jump = busIDs[maxSync]; // looking for bus0 and bus1 sync
	
	while (true) {
		// Tried using std::equal here, but wasn't working
		bool bEqual = true;
		for (int i = 0; i <= maxSync + 1; i++) {
			if (timesSinceDepart[i] != lookingFor[i]) {
				bEqual = false;
				break;
			}
		}
		if (bEqual) {
			// Found sync
			maxSync += 1;
			cout << delay << ": " << aoc::vtos(timesSinceDepart) << endl;
			cout << "Found sync. maxSync now " << maxSync << endl;
			if (maxSync == busIDs.size() - 1) {
				cout << "Found solution: " << delay << endl;
				return;
			}
			jump *= busIDs[maxSync];
			cout << "Changed jump to " << jump << endl;
		}
		
		delay += jump;
		timesSinceDepart = vector<long long>(busIDs.begin(), busIDs.end());
		transform(timesSinceDepart.begin(), timesSinceDepart.end(),
				  timesSinceDepart.begin(), CalcTimeSinceDepart);
	}
}