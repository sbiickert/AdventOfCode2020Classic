/*
 *  Advent of Code 2020, Day 8
 *	Handheld Halting
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "AoC.h"
#include "Day08.h"

using namespace std;  //introduces namespace std

const char ACC = 'a';
const char JMP = 'j';
const char NOP = 'n';

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day8_Input.txt", true);
	vector<string>::iterator it;
	
	vector<Instruction> instructions;
	for (it = input.begin(); it != input.end(); it++) {
		Instruction i = ParseInstruction(*it);
		instructions.push_back(i);
	}

	int accumulated = 0;
	vector<int> codePath = Run(instructions, accumulated);
	
	cout << "Accumulated " << accumulated << " when infinite loop found." << endl;
	
	vector<int> results = codePath;
	
	for (int index = codePath.size() - 2; index >= 0; index--) {
		if (results[results.size()-1] >= instructions.size()) {
			cout << "Broke out by modifying instruction " << index + 1 << endl;
			cout << "Accumulated: " << accumulated << endl;
			break;
		}
		vector<Instruction> modified(instructions); // Copy original
		int ptr = codePath[index];
		
		switch (modified[ptr].IType()) {
			case JMP:
				modified[ptr].instr = "nop";
				break;
			case NOP:
				modified[ptr].instr = "jmp";
				break;
		}
		
		accumulated = 0;
		results = Run(modified, accumulated);
	}
	
	return 0;
}

char Instruction::IType() {
	return instr[0];
}

vector<int> Run(std::vector<Instruction> instructions, int &acc) {
	vector<int> codePath;
	set<int> executed;
	int ptr = 0;
	
	while (executed.count(ptr) == 0) {
		Instruction i = instructions[ptr];
		executed.insert(ptr);
		codePath.push_back(ptr);
		switch (i.IType()) {
			case ACC:
				acc += i.value;
				ptr++;
				break;
			case JMP:
				ptr += i.value;
				break;
			case NOP:
				ptr++;
				break;
		}
		if (ptr < 0 || ptr >= instructions.size()) {
			cout << "ptr outside instruction bounds: " << ptr << endl;
			codePath.push_back(ptr);
			break;
		}
	}
	return codePath;
}

Instruction ParseInstruction(std::string source) {
	Instruction i;
	
	i.instr = source.substr(0, 3);
	
	string value = source.substr(5);
	char sign = source[4];
	if (sign == '+') {
		i.value = aoc::stoi(value);
	}
	else {
		i.value = aoc::stoi(value) * -1;
	}
	
	return i;
}