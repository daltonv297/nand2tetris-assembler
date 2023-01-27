#pragma once
#include <string>
class Code
{
public:
	Code();
	~Code();

	std::string dest(std::string m);
	std::string comp(std::string m);
	std::string jump(std::string m);
	std::string aCommand(std::string m);

	std::string toMachineLang(std::string m, int commandType);
};

