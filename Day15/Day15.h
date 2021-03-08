/*
 *  Advent of Code 2020, Day 15
 *  Rambunctious Recitation
 */

#include <vector>
#include <string>

int PlayMemoryGame(std::vector<std::string> const &input, int iterations);

class NumberHistory {
private:
	int number;
	int mostRecentTurn;
	int previousTurn;

public:
	NumberHistory();
	NumberHistory(int num, int turn);
	~NumberHistory();
	int GetNumber();
	int GetMostRecentTurn();
	void SetMostRecentTurn(int);
	bool HasBeenSpokenBefore();
	int GetAge();
};