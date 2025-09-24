// 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// Parser Implementation
#pragma once
#include "parser.h"
#include <iostream>
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::unique_ptr<Program> Parser::parse()
{
	auto program = std::make_unique<Program>();

	while (!check(TokenKind::End))
	{
		try {
			if (auto stmt = parseStatement())
				program->statements.push_back(std::move(stmt));
			else
				advance();
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Parse error: " << ex.what() << std::endl;
			advance();
		}
	}
	return program;
}

const Token& Parser::peek() const
{
	if (current >= tokens.size())
	{
		static Token endToken{ TokenKind::End, "", 0, 0 };
		return endToken;
	}
	return tokens[current];
}

const Token& Parser::advance()
{
	if (current < tokens.size())
		current++;
	return peek();
}

bool Parser::match(TokenKind kind)
{
	if (check(kind))
	{
		advance();
		return true;
	}
	return false;
}

bool Parser::check(TokenKind kind) const
{
	return peek().kind == kind;
}

const Token& Parser::consume(TokenKind kind, const std::string& message)
{
	if (check(kind))
	{
		return advance();
	}
	throw std::runtime_error(message + " at line " + std::to_string(peek().line));
}

std::unique_ptr<Statement> Parser::parseStatement()
{
	// If statement
	if (check(TokenKind::Keyword) && peek().lexeme == "if")
	{
		return parseIfStatement();
	}
	// While statement
	if (check(TokenKind::Keyword) && peek().lexeme == "while")
	{
		return parseWhileStatement();
	}
	// For statement
	if (check(TokenKind::Keyword) && peek().lexeme == "for")
	{
		return parseForStatement();
	}
	// Foreach statement
	if (check(TokenKind::Keyword) && peek().lexeme == "foreach")
	{
		return parseForeachStatement();
	}
	// Do while statement
	if (check(TokenKind::Keyword) && peek().lexeme == "do")
	{
		return parseDoWhileStatement();
	}
	// Switch statement
	if( check(TokenKind::Keyword) && peek().lexeme == "switch")
	{
		return parseSwitchStatement();
	}
	
	// Use of local or global
	if (check(TokenKind::Keyword) && (peek().lexeme == "local" || peek().lexeme == "global"))
	{
		if (debug)
			std::cout << "is local or global modifier" << std::endl;

		return parseVariableDeclaration();
	}
	// Explicity type string int float etc...
	if (check(TokenKind::Identifier))
	{
		std::string potential_type = peek().lexeme;
		static const std::unordered_set<std::string> types = {
			"int", "float", "string", "char", "bool", "double", "byte"
		};

		if (types.count(potential_type) &&
			current + 1 < tokens.size() &&
			tokens[current + 1].kind == TokenKind::Identifier)
		{

			if (debug)
				std::cout << "Explicity type" << std::endl;

			return parseVariableDeclaration();
		}
			
	}
	// Inference statements (identifier followed by '=') 
	if (check(TokenKind::Identifier) &&
		current + 1 < tokens.size() &&
		tokens[current + 1].kind == TokenKind::Assign)
	{

		return parseVariableDeclaration();
	}
	//Fallback 
	if (check(TokenKind::LBrace))
	{
		return parseBlock();
	}

	//Fallback for expressions
	if (auto expr = parseExpression())
	{
		auto stmt = std::make_unique<ExpressionStatement>();
		stmt->expression = std::move(expr);
		match(TokenKind::Semicolon);
		return stmt;
	}

	return nullptr;
}

std::unique_ptr<Expression> Parser::parseExpression() 
{ 
	return parseAssignment(); 
}

std::unique_ptr<Expression> Parser::parseAssignment()
{
	auto expr = parseEquality();

	
	if (match(TokenKind::Assign))
	{
		auto assign = std::make_unique<AssignmentExpression>();
		// Check if left side is an identifier
		if (auto ident = dynamic_cast<IdentifierExpression*>(expr.get()))
		{
			assign->name = ident->name;
			assign->value = parseExpression();
			return assign;
		}
		throw std::runtime_error("Invalid assignment target");
	}

	return expr;
}

std::unique_ptr<Expression> Parser::parseEquality()
{
	auto expr = parseComparison();

	while (check(TokenKind::Equal) || check(TokenKind::NotEqual))
	{
		auto binary = std::make_unique<BinaryExpression>();
		binary->left = std::move(expr);
		binary->op = peek().kind;
		advance();
		binary->right = parseComparison();
		expr = std::move(binary);
	}
	return expr;
}

std::unique_ptr<Expression> Parser::parseComparison()
{
	auto expr = parseTerm();

	while (check(TokenKind::LessThan) || check(TokenKind::GreaterThan) ||
		   check(TokenKind::LessThanEqual) || check(TokenKind::GreaterThanEqual))
	{
		auto binary = std::make_unique<BinaryExpression>();
		binary->left = std::move(expr);
		binary->op = peek().kind;
		advance();
		binary->right = parseTerm();
		expr = std::move(binary);
	}
	return expr;
}

std::unique_ptr<Expression> Parser::parseTerm()
{
	auto expr = parseFactor();

	while (check(TokenKind::Add) || check(TokenKind::Sub))
	{
		auto binary = std::make_unique<BinaryExpression>();
		binary->left = std::move(expr);
		binary->op = peek().kind;
		advance();
		binary->right = parseFactor();
		expr = std::move(binary);
	}
	return expr;
}

std::unique_ptr<Expression> Parser::parseFactor()
{
	auto expr = parseUnary();

	while(check(TokenKind::Mul) || check(TokenKind::Div) || check(TokenKind::Mod))
	{
		auto binary = std::make_unique<BinaryExpression>();
		binary->left = std::move(expr);
		binary->op = peek().kind;
		advance();
		binary->right = parseUnary();
		expr = std::move(binary);
	}
	return expr;
}

std::unique_ptr<Expression> Parser::parseUnary()
{
	if (check(TokenKind::Not) || check(TokenKind::Sub))
	{
		auto unary = std::make_unique<UnaryExpression>();
		unary->op = peek().kind;
		advance();
		unary->operand = parseUnary();
		return unary;
	}
	return parsePrimary();
}

std::unique_ptr<Expression> Parser::parsePrimary()
{
	// true/false/null
	if (match(TokenKind::Keyword) &&
		peek().lexeme == "true" ||
		peek().lexeme == "false" ||
		peek().lexeme == "null")
	{
		auto literal = std::make_unique<LiteralExpression>();
		literal->value = peek().lexeme;
		literal->types = TokenKind::Keyword;
		advance();
		return literal;
	}
	if (match(TokenKind::Number))
	{
		auto literal = std::make_unique<LiteralExpression>();
		literal->value = tokens[current - 1].lexeme;
		literal->types = TokenKind::Number;
		return literal;
	}

	if (match(TokenKind::StringLiteral))
	{
		auto literal = std::make_unique<LiteralExpression>();
		literal->value = tokens[current - 1].lexeme;
		literal->types = TokenKind::StringLiteral;
		return literal;
	}

	if (match(TokenKind::Char))
	{
		auto literal = std::make_unique<LiteralExpression>();
		literal->value = tokens[current - 1].lexeme;
		literal->types = TokenKind::Char;
		return literal;
	}

	if (match(TokenKind::Identifier))
	{
		auto ident = std::make_unique<IdentifierExpression>();
		ident->name = tokens[current - 1].lexeme;
		return ident;
	}

	if (match(TokenKind::LParen))
	{
		auto expr = parseExpression();
		consume(TokenKind::RParen, "Expected ')' after expression");
		return expr;
	}

	throw std::runtime_error("Unexpected token: " + peek().lexeme);
}

std::unique_ptr<Statement> Parser::parseBlock()
{
	consume(TokenKind::LBrace, "Expected '{' before block");
	auto block = std::make_unique<BlockStatement>();

	while (!check(TokenKind::RBrace) && !check(TokenKind::End))
	{
		if (auto stmt = parseStatement()) {
			block->statements.push_back(std::move(stmt));
		}
	}

	consume(TokenKind::RBrace, "Expected '}' after block");
	return block;
}

std::unique_ptr<Statement> Parser::parseVariableDeclaration()
{
	auto var_decl = std::make_unique<VariableDeclaration>();

	// local or global modifier
	if (check(TokenKind::Keyword) && (peek().lexeme == "local" || peek().lexeme == "global"))
	{
		var_decl->is_global = peek().lexeme == "global";
		advance();
	}

	// Explicitly type
	if (check(TokenKind::Identifier))
	{
		std::string potential_type = peek().lexeme;
		static const std::unordered_set<std::string> types = {
		"int", "float", "string", "char", "bool", "double", "byte" };

		if (types.count(potential_type) &&
			current + 1 < tokens.size() &&
			tokens[current + 1].kind == TokenKind::Identifier)
		{
			var_decl->has_explicit_type = true;	//VarDecl ::= "type" "name"
			var_decl->type_name = potential_type;
			advance();	//Consume type

			consume(TokenKind::Identifier, "Expected variable name after type");	//Variable name)
			var_decl->name = tokens[current - 1].lexeme;	//VarDec
		}
		else {
			var_decl->has_explicit_type = false;	//VarDec ::= "name"
			consume(TokenKind::Identifier, "Expected variable name");	//Variable name)
			var_decl->name = tokens[current - 1].lexeme;
		}
	}

	//Consume operator assing
	consume(TokenKind::Assign, "Expected '=' after variable name");

	//Parse initial value
	var_decl->initializer = parseExpression();

	//Consume semicolon if needed
	match(TokenKind::Semicolon);

	return var_decl;
}

//
// Flow control
//

std::unique_ptr<Statement> Parser::parseIfStatement()
{
	auto stmt = std::make_unique<IfStatement>();

	//Consume If
	consume(TokenKind::Keyword, "Expected 'if' before condition");
	// Parse Condition
	consume(TokenKind::LParen, "Expected '(' after 'if'");
	stmt->condition = parseExpression();
	consume(TokenKind::RParen, "Expected ')' after condition in 'if'");
	
	// Parse Then
	stmt->thenBranch = parseStatement();

	// Parse Else
	if (check(TokenKind::Keyword) && peek().lexeme == "else")
	{
		advance();
		stmt->elseBranch = parseStatement();
	}
	return stmt;
}

std::unique_ptr<Statement> Parser::parseWhileStatement()
{
	auto stmt = std::make_unique<WhileStatement>();
	//Consume While
	consume(TokenKind::Keyword, "Expected while");
	// Parse Condition
	consume(TokenKind::LParen, "Expected '(' after 'while'");
	stmt->condition = parseExpression();
	consume(TokenKind::RParen, "Expected ')' after condition in 'while loop'");

	//Parse Body
	stmt->body = parseStatement();
	return stmt;
}

std::unique_ptr<Statement> Parser::parseDoWhileStatement()
{
	auto stmt = std::make_unique<DoWhileStatement>();
	//Consume Do
	consume(TokenKind::Keyword, "Expected do before condition");
	// Parse Body
	stmt->body = parseStatement();
	// Consume While
	consume(TokenKind::Keyword, "Expected while before condition");
	// Parse Condition
	consume(TokenKind::LParen, "Expected '(' after 'while'");
	stmt->condition = parseExpression();
	consume(TokenKind::RParen, "Expected ')' after condition in 'do while loop'");

	match(TokenKind::Semicolon);

	// Parse Body
	return stmt;
}

std::unique_ptr<Statement> Parser::parseForStatement()
{
	auto stmt = std::make_unique<ForStatement>();
	// Consume For
	consume(TokenKind::Keyword, "Expected 'for' before condition");

	// Parse Condition
	consume(TokenKind::LParen, "Expected '(' after 'for'");
	stmt->condition = parseExpression();
	consume(TokenKind::RParen, "Expected ')' after condition in 'for loop'");

	//Parse Body
	stmt->body = parseStatement();

	return stmt;
}

std::unique_ptr<Statement> Parser::parseForeachStatement()
{
	auto stmt = std::make_unique<ForeachStatement>();
	//Consume Foreach
	consume(TokenKind::Keyword, "Expected foreach before condition");

	// Parse Condition
	consume(TokenKind::LParen, "Expected '(' after 'foreach' ");
	stmt->condition = parseExpression();
	consume(TokenKind::RParen, "Expected ')' after condition ");

	// Parse Body
	stmt->body = parseStatement();
	return stmt;
}

std::unique_ptr<Statement> Parser::parseSwitchStatement()
{
	auto stmt = std::make_unique<SwitchStatement>();
	// Consume Switch
	consume(TokenKind::Keyword, "Expected switch before condition");

	// Parse Condition
	consume(TokenKind::LParen, "Expected '(' after 'switch'");
	stmt->expression = parseExpression();
	consume(TokenKind::RParen, "Expected ')' after condition");

	/*
	{
		// Parse Body
		while (!check(TokenKind::RBrace) && !check(TokenKind::End))
		{
			if (check(TokenKind::Keyword) && peek().lexeme == "case")
			{
				auto casestmt = std::make_unique<CaseStatement>();
				// Consume Case
				advance();

				// Parse Condition
				casestmt->condition = parseExpression();

				//Consume colon
				consume(TokenKind::Colon, "Expected ':' after case");

				// Parse case body (can be a block or a single statement)
				if (check(TokenKind::LBrace))
				{
					casestmt->body = parseBlock();
				}
				else
				{
					casestmt->body = parseStatement();
				}

				stmt->cases.push_back(std::move(casestmt)); // Add case to switch
			}
			else if (check(TokenKind::Keyword) && peek().lexeme == "default")
			{
				auto caseStmt = std::make_unique<CaseStatement>();

				// Consume 'default'
				advance();

				// Consume colon
				consume(TokenKind::Colon, "Expected ':' after default");

				// Parse default body
				if (check(TokenKind::LBrace))
				{
					caseStmt->body = parseBlock();
				}
				else
				{
					caseStmt->body = parseStatement();
				}

				stmt->cases.push_back(std::move(caseStmt));
			}
			else
			{
				break;
			}
		}
	}
	*/




	return stmt;
}
