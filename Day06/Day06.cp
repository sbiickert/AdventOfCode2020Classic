/*
 *  Advent of Code 2020, Day 6
 *	Custom Customs
 */

#include <iostream>
#include <set>
#include <numeric>

#include "AoC.h"
#include "Day06.h"

using namespace std;  //introduces namespace std

int main()
{	
	vector<vector<string> > input = aoc::ReadGroupedInputFile("Day6_Input.txt");
	
	vector<int> countsPerGroup1;
	vector<vector<string> >::iterator it;
	
	for (it = input.begin(); it != input.end(); it++) {
		set<char> summary = SummarizeGroup1(*it);
		countsPerGroup1.push_back(summary.size());
	}
	
	int total1 = accumulate(countsPerGroup1.begin(), countsPerGroup1.end(), 0);
	
	cout << "The total number of yes answers for part 1: " << total1 << endl;
	
	vector<int> countsPerGroup2;

	for (it = input.begin(); it != input.end(); it++) {
		set<char> summary = SummarizeGroup2(*it);
		countsPerGroup2.push_back(summary.size());
	}
	
	int total2 = accumulate(countsPerGroup2.begin(), countsPerGroup2.end(), 0);
	
	cout << "The total number of yes answers for part 2: " << total2 << endl;
	
	return 0;
}

set<char> SummarizeGroup1(vector<string> answers) {
	set<char> summary;
	
	vector<string>::iterator vit;
	vector<char>::iterator cit;
	
	// Get all the unique letters from all answers in group
	for (vit = answers.begin(); vit != answers.end(); vit++) {
		string answer = *vit;
		for (cit = answer.begin(); cit != answer.end(); cit++) {
			summary.insert(*cit);
		}
	}
	
	return summary;
}


set<char> SummarizeGroup2(vector<string> answers) {
	// Get all the unique "yes" answers from part 1
	set<char> summary1 = SummarizeGroup1(answers);
	set<char> summary2;
	
	set<char>::iterator s1it;
	vector<string>::iterator vit;
	
	// Loop through all the responses in summary 1.
	// Everybody has to answer yes. So check that the letter is in each answer.
	// If we don't find char in any answer, we don't add it to the summary2
	for (s1it = summary1.begin(); s1it != summary1.end(); s1it++) {
		char charToFind = *s1it;
		bool skip = false;
		for (vit = answers.begin(); vit != answers.end(); vit++) {
			string answer = *vit;
			if (answer.find(charToFind) == string::npos) {
				// Not found
				skip = true;
				break;
			}
		}
		if (skip == false) {
			summary2.insert(charToFind);
		}
	}
	
	return summary2;
}