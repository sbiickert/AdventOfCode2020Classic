#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace aoc {
	std::vector<std::string> ReadInputFile(std::string name, bool removeEmpty);
	std::vector<std::vector<std::string> > ReadGroupedInputFile(std::string name);
	
	int stoi(std::string input);
	long long stol(std::string input);
	
	std::string replace_all(std::string s, std::string old_str, std::string new_str);
	std::vector<std::string> split(std::string);
	std::vector<std::string> split(std::string, std::string delim);
	
	bool is_whitespace(const std::string& s);

	
	template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
    
    template <typename T> std::string vtos(std::vector<T> const &v)
    {
    	std::string output = "[";
		
		std::vector<T>::const_iterator it;
		for (it = v.begin(); it != v.end(); it++) {
			output.append(to_string(*it));
			output.append(",");
		}
		output = output.substr(0, output.size() - 1); // Remove excess comma
		output.append("]");
		return output;
    }
	
	template <typename T> void remove_value(std::vector<T> &v, T value) {
		v.erase( remove(v.begin(), v.end(), value), v.end());
	} 
}