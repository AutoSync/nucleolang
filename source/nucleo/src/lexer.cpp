// 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// Definition of the lexer

#include "lexer.h"
#include <ctype.h>
#include <unordered_set>

//TEMP
#include <iostream>

static const std::unordered_set<std::string> keywords = {
	"local", "global", "public", "protected", "private", "get", "set",
	"if", "else", "while", "for", "foeach", "do", 
	"return", "break", "continue", "pause"
	"true", "false", "null", "trash",
	"promote", "function", "class", "struct", "enum", "switch",
	"in", "to", "as", "out",
	"pipe", "console"
};

Lexer::Lexer(const std::string& source) : source(source) { /* EMPTY DEFINITION */ }

char Lexer::peek() const
{
	if (start >= source.size())
	{
		return '\0';
	}
	return source[start];
}

char Lexer::advance()
{
	if(debug)
		std::cout << "Advance look is: [" << peek() << "]" << std::endl;

	char c = peek();
	if (c == '\0')
	{
		return c;
	}
	++start;
	if (c == '\n')
	{
		++line;
		col = 1;
	}
	else
	{
		col++;
	}
	return c;
}

bool Lexer::match(char expected)
{

	if(debug)
		std::cout << "Match: " << expected << std::endl;

	if (peek() == expected)
	{
		advance();
		return true;
	}
	return false;
}

void Lexer::skipWhitespaceAndComments()
{
	if(debug)
		std::cout << "Init Skip whitespace and comments" << std::endl;

	for (;;)
	{
		char c = peek();
		if (c == '\0') return;
		//WhiteSpace
		if (isspace((unsigned char)c))
		{
			advance();
			continue;
		}
		//Line comments
		if (c == '/' && start + 1 < source.size() && source[start + 1] == '/')
		{
			advance(); advance();
			while (peek() != '\n' && peek() != '\0')
			{
				advance();
			}
			continue;
		}
		//Block comments
		if (c == '/' && start + 1 < source.size() && source[start + 1] == '*')
		{
			advance(); advance();
			while (!(peek() == '*' && start + 1 < source.size() && source[start + 1] == '/') && peek() != '\0')
			{
				advance();
			}
			if (peek() != '\0')
			{
				advance(); advance();
			}
			continue;
		}
		break;
	}
	if(debug)
		std::cout << "End of functiom Skip whitespace and comments" << std::endl;

}

Token Lexer::make_token(TokenKind kind, const std::string& lexeme)
{
	Token token;
	token.kind = kind;
	token.lexeme = lexeme;
	token.line = line;
	token.col = col - (int)lexeme.size();
	return token;
}

Token Lexer::number()
{
	size_t _start = start;
	while (isdigit((unsigned char)peek())) 
	{
		advance();
	}
	// TODO FLOAT, DOUBLE SUPORT
	return make_token(TokenKind::Number, source.substr(_start, start - _start));
}

Token Lexer::indentifierOrKeyword()
{
	size_t _start = start;
	while (isalnum((unsigned char)peek()) || peek() == '_')
	{
		advance();
	}
	std::string lex = source.substr(_start, start - _start);
	if (keywords.count(lex))
	{
		return make_token(TokenKind::Keyword, lex);
	}
	return make_token(TokenKind::Identifier, lex);
}

std::vector<Token> Lexer::tokenize() 
{
	if(debug)
		std::cout << "Initialize Tokenize" << std::endl;

	std::vector<Token> out;
	while (true) 
	{
		if (debug)
			std::cout << "Loop Tokenize" << std::endl;

		skipWhitespaceAndComments();
		
		char look = peek();
		if (look == '\0')
		{
			out.push_back(make_token(TokenKind::End, ""));
			break;
		}
		// Handle numbers
		if (isdigit((unsigned char)look))
		{
			out.push_back(number());
			continue;
		}
		// Handle identifiers and keywords
		if (isalpha((unsigned char)look || look == '_'))
		{
			out.push_back(indentifierOrKeyword());
			continue;
		}

		// Handle operators and punctuation
		switch (look) 
		{
		case '+':
			advance();
			if (match('+')) out.push_back(make_token(TokenKind::Increment, "++"));	// Increment operator ())
			else out.push_back(make_token(TokenKind::Add, "+"));					// Add operator
			break;
		case '-':
			advance();
			if (match('-')) out.push_back(make_token(TokenKind::Decrement, "--"));	// Decrement operator ))
			else out.push_back(make_token(TokenKind::Sub, "-"));					// Subtract operator
			break;
		case '*':
			advance();
			out.push_back(make_token(TokenKind::Mul, "*"));						// Multiply operator
			break;
		case '/':
			advance();
			out.push_back(make_token(TokenKind::Div, "/"));						// Divide operator
			break;
		case '%':
			advance();
			out.push_back(make_token(TokenKind::Mod, "%"));						// Mod operator
			break;
		case '^':
			advance();
			out.push_back(make_token(TokenKind::Pow, "^"));						// Power operator
			break;
		case '(':
			advance();
			out.push_back(make_token(TokenKind::LParen, "("));					// Left Parenthesis
			break;
		case ')':
			advance();
			out.push_back(make_token(TokenKind::RParen, ")"));					// Right Parenthesis
			break;
		case '[':
			advance();
			out.push_back(make_token(TokenKind::LBracket, "["));				// Left Bracket
			break;
		case ']':
			advance();
			out.push_back(make_token(TokenKind::RBracket, "]"));				// Right Bracket
			break;
		case '{':
			advance();
			out.push_back(make_token(TokenKind::LBrace, "{"));					// Left Brace
			break;
		case '}':
			advance();
			out.push_back(make_token(TokenKind::RBrace, "}"));					// Right Brace
			break;
		case ':':
			advance();
			out.push_back(make_token(TokenKind::Colon, ":"));					// Colon
			break;
		case ';':
			advance();
			out.push_back(make_token(TokenKind::Semicolon, ";"));				// Semicolon
			break;
		case ',':
			advance();
			out.push_back(make_token(TokenKind::Comma, ","));					// Comma
			break;
		case '=':
			advance();
			if (match('=')) out.push_back(make_token(TokenKind::Equal, "==")); 	// EQUAL OPERATOR
			else out.push_back(make_token(TokenKind::Assign, "="));				// ASSIGN OPERATOR
			break;
		case '!':
			advance();
			if (match('=')) out.push_back(make_token(TokenKind::NotEqual, "!="));  // NOT EQUAL)
			else out.push_back(make_token(TokenKind::Not, "!"));
			break;
		case '<':
			advance();
			if (match('=')) out.push_back(make_token(TokenKind::LessThanEqual, "<="));		// LESS THAN OR EQUAL)
			else out.push_back(make_token(TokenKind::LessThan, "<"));
			break;
		case '>':
			advance();
			if (match('=')) out.push_back(make_token(TokenKind::GreaterThanEqual, ">="));	// GREATER THAN OR EQUAL
			else out.push_back(make_token(TokenKind::GreaterThan, ">"));
			break;
		case '&':
			advance();
			if (match('&')) out.push_back(make_token(TokenKind::And, "&&"));				// AND OPERATOR &&
			else out.push_back(make_token(TokenKind::MemoryRead, "&"));					// MEMORY READ OPERATOR &
			break;
		case '|':
			advance();
			if (match('>')) out.push_back(make_token(TokenKind::PipeIn, "|>"));			// PROCESS INPUT OPERATOR |>
			else if (match('<')) out.push_back(make_token(TokenKind::PipeOut, "|<"));	// PROCESS OUTPUT OPERATOR |<
			else if (match('|')) out.push_back(make_token(TokenKind::Or, "||"));		// OR OPERATOR ||
			else out.push_back(make_token(TokenKind::Unknown, "|"));					// MEMORY READ OPERATOR |
			break;
		case '@':
			advance();
			if (match('%')) out.push_back(make_token(TokenKind::Malloc, "@%"));			// MEMORY ALLOCATOR OPERATOR @*
			else out.push_back(make_token(TokenKind::Unknown, "@"));					// MEMORY READ OPERATOR @
			break;
		case '#':
			advance();
			if (match('%')) out.push_back(make_token(TokenKind::Delete, "#%"));			// MEMORY DELETE OPERATOR #%
			else out.push_back(make_token(TokenKind::MemoryWrite, "#"));				// MEMORY ADDRESS WRITE OPERATOR #
			break;
		case '"':
		{
			advance(); // Consume opening quote
			std::string str;
			while (peek() != '"' && peek() != '\0') {
				if (peek() == '\\') {
					advance(); // Consume backslash
					switch (peek()) {
					case 'n': str += '\n'; break;
					case 't': str += '\t'; break;
					case 'r': str += '\r'; break;
					case '0': str += '\0'; break;
					case '"': str += '"'; break;
					case '\\': str += '\\'; break;
					default: str += '\\'; str += peek(); break;
					}
					advance();
				}
				else {
					str += advance();
				}
			}
			if (match('"')) {
				out.push_back(make_token(TokenKind::StringLiteral, str));
			}
			else {
				out.push_back(make_token(TokenKind::Unknown, "\"" + str));
			}
			break;
		}
		case '\'':
		{
			advance();
			std::string CharLiteral;
			// Handle escape sequences and read character
			if (peek() == '\\')
			{
				advance();
				switch (peek())
				{
				case 'n': CharLiteral += '\n'; break;
				case 't': CharLiteral += '\t'; break;
				case 'r': CharLiteral += '\r'; break;
				case 'b': CharLiteral += '\b'; break;
				case '0': CharLiteral += '\0'; break;
				case '\'': CharLiteral += '\''; break;
				case '\\': CharLiteral += '\\'; break;
				default: CharLiteral = '\\' + std::string(1, peek()); break;		// Unknown escape sequence
				}
				advance();
			}
			else CharLiteral = std::string(1, advance());
			if (match('\'')) out.push_back(make_token(TokenKind::Char, CharLiteral));	// Char wih()
			else out.push_back(make_token(TokenKind::Unknown, "'" + CharLiteral));		// UNKNOWN TOKEN
			break;
		}
		default:
			//Unknow single character token
			std::string unkn(1, look);
			advance();
			out.push_back(make_token(TokenKind::Unknown, unkn));						// UNKNOWN TOKEN
			break;
		}
	}

	if(debug)
		std::cout << "Complete Tokenize" << std::endl;

	return out;
}