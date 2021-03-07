/*
 *  Advent of Code 2020, Day 14
 *  Docking Data
 */

#include <string>
#include <bitset>

struct MemWrite {
	int address;
	long long value;
	
	MemWrite(std::string);
};

struct Mask {
	std::string value;
	long long ApplyTo(int);
	std::vector<long long> FloatingAddresses(int);
	
	Mask();
	Mask(std::string);
};

bool IsMask(std::string);
bool IsMemWrite(std::string);

unsigned long long BitSetToULLong(std::bitset<36>);

std::vector<bool> IntToBinary(long long, int padBits);