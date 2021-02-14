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
	
	int stoi(std::string input) {
		std::istringstream ss(input);
		int theValue;
		ss >> theValue;
		return theValue;
	}
	
	long stol(std::string input) {
		std::istringstream ss(input);
		long theValue;
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