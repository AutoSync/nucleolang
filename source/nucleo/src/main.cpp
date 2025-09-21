// // 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// Main Application


#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

/*
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
*/

void print_expression(const std::unique_ptr<Expression>& expr, int indent = 0) {
    std::string indentation(indent * 2, ' ');

    if (auto lit = dynamic_cast<LiteralExpression*>(expr.get())) {
        std::cout << indentation << "Literal: " << lit->value << std::endl;
    }
    else if (auto ident = dynamic_cast<IdentifierExpression*>(expr.get())) {
        std::cout << indentation << "Identifier: " << ident->name << std::endl;
    }
    else if (auto unary = dynamic_cast<UnaryExpression*>(expr.get())) {
        std::cout << indentation << "Unary op: " << static_cast<int>(unary->op) << std::endl;
        print_expression(unary->operand, indent + 1);
    }
    else if (auto binary = dynamic_cast<BinaryExpression*>(expr.get())) {
        std::cout << indentation << "Binary op: " << static_cast<int>(binary->op) << std::endl;
        std::cout << indentation << "Left:" << std::endl;
        print_expression(binary->left, indent + 1);
        std::cout << indentation << "Right:" << std::endl;
        print_expression(binary->right, indent + 1);
    }
    else if (auto assign = dynamic_cast<AssignmentExpression*>(expr.get())) {
        std::cout << indentation << "Assignment to: " << assign->name << std::endl;
        std::cout << indentation << "Value:" << std::endl;
        print_expression(assign->value, indent + 1);
    }
}

void test_parser(const std::string& source) {
    std::cout << "=== Testing: " << source << " ===" << std::endl;

    try {
        Lexer lexer(source);
        auto tokens = lexer.tokenize();

        std::cout << "Tokens: ";
        for (const auto& token : tokens) {
            std::cout << token.lexeme << " ";
        }
        std::cout << std::endl;

        Parser parser(tokens);
        auto program = parser.parse();

        std::cout << "Parse successful! AST:" << std::endl;
        for (const auto& stmt : program->statements) {
            if (auto expr_stmt = dynamic_cast<ExpressionStatement*>(stmt.get())) {
                print_expression(expr_stmt->expression);
            }
        }

    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    std::cout << "Nucleo Parser Test" << std::endl;
    std::cout << "==================" << std::endl;

    // Testes simples
    test_parser("42");
    test_parser("x");
    test_parser("-10");
    test_parser("!true");
    test_parser("2 + 3");
    test_parser("2 * 3 + 4");
    test_parser("2 * (3 + 4)");
    test_parser("x = 5");
    test_parser("a + b * c");
    test_parser("x == 10");
    test_parser("x > 5 && y < 10");
    test_parser("2 + 3 * 4 - 5 / 2");
    test_parser("x = y = 10");
    test_parser("a && b || c");
    test_parser("-x + !y");

    return 0;
}