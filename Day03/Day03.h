/*
 *  Advent of Code 2020, Day 3
 *	Toboggan Trajectory
 */

#include <vector>
#include <string>

int SolveDay03();

class TobogganHill {
private:
	std::vector<std::string> mHill;

public:
	static const char SNOW = '.';
	static const char TREE = '#';
	
	TobogganHill();
	TobogganHill(std::vector<std::string> data);
	~TobogganHill();
	
	int GetHillHeight();
	char GetTerrain(int fall, int run);
	std::string GetTraverse(int fall, int run);
	static bool IsTree(char terrain);
};
