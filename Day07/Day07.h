/*
 *  Advent of Code 2020, Day 7
 *	Handy Haversacks
 */
#include <string>
#include <map>
#include <set>

struct BagRule {
	std::string source;
	std::string color;
	std::map<std::string,int> containedQuantities;
	
	int TotalBags();
	bool Contains(std::string color);
	void DebugOut();
};


BagRule ParseRule(std::string source);

void FindColorsContaining(std::string color, std::set<std::string>& found);
BagRule RuleForColor(std::string color);
int CountContainedBags(std::string color);