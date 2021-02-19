/*
 *  Advent of Code 2020, Day 4
 *	Passport Processing
 */

#include <vector>
#include <map>
#include <string>

using namespace std;

struct PassportInfo {
	int byr;
	int iyr;
	int eyr;
	int hgt;
	string hcl;
	string ecl;
	string pid;
	int cid;
};

PassportInfo ParseInfo(vector<string> data);
map<string, string> ParseLine(string line);
int ParseHeight(string value);

bool IsPassportInfoValidPt1(PassportInfo pi);
bool IsPassportInfoValidPt2(PassportInfo pi);

bool IsEyeColorValid(string ecl);
bool IsHairColorValid(string hcl);