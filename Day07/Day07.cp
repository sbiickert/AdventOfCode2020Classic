/*
 *  Advent of Code 2020, Day 7
 *	Handy Haversacks
 */

#include <iostream>
#include <vector>
#include <string>

#include "AoC.h"
#include "Day07.h"

using namespace std;  //introduces namespace std

const char* DIGITS = "01223456789";
const string GOLD = "shiny gold";

vector<BagRule> rules;

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day7_Input.txt", true);
	
	vector<string>::iterator it;
	for (it = input.begin(); it != input.end(); it++) {
		BagRule rule = ParseRule(*it);
		// rule.DebugOut();
		rules.push_back(rule);
	}
	
	set<string>containingColors;
	FindColorsContaining(GOLD, containingColors);
	
	cout << "Number of colors containing shiny gold is: " << containingColors.size() << endl;
	
	int containedBagCount = CountContainedBags(GOLD) - 1; // Counts self, subtract 1 to compensate.
	
	cout << "Number of bags contained by shiny gold is: " << containedBagCount << endl;

	return 0;
}

int BagRule::TotalBags() {
	int total = 0;
	
	map<string, int>::iterator it;
	for (it = containedQuantities.begin(); it != containedQuantities.end(); it++) {
		total += it->second;
	}
	
	return total;
}

bool BagRule::Contains(string color) {
	return containedQuantities.count(color) == 1;
}

void BagRule::DebugOut() {
	cout << source << endl;
	cout << "Bag color: " << color << endl;
	map<string, int>::iterator it;
	for (it = containedQuantities.begin(); it != containedQuantities.end(); it++) {
		cout << "Contains " << it->second << " " << it->first << " bags." << endl;
	}
	cout << "for a total contained bag count of: " << TotalBags() << endl;
	cout << "Does it contain red? " << Contains("red") << endl;
	cout << "Does it contain striped aqua? " << Contains("striped aqua") << endl;
}

void FindColorsContaining(string color, set<string>& found) {
	vector<BagRule>::iterator rit;
	for (rit = rules.begin(); rit != rules.end(); rit++) {
		BagRule r = *rit;
		if (r.Contains(color) && found.count(r.color) == 0) {
			found.insert(r.color);
			FindColorsContaining(r.color, found);
		}
	}
}

BagRule RuleForColor(string color) {
	BagRule rule;
	
	vector<BagRule>::iterator it;
	for (it = rules.begin(); it != rules.end(); it++) {
		BagRule r = *it;
		if (r.color == color) {
			rule = r;
			break;
		}
	}
	return rule;
}

int CountContainedBags(std::string color) {
	BagRule rule = RuleForColor(color);
	
	int count = 1;
	map<string, int>::iterator it;
	for (it = rule.containedQuantities.begin(); it != rule.containedQuantities.end(); it++) {
		int numBags = it->second;
		count += (CountContainedBags(it->first) * numBags);
	}
	return count;
}

BagRule ParseRule(string source) {
	// {color} bags contain no other bags.
	// {color} bags contain {N} {color} bag(s).
	// {color} bags contain {N} {color} bag(s), {N} {color} bag(s)..., {N} {color} bag(s).
	BagRule r;
	
	r.source = source;
	
	// Find the color of this bag
	int index;
	index = source.find(" bags contain ", 0);
	r.color = source.substr(0, index);
	
	// Does the remaining content define any contained bags?
	index = source.find("no other bags", index);
	if (index < 0) {
		// There will be 1 or more contained bag
		index = source.find_first_of(DIGITS, 0);
		while (index > 0) {
			int quantity = aoc::stoi(source.substr(index, 1));
			int bagIndex = source.find(" bag", index);
			int startIndex = index + 2;
			int length = bagIndex - startIndex;
			string containedColor = source.substr(startIndex, length);
			r.containedQuantities.insert(map<string,int>::value_type(containedColor, quantity));
			index = source.find_first_of(DIGITS, bagIndex);
		}
	}
	
	return r;
}
