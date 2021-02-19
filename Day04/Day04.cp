/*
 *  Advent of Code 2020, Day 4
 *	Passport Processing
 */

#include <iostream>
#include <algorithm>
#include <math.h>

#include "Day04.h"
#include "AoC.h"

using namespace std;  //introduces namespace std

const string NODATA = "NO DATA";

int main()
{	
	vector<vector<string> > input = aoc::ReadGroupedInputFile("Day4_Input.txt");
	
	vector<PassportInfo> passports;
	for (int i = 0; i < input.size(); i++) {
		PassportInfo pi = ParseInfo(input[i]);
		passports.push_back(pi);
	}
	
	cout << "Read " << passports.size() << " passports." << endl;
	
	int validCount = count_if(passports.begin(), passports.end(), IsPassportInfoValidPt1);
	cout << "(Part 1) The number of valid passports: " << validCount << endl;

	validCount = count_if(passports.begin(), passports.end(), IsPassportInfoValidPt2);
	cout << "(Part 2) The number of valid passports: " << validCount << endl;

	return 0;
}

PassportInfo ParseInfo(vector<string> data) {	
	// Parse the read passport field information
	PassportInfo pi;
	
	pi.byr = -1;
	pi.iyr = -1;
	pi.eyr = -1;
	pi.hgt = -1;
	pi.pid = NODATA;
	pi.hcl = NODATA;
	pi.ecl = NODATA;
	pi.cid = -1;
	
	vector<string>::iterator line;
	for (line = data.begin(); line != data.end(); line++) {
		map<string,string> lineMap = ParseLine(*line);
		
		map<string,string>::iterator kv;
		for (kv = lineMap.begin(); kv != lineMap.end(); kv++) {
			string key = kv->first;
			if (key == "byr")
				pi.byr = aoc::stoi(kv->second);
			if (key == "iyr")
				pi.iyr = aoc::stoi(kv->second);
			if (key == "eyr")
					pi.eyr = aoc::stoi(kv->second);
			if (key == "pid")
					pi.pid = kv->second;
			if (key == "cid")
					pi.cid = aoc::stoi(kv->second);
			if (key == "hcl")
					pi.hcl = kv->second;
			if (key == "ecl")
					pi.ecl = kv->second;
			if (key == "hgt")
				pi.hgt = ParseHeight(kv->second);
		}
	}
	
	return pi;
}

map<string, string> ParseLine(string line) {
	// Turn line with multiple key:values into map
	// hgt:163cm hcl:#866857 pid:628113926
	map<string, string> result;
	
	// Split on spaces
	istringstream iss(line);
	vector<string> parsed((istream_iterator<string>(iss)), istream_iterator<string>());
	
	// For each pair on the line
	vector<string>::iterator it;
	for (it = parsed.begin(); it != parsed.end(); it++) {
		// key is the first three characters
		string key = it->substr(0, 3);
		string value = it->substr(4, string::npos);
		result.insert( map<string,string>::value_type(key, value) );
	}
	
	return result;
}

int ParseHeight(string value) {
	int pos = value.find("in");
	if (pos != string::npos) {
		int inches = aoc::stoi(value.substr(0, pos));
		return round(inches * 2.54);
	}
	else {
		pos = value.find("cm");
		if (pos != string::npos) {
			return aoc::stoi(value.substr(0, pos));
		}
	}
	return 0;
}

bool IsPassportInfoValidPt1(PassportInfo pi) {
	// Valid if all fields are populated
	// cid is optional
	
	return pi.byr != -1 && pi.iyr != -1
		&& pi.eyr != -1 && pi.pid != NODATA
		&& pi.hcl != NODATA && pi.ecl != NODATA
		&& pi.hgt != -1;
}

bool IsPassportInfoValidPt2(PassportInfo pi) {
	// Any passport invalid in part 1 will be invalid in part 2
	if (IsPassportInfoValidPt1(pi) == false) {
		return false;
	}
	if (pi.byr < 1920 || pi.byr > 2002) {
		// cout << "Invalid byr: " << pi.byr << endl;
		return false;
	}
	if (pi.iyr < 2010 || pi.iyr > 2020) {
		// cout << "Invalid iyr: " << pi.iyr << endl;
		return false;
	}
	if (pi.eyr < 2020 || pi.eyr > 2030) {
		// cout << "Invalid eyr: " << pi.eyr << endl;
		return false;
	}
	if (pi.hgt < 150 || pi.hgt > 193) {
		// cout << "Invalid height: " << pi.hgt << endl;
		return false;
	}
	if (pi.pid.size() != 9) {
		// cout << "Invalid pid: " << pi.pid << endl;
		return false;
	}
	if (IsEyeColorValid(pi.ecl) == false) {
		// cout << "Invalid eye color: " << pi.ecl << endl;
		return false;
	}
	if (IsHairColorValid(pi.hcl) == false) {
		// cout << "Invalid hair color: " << pi.hcl << endl;
		return false;
	}
	return true;
}

bool IsEyeColorValid(string ecl) {
	if (ecl == "amb" || ecl == "blu" || ecl == "brn"
		|| ecl == "gry" || ecl == "grn" || ecl == "hzl"
		|| ecl == "oth") {
		return true;
	}
	return false;
}

bool IsHairColorValid(string hcl) {
	// a # followed by six characters 0-9 or a-f
	if (hcl.size() != 7 || hcl[0] != '#') {
		return false;
	}
	
	for (int i = 1; i < 7; i++) {
		if (hcl[i] >= '0' && hcl[i] <= '9' || hcl[i] >= 'a' && hcl[i] <= 'f') {
			// ok
		}
		else {
			return false;
		}
	}
	return true;
}