/*
	Advent of Code 2020, Day 2
	Password Philosophy
*/

#include <iostream>
#include <algorithm>

#include "Day02.h"
#include "AoC.h"

using namespace std;  //introduces namespace std

bool IsPasswordValid1(PasswordInfo p) {
	int letter_count = count(p.password.begin(), p.password.end(), p.letter);
	bool enough = p.min <= letter_count;
	bool too_many = letter_count > p.max;
	return enough && !too_many;
}

bool IsPasswordValid2(PasswordInfo p) {
	// Offsetting by -1 because min and max are 1-based, not 0-based
	bool minPosIsLetter = p.password[p.min-1] == p.letter;
	bool maxPosIsLetter = p.password[p.max-1] == p.letter;
	return minPosIsLetter != maxPosIsLetter;
}

int main()
{	
	vector<PasswordInfo> pi = ReadPasswordInfo();
	
	int valid_count;
	
	valid_count = count_if(pi.begin(), pi.end(), IsPasswordValid1);
	cout << valid_count << " passwords are valid for part 1." << endl;
	
	valid_count = count_if(pi.begin(), pi.end(), IsPasswordValid2);
	cout << valid_count << " passwords are valid for part 2." << endl;
	
	return 0;
}

PasswordInfo ParsePasswordInfo(string line);

vector<PasswordInfo> ReadPasswordInfo() {
	
	vector<string> input;
	input = aoc::ReadInputFile("Day2_Input.txt", true);
	
	vector<PasswordInfo> results;
	
	vector<string>::iterator it;
	for (it = input.begin(); it != input.end(); it++) {
		results.push_back(ParsePasswordInfo(*it));
	}	
	
	return results;
}

PasswordInfo ParsePasswordInfo(string line) {
	// Example:
	//4-6 r: rrrkrgr
	//min-max letter: password
	PasswordInfo result;
	
	line.replace(line.find("-"), 1, " ");
	line.replace(line.find(":"), 0, "");
	
	// Now we have:
	//4 6 r rrrkrgr
	
	// Split on spaces
	istringstream iss(line);
	vector<string> parsed((istream_iterator<string>(iss)), istream_iterator<string>());
	
	result.min = aoc::stoi(parsed[0]);
	result.max = aoc::stoi(parsed[1]);
	result.letter = parsed[2][0];
	result.password = parsed[3];
	
	return result;
}