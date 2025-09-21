// // 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// Main Application


#include <iostream>
#include <fstream>
#include "lexer.h"

int main(int argc, char** argv)
{
	//GUI Initialization
	std::cout << "Nucleo Lang Live Compiler \n";

	if (argc < 2)
	{
		std::cerr << "Usage: live compiler <file.nucleo> \n";
		return 1;
	}

	std::fstream in(argv[1]);
	std::string source((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	Lexer lexer(source);
	auto tokens = lexer.tokenize();

	std::cout << "Procesing...\n";
	for (auto &token : tokens)
	{
		std::cout << "(" << (int)token.kind << ") " << token.lexeme << "[" << token.line << ", " << token.col << "]" << "\n";
	}

	std::cout << "Complete\n";
	return 0;
}