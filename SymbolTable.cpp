#include "SymbolTable.h"
#include <map>
#include <string>



SymbolTable::SymbolTable()
{
	address = 16;

	table["SP"] = 0;
	table["LCL"] = 1;
	table["ARG"] = 2;
	table["THIS"] = 3;
	table["THAT"] = 4;
	table["SCREEN"] = 16384;
	table["KBD"] = 24576;

	for (int i = 0; i < 16; i++)
	{
		table["R" + std::to_string(i)] = i;
	}
}


SymbolTable::~SymbolTable()
{
}

void SymbolTable::addSymbol(std::string symbol)
{
	if (!contains(symbol)) {
		table[symbol] = address;
		address++;
	}
}

void SymbolTable::addSymbol(std::string symbol, int s_address)
{
	if (!contains(symbol)) {
		table[symbol] = s_address;
	}
}

bool SymbolTable::contains(std::string symbol)
{
	return table.find(symbol) != table.end();
}

int SymbolTable::getAddress(std::string symbol)
{
	return table[symbol];
}