#include "AoC.h"
#include <sstream>

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

	std::string replace_all(std::string s, std::string old_str, std::string new_str) {
		std::size_t pos = s.find(old_str);
		while (pos != std::string::npos) {
			s.replace(pos, new_str.size(), new_str);
			pos = s.find(old_str, pos+1);
		}
		return s;
	}
	
	std::vector<std::string> split(std::string s) {
		return split(s, " ");
	}
	
	const char* UNLIKELY_DELIMITERS = "_~%$#";
	
	std::vector<std::string> split(std::string s, std::string delim) {
		std::string space_substitute = " ";
		if (delim != " ") {
			// We want to get s to be ' ' delimited
			// Replace all spaces in s with an UNLIKELY_DELIMITER
			space_substitute = "_";
			s = replace_all(s, " ", space_substitute);
			
			// Now turn all of the delimiter chars into spaces
			s = replace_all(s, delim, " ");
		}
		
		std::istringstream iss(s);
		std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)),
										 std::istream_iterator<std::string>());
		std::vector<std::string>::iterator it;
		
		if (delim != " ") {
			for (it = parsed.begin(); it != parsed.end(); it++) {
				*it = replace_all(*it, space_substitute, " ");
			}
		}
		
		return parsed;
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