/*
 *  Advent of Code 2020, Day 16
 *  Ticket Translation
 */

#include <vector>
#include <string>

struct FieldRule {
	std::string field;
	int r1Min;
	int r1Max;
	int r2Min;
	int r2Max;
	
	FieldRule();
	FieldRule(std::string defn);
	bool IsValueInRanges(int);
};

struct Ticket {
	std::vector<int> values;
	
	Ticket();
	Ticket(std::string defn);
	bool IsValidForRules(std::vector<FieldRule> const&);
	std::vector<int> InvalidValues(std::vector<FieldRule> const&);
};

int CalcErrorRate(std::vector<Ticket> const&);
std::vector<Ticket> FilterValid(std::vector<Ticket> const&);

std::vector<std::string> ProcessOfElimination(std::vector<Ticket> const &);