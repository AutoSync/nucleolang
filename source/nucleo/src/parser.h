// 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// Parser Definition
#pragma once


#include "ast.h"
#include "token.h"
#include <vector>
#include <memory>

class Parser {
public:
	Parser(const std::vector<Token>& tokens);
	std::unique_ptr<Program> parse();
private:
	// Variables
	std::vector<Token> tokens;
	size_t current = 0;

	// Methods
	const Token& peek() const;
	const Token& advance();
	bool match(TokenKind kind);
	bool check(TokenKind kind) const;
	const Token& consume(TokenKind kind, const std::string& errorMs);

	// Rules execution
	std::unique_ptr<Statement> parseStatement();
	std::unique_ptr<Expression> parseExpression();
	std::unique_ptr<Expression> parseAssignment();
	std::unique_ptr<Expression> parseEquality();
	std::unique_ptr<Expression> parseComparison();
	std::unique_ptr<Expression> parseTerm();
	std::unique_ptr<Expression> parseFactor();
	std::unique_ptr<Expression> parseUnary();
	std::unique_ptr<Expression> parsePrimary();
	std::unique_ptr<Expression> parseBlock();
	std::unique_ptr<Expression> parseVariableScopeDeclaration();
	std::unique_ptr<Expression> parseVariableDeclaration();
	std::unique_ptr<Expression> parseFunctionDeclaration();
	std::unique_ptr<Expression> parseFunctionCall();
	std::unique_ptr<Expression> parseIfStatement();
};