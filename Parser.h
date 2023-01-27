#pragma once
#include <fstream>
#include <string>

class Parser
{
public:
	Parser(char* argv[]);
	~Parser();

	std::string getCurrentCommand();
	bool hasMoreCommands();
	void advance();
	void reset();
	int getLineNumber();
	int commandType();  //returns: 0 for A, 1 for C, 2 for Label, 3 for comment
	std::string dest();
	std::string comp();
	std::string jump();
	std::string symbol();

	bool isInteger(std::string s);
	
private:
	void readFile();
	int openFile(char* argv);

	int lineNumber;
	std::string currentCommand;
	std::ifstream inputFile;
};

