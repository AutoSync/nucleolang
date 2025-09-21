// 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// Token Definition
#pragma once

#include <string>
#include <variant>

enum class TokenKind {
	End,																		// End
	Identifier,																	// Identifier
	Number,																		// Number Int, float or double
	Keyword,																	// Keyword
	Add, Sub, Mul, Div, Mod, Pow, Increment, Decrement,							// Math	
	LParen, RParen, LBrace, RBrace, LBracket, RBracket,							// Brackets
	Semicolon, Comma, Colon,													// Delimiters
	Assign,																		// Assignment
	Equal, NotEqual, LessThan, GreaterThan, LessThanEqual, GreaterThanEqual,	// Comparators
	And, Or, Not, Xor,															// Logical Operators
	PipeIn, PipeOut,															// Pipe Operators
	Unknown,																	// Unknown indentifier
	Malloc, Delete, MemoryRead, MemoryWrite,							        // Memory Operators
	String, StringLiteral, Char,												// String Operators
};

struct Token {
	TokenKind kind;
	std::string lexeme;
	int line = 1;
	int col = 1;
};
