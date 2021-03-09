/*
 *  Advent of Code 2020, Day 16
 *  Ticket Translation
 */

#include <iostream>
#include <string>
#include <algorithm>

#include "AoC.h"
#include "Day16.h"

using namespace std;  //introduces namespace std

vector<FieldRule> rules;

int main()
{	
	vector<vector<string> > input = aoc::ReadGroupedInputFile("Day16_Input.txt");
	vector<string>::const_iterator it;
	
	for (it = input[0].begin(); it != input[0].end(); it++) {
		rules.push_back(FieldRule(*it));
	}
	
	Ticket myTicket = Ticket(input[1][1]); // [1][0] is label "your ticket:"
	
	vector<Ticket> otherTickets;
	input[2].erase(input[2].begin());  // First element is label "nearby tickets"
	for (it = input[2].begin(); it != input[2].end(); it++) {
		otherTickets.push_back(Ticket(*it));
	}
	
	int errorRate = CalcErrorRate(otherTickets);
	
	cout << "Part 1 error rate: " << errorRate << endl << endl;
	
	vector<Ticket> validTickets = FilterValid(otherTickets);
	
	cout << validTickets.size() << " valid tickets out of " << otherTickets.size() << endl;
	
	vector<string> certainFields = ProcessOfElimination(validTickets);
	cout << "The fields, in order: " << endl << aoc::vtos(certainFields) << endl;

	vector<int> departureValues;
	for (int i = 0; i < certainFields.size(); i++) {
		string fName = certainFields[i];
		if (fName.substr(0, 9) == "departure") {
			departureValues.push_back(myTicket.values[i]);
		}
	}
	
	long long product = 1;
	for (int i = 0; i < departureValues.size(); i++) {
		product *= departureValues[i];
	}
	
	cout << "Multiply " << aoc::vtos(departureValues) << " together: " << product << endl;
	
	return 0;
}

int CalcErrorRate(vector<Ticket> const &tickets)
{
	int errorRate = 0;
	
	vector<Ticket>::const_iterator it;
	for (it = tickets.begin(); it != tickets.end(); it++)
	{
		Ticket t = *it;
		vector<int> invalidValues = t.InvalidValues(rules);
		vector<int>::iterator vit;
		for (vit = invalidValues.begin(); vit != invalidValues.end(); vit++) {
			errorRate += *vit;
		}
	}
	
	return errorRate;
}

// Would be better to use copy_if and a lambda in modern C++
vector<Ticket> FilterValid(std::vector<Ticket> const &tickets) 
{
	vector<Ticket> validTickets;
	vector<Ticket>::const_iterator it;
	for (it = tickets.begin(); it != tickets.end(); it++)
	{
		Ticket t = *it;
		if (t.IsValidForRules(rules)) {
			validTickets.push_back(t);
		}
	}
	return validTickets;
}

vector<string> ProcessOfElimination(vector<Ticket> const &tickets)
{
	vector<FieldRule>::iterator frit;
	
	// At the start, any field could be possible
	vector<string> fieldNames;
	for (frit = rules.begin(); frit != rules.end(); frit++) {
		FieldRule fr = *frit;
		fieldNames.push_back(fr.field);
	}
	vector<vector<string> > possibleFields;
	for (int i = 0; i < tickets[0].values.size(); i++) {
		possibleFields.push_back(fieldNames);
	}
	
	// Eliminate all of the possibilities where field values violate rules
	for (int i = 0; i < tickets.size(); i++) {
		Ticket t = tickets[i];
		for (int j = 0; j < t.values.size(); j++) {
			int value = t.values[j];
			for (frit = rules.begin(); frit != rules.end(); frit++) {
				FieldRule fr = *frit;
				if (fr.IsValueInRanges(value) == false) {
					aoc::remove_value(possibleFields[j], fr.field);
				}
			}
		}
	}
	
	// Find any field where there is only one option. Mark as certain, eliminate from possibles.
	vector<string> certainFields(tickets[0].values.size(), "");
	
	while (true) {
		for (int i = 0; i < possibleFields.size(); i++) {
			if (possibleFields[i].size() == 1) {
				string certainField = possibleFields[i][0];
				certainFields[i] = certainField;
				for (int j = 0; j < possibleFields.size(); j++) {
					aoc::remove_value(possibleFields[j], certainField);
				}
				break; // eliminated a field. loop again.
			}
		}
		
		bool noWorkToDo = true;
		for (int i = 0; i < possibleFields.size(); i++) {
			if (possibleFields[i].size() > 0) {
				noWorkToDo = false;
				break;
			}
		}
		
		if (noWorkToDo)
			break;
	}	
	
	return certainFields;
}


FieldRule::FieldRule() 
{
	field = "";
	r1Min = 0;
	r1Max = 0;
	r2Min = 0;
	r2Max = 0;
}

FieldRule::FieldRule(string defn) 
{
	// Example:
	//arrival station: 39-703 or 724-950
	string spaced = aoc::replace_all(defn, "-", " ");
	//arrival station: 39 703 or 724 950
	vector<string> firstSplit = aoc::split(spaced, ":");
	// ["arrival station", "39 703 or 724 950"]
	vector<string> secondSplit = aoc::split(firstSplit[1]);
	field = firstSplit[0];
	r1Min = aoc::stoi(secondSplit[0]);
	r1Max = aoc::stoi(secondSplit[1]);
	r2Min = aoc::stoi(secondSplit[3]);
	r2Max = aoc::stoi(secondSplit[4]);
}

bool FieldRule::IsValueInRanges(int value)
{
	return (value >= r1Min && value <= r1Max) || (value >= r2Min && value <= r2Max);
}

Ticket::Ticket() {}

Ticket::Ticket(string defn)
{
	vector<string> strs = aoc::split(defn, ",");
	vector<string>::const_iterator it;
	
	for (it = strs.begin(); it != strs.end(); it++) {
		values.push_back(aoc::stoi(*it));
	}
}

bool Ticket::IsValidForRules(vector<FieldRule> const &rules)
{
	return InvalidValues(rules).size() == 0;
}

vector<int> Ticket::InvalidValues(vector<FieldRule> const &rules)
{
	vector<int> invalidValues;
	vector<int>::const_iterator vit;
	for (vit = values.begin(); vit != values.end(); vit++)
	{
		int value = *vit;
		bool isValidForAnyRule = false;
		vector<FieldRule>::const_iterator frit;
		for (frit = rules.begin(); frit != rules.end(); frit++)
		{
			FieldRule fr = *frit;
			if (fr.IsValueInRanges(value)) {
				isValidForAnyRule = true;
				break;
			}
		}
		if (isValidForAnyRule == false) {
			invalidValues.push_back(value);
		}
	}
	return invalidValues;
}
