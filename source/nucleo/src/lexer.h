// // 2018 - 2025 (C) AutoSync Nucleo Language - All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// Lexer Definition
#pragma once

#include "token.h"
#include <string>
#include <vector>

class Lexer 
{
public: 
	Lexer(const std::string& source);
	std::vector<Token> tokenize();
private:
	//VARIABLES
	const std::string source;
	size_t start = 0;
	int line = 1, col = 1;
	bool debug = false;

	//FUNCTIONS
	char peek() const;
	char advance();
	bool match(char expected);
	void skipWhitespaceAndComments();
	Token make_token(TokenKind token, const std::string& lexeme);
	Token number();
	Token indentifierOrKeyword();
};
