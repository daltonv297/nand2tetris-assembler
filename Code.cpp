#include "Code.h"
#include <iostream>
#include <string>
#include <bitset>


Code::Code()
{
}


Code::~Code()
{
}

std::string Code::toMachineLang(std::string m, int commandType)
{
	return "";
}

std::string Code::dest(std::string m)
{
	
	int total = 0;
	if (m.find("M") != std::string::npos) {
		total += 0b001;
	}
	if (m.find("D") != std::string::npos) {
		total += 0b010;
	}
	if (m.find("A") != std::string::npos) {
		total += 0b100;
	}

	return std::bitset< 3 >(total).to_string();
}

std::string Code::comp(std::string m)
{
	int mcode = 0;

	if (m == "0")
		mcode = 0b0101010;
	else if (m == "1")
		mcode = 0b0111111;
	else if (m == "-1")
		mcode = 0b0111010;
	else if (m == "D")
		mcode = 0b0001100;
	else if (m == "A")
		mcode = 0b0110000;
	else if (m == "!D")
		mcode = 0b0001101;
	else if (m == "!A")
		mcode = 0b0110001;
	else if (m == "-D")
		mcode = 0b0001111;
	else if (m == "-A")
		mcode = 0b0110011;
	else if (m == "D+1")
		mcode = 0b0011111;
	else if (m == "A+1")
		mcode = 0b0110111;
	else if (m == "D-1")
		mcode = 0b0001110;
	else if (m == "A-1")
		mcode = 0b0110010;
	else if (m == "D+A")
		mcode = 0b0000010;
	else if (m == "D-A")
		mcode = 0b0010011;
	else if (m == "A-D")
		mcode = 0b0000111;
	else if (m == "D&A")
		mcode = 0b0000000;
	else if (m == "D|A")
		mcode = 0b0010101;

	else if (m == "M")
		mcode = 0b1110000;
	else if (m == "!M")
		mcode = 0b1110001;
	else if (m == "-M")
		mcode = 0b1110011;
	else if (m == "M+1")
		mcode = 0b1110111;
	else if (m == "M-1")
		mcode = 0b1110010;
	else if (m == "D+M")
		mcode = 0b1000010;
	else if (m == "D-M")
		mcode = 0b1010011;
	else if (m == "M-D")
		mcode = 0b1000111;
	else if (m == "D&M")
		mcode = 0b1000000;
	else if (m == "D|M")
		mcode = 0b1010101;
	else
		std::cout << "Error: no comp mnemonic\n";

	return std::bitset< 7 >(mcode).to_string();

}

std::string Code::jump(std::string m)
{
	int mcode = 0;

	if (m == "JGT")
		mcode = 0b001;
	if (m == "JEQ")
		mcode = 0b010;
	if (m == "JGE")
		mcode = 0b011;
	if (m == "JLT")
		mcode = 0b100;
	if (m == "JNE")
		mcode = 0b101;
	if (m == "JLE")
		mcode = 0b110;
	if (m == "JMP")
		mcode = 0b111;

	return std::bitset< 3 >(mcode).to_string();
}

std::string Code::aCommand(std::string m)
{
	if (m.at(0) != '@') {
		std::cout << "Error: not an a command\n";
		return "";
	}

	std::string address_str = m.substr(1);
	int address = std::stoi(address_str);
	
	return "0" + std::bitset< 15 >(address).to_string();
}