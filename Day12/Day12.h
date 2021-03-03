/*
 *  Advent of Code 2020, Day 12
 *  Rain Risk
 */

#include <vector>
#include <string>

struct Instruction {
	char action;
	int  val;
};

Instruction ParseInstruction(std::string const&);
std::vector<Instruction> ParseInstructions(std::vector<std::string> const&);

int ManhattanDistance(int, int);

class WayPoint {
private:
	int x;
	int y;
	void RotateRight();
	void RotateLeft();
	void Move(char dir, int val);
public:
	WayPoint();
	~WayPoint();
	void Apply(Instruction);
	int GetX();
	int GetY();
};

class Boat {
private:
	int x;
	int y;
	char dir;
	WayPoint w;
	void TurnRight();
	void TurnLeft();
	void Move(char dir, int val);
	void MoveBy(int dx, int dy);
public:
	Boat();
	~Boat();
	void Apply(Instruction);
	void ApplyWithWaypoint(Instruction);
	int GetX();
	int GetY();
	char GetDir();
	void Reset();
};
