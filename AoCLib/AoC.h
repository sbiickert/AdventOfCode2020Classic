#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace aoc {
	std::vector<std::string> ReadInputFile(std::string name, bool removeEmpty);
	std::vector<std::vector<std::string> > ReadGroupedInputFile(std::string name);
	
	int stoi(std::string input);
	long long stol(std::string input);
	
	bool is_whitespace(const std::string& s);

	
	template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}