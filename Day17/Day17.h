/*
 *  Advent of Code 2020, Day 17
 *  Conway Cubes
 */

#include <vector>
#include <string>
#include <map>

using namespace std;  //introduces namespace std

class ConwayPocket {
private:
	map< vector<int>, bool > mState;
	int mDimensionCount;
	
public:
	ConwayPocket();
	ConwayPocket(int n_dimensions);
	~ConwayPocket();
	int GetDimensionCount() { return mDimensionCount; };
	bool IsActive(vector<int> key);
	int Iterate();
	void LoadData(vector<string>);
	int CountActive();
};

vector< vector<int> > GetNeighbourKeys(vector<int> const&);	
vector<int> NumToTernary(int num, int pad=0);
