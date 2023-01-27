#pragma once
#include <map>

class SymbolTable
{
public:
	SymbolTable();
	~SymbolTable();

	void addSymbol(std::string symbol);
	void addSymbol(std::string symbol, int s_address);

	bool contains(std::string symbol);
	int getAddress(std::string symbol);

private:
	std::map<std::string, int> table;
	int address;
};

