#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>



Parser::Parser(char* argv[])
{
	lineNumber = -1;
	if (openFile(argv[1]) == 1)
	{
		std::cout << "Error: could not open input file.\n";
	}
}

Parser::~Parser()
{
	inputFile.close();
}

bool Parser::isInteger(std::string s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

int Parser::openFile(char* filename)
{
	inputFile = std::ifstream(filename);

	if (!inputFile.is_open()) {
		return 1;
	}

	return 0;
}
void Parser::readFile()		//reads a line in inputFile and assigns it to currentCommand (removes whitespace and comments)
{
	char* line = new char[512];
	inputFile.getline(line, 512);
	currentCommand = std::string(line);
	currentCommand.erase(std::remove_if(currentCommand.begin(), currentCommand.end(), isspace), currentCommand.end());	//removes whitespace
	currentCommand = currentCommand.substr(0, currentCommand.find('/'));	//removes comments
}

void Parser::advance()
{
	readFile();
	if (currentCommand.length() != 0 && commandType() != 2)
		lineNumber++;
}

void Parser::reset()		//reset to beginning of file
{
	inputFile.clear();
	inputFile.seekg(0, std::ios::beg);
	lineNumber = -1;
	readFile();
}

int Parser::getLineNumber()
{
	return lineNumber;
}

std::string Parser::getCurrentCommand()
{
	return currentCommand;
}

bool Parser::hasMoreCommands()
{
	if (inputFile.peek() != -1) {
		return true;
	}
	else
		return false;

}

std::string Parser::dest()
{
	if (currentCommand.find("=") == std::string::npos) {
		return "";
	}

	size_t pos = currentCommand.find("=");
	return currentCommand.substr(0, pos);
}

std::string Parser::comp()
{
	size_t equalsPos = currentCommand.find("=");
	size_t semicolonPos = currentCommand.find(";");
	size_t newlinePos = currentCommand.find("\n");
	if (equalsPos != std::string::npos && semicolonPos != std::string::npos) {	 //currentCommand contains both '=' and ';'
		return currentCommand.substr(equalsPos + 1, semicolonPos - equalsPos - 1);
	}
	else if (equalsPos != std::string::npos) {
		return currentCommand.substr(equalsPos + 1, newlinePos - equalsPos - 1);
	}
	else if (semicolonPos != std::string::npos) {
		return currentCommand.substr(0, semicolonPos);
	}
	else {
		std::cout << "error: does not contain a comp command\n";
		return "";
	}
}

std::string Parser::jump()
{
	size_t semicolonPos = currentCommand.find(";");
	size_t newlinePos = currentCommand.find("\n");

	if (currentCommand.find("J") != std::string::npos)
		return currentCommand.substr(semicolonPos + 1, newlinePos - semicolonPos - 1);
	else
		return "";
}

std::string Parser::symbol()
{
	if (commandType() == 2)		//label
		return currentCommand.substr(1, currentCommand.length() - 2);
	else if (commandType() == 0 && !isInteger(std::string(1, currentCommand.at(1))))	//a command using a variable
		return currentCommand.substr(1, currentCommand.find('\n') - 1);
	else
		return "";
} 

int Parser::commandType()
{
	if (currentCommand.length() != 0) {
		if (currentCommand.at(0) == '@')	//A command
			return 0;
		else if (currentCommand.at(0) == '(')	//Label
			return 2;
		else if (currentCommand.at(0) == '/' || currentCommand.at(0) == '\n')	//comment
			return 3;
		else							//C command
			return 1;	
	}
	else
		return -1;
}


