/*
 *  Advent of Code 2020, Day 14
 *  Docking Data
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include <cmath>

#include "AoC.h"
#include "Day14.h"

using namespace std;  //introduces namespace std

int main()
{	
	vector<string> input = aoc::ReadInputFile("Day14_Input.txt", true);
	vector<string>::const_iterator it;
		
	Mask mask;
	
	// Testing
	//int value = 11;
	//mask = Mask("mask = X1XXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X");
	//long long masked = mask.ApplyTo(value); // expect 73
	//cout << value << " -> " << masked;
	//return 1;
	
	cout << "Part 1" << endl;
	map<int, long long> memory;
	
	for (it = input.begin(); it != input.end(); it++) {
		if (IsMask(*it)) {
			mask = Mask(*it);
		}
		else if (IsMemWrite(*it)) {
			MemWrite mw = MemWrite(*it);
			mw.value = mask.ApplyTo(mw.value);
			memory[mw.address] = mw.value;
		}
	}
	
	// Now get the sum of the memory values
	long long sum = 0;
	map<int,long long>::const_iterator summer;
	for (summer = memory.begin(); summer != memory.end(); summer++) {
		sum += summer->second;
	}
	
	cout << "The sum of memory values is " << sum << endl << endl;

	// Testing
	//int address = 42;
	//mask = Mask("mask = 000000000000000000000000000000X1001X");
	//vector<long long> addresses = mask.FloatingAddresses(address); // expect 26, 27, 58, 59
	//cout << address << " -> " << aoc::vtos(addresses) << endl;
	//return 1;
	
	cout << "Part 2" << endl;
	map<long long, long long> bigMemory;
	
	for (it = input.begin(); it != input.end(); it++) {
		if (IsMask(*it)) {
			mask = Mask(*it);
		}
		else if (IsMemWrite(*it)) {
			MemWrite mw = MemWrite(*it);
			vector<long long> addresses = mask.FloatingAddresses(mw.address);
			vector<long long>::const_iterator add_it;

			for (add_it = addresses.begin(); add_it != addresses.end(); add_it++) {
				long long targetAddress = *add_it;
				bigMemory[targetAddress] = mw.value;
			}
		}
	}
	
	// Now get the sum of the memory values
	long long bigSum = 0;
	map<long long,long long>::const_iterator big_summer;
	for (big_summer = bigMemory.begin(); big_summer != bigMemory.end(); big_summer++) {
		bigSum += big_summer->second;
	}
	
	cout << "The sum of memory values is " << bigSum << endl;
	
	return 0;
}


bool IsMask(string input) {
	// Example:
	// mask = 1X0X00101111100010100X001010XX0X0XXX
	return (input.substr(0, 4) == "mask");
}

bool IsMemWrite(string input) {
	// Example:
	// mem[45876] = 33941457
	return (input.substr(0, 3) == "mem");
}


#pragma mark MemWrite Implementation

MemWrite::MemWrite(string input) {
	// Break on spaces
	vector<string> parts = aoc::split(input);
	
	// [0] First 4 chars are 'mem[', then remove last char
	string addressStr = parts[0].substr(4);
	addressStr = addressStr.substr(0, addressStr.size() - 1);
	address = aoc::stoi(addressStr);
	
	// [1] =
	
	// [2] integer value
	value = aoc::stol(parts[2]);
}

#pragma mark Mask Implementation

Mask::Mask() {
	value = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
}

Mask::Mask(string input) {
	// 36 character string with 7 character prefix
	value = input.substr(7);
}

long long Mask::ApplyTo(int input) {
	// Turn input into bitset
	bitset<36> inputBits(input);
	
	//cout << "in:   " << inputBits.to_string() << endl;
	//cout << "mask: " << value << endl;
	
	// The endian-ness of the mask is opposite expected. Reverse for masking.
	string reversed = value;
	reverse(reversed.begin(), reversed.end());

	for (int i = 0; i < 36; i++) {
		switch (reversed[i]) {
			case '1':
				inputBits[i] = 1;
				break;
			case '0':
				inputBits[i] = 0;
				break;
			case 'X':
				break;
		}
	}
	
	//cout << "out:  " << inputBits.to_string() << endl;
	
	return BitSetToULLong(inputBits);
}

vector<long long> Mask::FloatingAddresses(int input) {
	vector<long long> result;
	
	// The endian-ness of the mask is opposite expected. Reverse for masking.
	string reversed = value;
	reverse(reversed.begin(), reversed.end());
	
	// Turn input into bitset
	bitset<36> inputBits(input);

	// cout << "in:   " << inputBits.to_string() << endl;
	// cout << "mask: " << value << endl;
	
	// Set the overwritten '1's first, note the floating indexes
	vector<int> floatingIndexes;
	for (int i = 0; i < 36; i++) {
		switch (reversed[i]) {
			case '1':
				inputBits[i] = 1;
				break;
			case 'X':
				floatingIndexes.push_back(i);
				break;
		}
	}
	
	int nOptions = pow(2, floatingIndexes.size());
	for (int i = 0; i < nOptions; i++) {
		bitset<36> option = inputBits;
		vector<bool> o = IntToBinary(i, floatingIndexes.size());
		for (int j = 0; j < o.size(); j++) {
			option[floatingIndexes[j]] = o[j] ? 1 : 0;
		}
		result.push_back(BitSetToULLong(option));
		// cout << "out:  " << option.to_string() << endl;
	}
	
	return result;
}

unsigned long long BitSetToULLong(std::bitset<36> bs) {
	/*
	 * MSL does not have to_ullong() on the bitset class :-(
	 * return bs.to_ullong();
	 */
	unsigned long long result = 0;
	for (int i = 0; i < 36; i++) {
		if (bs[i] == 1) {
			result += pow(2, i);	
		}
	}
	return result;
}

vector<bool> IntToBinary(long long i, int padBits) {
	vector<bool> result;
	
	bitset<64> bits(i);
	// Make the vector as small as needed or as per padBits.
	// Only start pushing bools on once we have found the first 1.
	bool pushing = false;
	
	for (int i = 63; i >= 0; i--) {
		if (bits[i] == 1 || i < padBits)
			pushing = true;
		if (pushing)
			result.push_back(bits[i] == 1);
	}
	
	reverse(result.begin(), result.end());
	
	return result;
}