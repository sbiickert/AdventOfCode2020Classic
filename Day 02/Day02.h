#include <vector>
#include <string>

struct PasswordInfo {
	int min;
	int max;
	char letter;
	std::string password;
};

bool IsPasswordValid1(PasswordInfo p);
bool IsPasswordValid2(PasswordInfo p);

std::vector<PasswordInfo> ReadPasswordInfo();
