/*
 *  Advent of Code 2020, Day 8
 *	Handheld Halting
 */
#include <string>
#include <vector>

struct Instruction {
	std::string instr;
	int value;
	
	char IType();
};

Instruction ParseInstruction(std::string source);

std::vector<int> Run(std::vector<Instruction> instructions, int &acc);
