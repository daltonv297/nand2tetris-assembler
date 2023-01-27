#include <iostream>
#include <fstream>
#include <string>

#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

void assemble(char* argv[]);

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cout << "Error: not the right number of arguments\n";
	}
	else {

		assemble(argv);
	}
}

void assemble(char* argv[])
{
	Parser parser(argv);
	Code code;
	SymbolTable table;

	std::ofstream outputFile = std::ofstream(argv[2]);		//opens output file

	if (!outputFile.is_open())
	{
		std::cout << "Error: could not open output file.\n";
		return;
	}

	std::cout << "Building symbol table...\n";

	while (parser.hasMoreCommands())		//first pass, add labels to symbol table
	{
		parser.advance();
		if (parser.commandType() == 2) {		// is a label
			table.addSymbol(parser.symbol(), parser.getLineNumber() + 1);
		}
	}

	parser.reset();			//second pass, adds variables to symbol table

	while (parser.hasMoreCommands())
	{
		parser.advance();
		if (parser.symbol().length() != 0) {
			table.addSymbol(parser.symbol());
		}
	}

	parser.reset();

	std::cout << "Assembling code...\n";

	while (parser.hasMoreCommands())		//third pass, assembles code with sybols
	{

		parser.advance();

		if (parser.commandType() == 0) {		// is an a command
			if (parser.symbol().length() != 0) {		//a command contains a symbol
				outputFile << code.aCommand("@" + std::to_string(table.getAddress(parser.symbol())));
			}
			else {
				outputFile << code.aCommand(parser.getCurrentCommand());
			}

			if (parser.hasMoreCommands()) {
				outputFile << '\n';
			}
		}
		else if (parser.commandType() == 1) {	// c command
			
			outputFile << "111";
			outputFile << code.comp(parser.comp());
			outputFile << code.dest(parser.dest());
			outputFile << code.jump(parser.jump());

			if (parser.hasMoreCommands()) {
				outputFile << '\n';
			}
		}

		
	}

	std::cout << "Done!\n";
	outputFile.close();
	
}