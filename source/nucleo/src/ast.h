// 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// AST - Abstract Syntax Tree Definition
#pragma once
#include "token.h"
#include <memory>
#include <vector>
#include <string>

//Forward Declaration
struct Program;
struct Statement;
struct Expression;

//Expression Struct
struct Expression {
	virtual ~Expression() = default;
};

struct UnaryExpression : Expression {
	std::unique_ptr<Expression> operand;
	TokenKind op;
};

struct BinaryExpression : Expression {
	std::unique_ptr<Expression> left;
	TokenKind op;
	std::unique_ptr<Expression> right;
};

struct LiteralExpression : Expression {
	std::string value;
	TokenKind Types;
};

struct IdentifierExpression : Expression {
	std::string name;
};

struct AssignmentExpression : Expression {
	std::string name;
	std::unique_ptr<Expression> value;
};

//Statement
struct Statement {
	virtual ~Statement() = default;
};

struct ExpressionStatement : Statement {
	std::unique_ptr<Expression> expression;
};

struct VariableDeclaration : Statement {
	std::string name;
	std::unique_ptr<Expression> initializer;
	bool is_global = false;						// Scope local/Global
	bool has_explicit_type = false;				// inference or explicit typing
	std::string type_name;						// para tipagem explícita (ex: "string", "int")
};

struct BlockStatement : Statement {
	std::vector<std::unique_ptr<Statement>> statements;
};

struct Program {
	std::vector<std::unique_ptr<Statement>> statements;
};