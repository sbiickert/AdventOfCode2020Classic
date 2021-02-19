#include "AoC.h"

namespace aoc {
	std::vector<std::string> ReadInputFile(std::string name, bool removeEmpty) {
		std::vector<std::string> results;
		
		std::ifstream file(name.c_str());
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				if (removeEmpty && is_whitespace(line)) {
					// ignore
				}
				else {
					results.push_back(line);
				}
			}	
		}
		return results;
	}
	
	std::vector<std::vector<std::string> > ReadGroupedInputFile(std::string name) {
		// 2-dimensional vector of strings, broken on empty lines
		std::vector<std::vector<std::string> > input;
		
		std::vector<std::string> lines = ReadInputFile(name, false);
		
		std::vector<std::string> group;
		std::vector<std::string>::iterator it;
		for (it = lines.begin(); it != lines.end(); it++) {
			if (is_whitespace(*it)) {
				input.push_back(group);
				group = std::vector<std::string>();
			}
			else {
				group.push_back(*it);
			}
		}
		if (group.size() > 0) {
			input.push_back(group);
		}
		return input;
	}
	
	int stoi(std::string input) {
		std::istringstream ss(input);
		int theValue;
		ss >> theValue;
		return theValue;
	}
	
	long long stol(std::string input) {
		std::istringstream ss(input);
		long long theValue;
		ss >> theValue;
		return theValue;
	}

	bool is_whitespace(const std::string& s) {
		for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
			if (!std::isspace(*it)) {
				return false;
			}
		}
		return true;
	}
}