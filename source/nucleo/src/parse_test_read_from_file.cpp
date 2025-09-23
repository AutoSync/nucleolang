// 2018 - 2025 © AutoSync Nucleo Lang All Rights Reserved | Erick Andrade MIT License
// https://github.com/AutoSync/nucleolang
// Nucleo Compiler - File-based Testing

#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

bool debug = true;

std::string tokenToString(TokenKind kind) {
    switch (kind) {
    case TokenKind::End: return "End";
    case TokenKind::Identifier: return "Identifier";
    case TokenKind::Number: return "Number";
    case TokenKind::Keyword: return "Keyword";
    case TokenKind::Add: return "Add";
    case TokenKind::Sub: return "Sub";
    case TokenKind::Mul: return "Mul";
    case TokenKind::Div: return "Div";
    case TokenKind::Mod: return "Mod";
    case TokenKind::Pow: return "Pow";
    case TokenKind::Increment: return "Increment";
    case TokenKind::Decrement: return "Decrement";
    case TokenKind::LParen: return "LParen";
    case TokenKind::RParen: return "RParen";
    case TokenKind::LBrace: return "LBrace";
    case TokenKind::RBrace: return "RBrace";
    case TokenKind::LBracket: return "LBracket";
    case TokenKind::RBracket: return "RBracket";
    case TokenKind::Semicolon: return "Semicolon";
    case TokenKind::Comma: return "Comma";
    case TokenKind::Colon: return "Colon";
    case TokenKind::Assign: return "Assign";
    case TokenKind::Equal: return "Equal";
    case TokenKind::NotEqual: return "NotEqual";
    case TokenKind::LessThan: return "LessThan";
    case TokenKind::GreaterThan: return "GreaterThan";
    case TokenKind::LessThanEqual: return "LessThanEqual";
    case TokenKind::GreaterThanEqual: return "GreaterThanEqual";
    case TokenKind::And: return "And";
    case TokenKind::Or: return "Or";
    case TokenKind::Not: return "Not";
    case TokenKind::Xor: return "Xor";
    case TokenKind::PipeIn: return "PipeIn";
    case TokenKind::PipeOut: return "PipeOut";
    case TokenKind::Unknown: return "Unknown";
    case TokenKind::Malloc: return "Malloc";
    case TokenKind::Delete: return "Delete";
    case TokenKind::MemoryRead: return "MemoryRead";
    case TokenKind::MemoryWrite: return "MemoryWrite";
    case TokenKind::String: return "String";
    case TokenKind::StringLiteral: return "StringLiteral";
    case TokenKind::Char: return "Char";
    default: return "UnknownToken";
    }
}

class ASTPrinter {
public:
    void print(const std::unique_ptr<Program>& program) {
        std::cout << "\n=== ABSTRACT SYNTAX TREE ===" << std::endl;
        for (size_t i = 0; i < program->statements.size(); ++i) {
            std::cout << "Statement " << i + 1 << ":" << std::endl;
            print_statement(program->statements[i], 1);
            std::cout << std::endl;
        }
    }

private:
    void print_statement(const std::unique_ptr<Statement>& stmt, int indent) {
        std::string indentation(indent * 2, ' ');
        // ... (resto mantido igual)
    }
};

void compile_file(const std::string& filename) {
    std::cout << "Nucleo Lang Compiler" << std::endl;
    std::cout << "Loading: " << filename << std::endl;
    std::cout << "========================================" << std::endl;

    try {
        // Ler arquivo
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();

        std::cout << "Source code:" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << source << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        // Lexer
        std::cout << "\nLEXICAL ANALYSIS" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        Lexer lexer(source);
        auto tokens = lexer.tokenize();

        if (debug) {
            std::cout << "Tokens found:" << std::endl;
            for (size_t i = 0; i < tokens.size(); ++i) {
                const auto& token = tokens[i];
                std::cout << "[" << i << "] " << tokenToString(token.kind)
                    << " '" << token.lexeme << "'"
                    << " (line " << token.line << ", col " << token.col << ")" << std::endl;
            }
        }

        // Parser
        std::cout << "\nSYNTACTIC ANALYSIS" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        Parser parser(tokens);
        auto program = parser.parse();

        // AST Printing
        ASTPrinter printer;
        printer.print(program);

        std::cout << "\nCOMPILATION SUCCESSFUL!" << std::endl;
        std::cout << "Statistics:" << std::endl;
        std::cout << "  - Statements: " << program->statements.size() << std::endl;
        std::cout << "  - Tokens: " << tokens.size() << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "\nCOMPILATION ERROR: " << e.what() << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: nucleo <file.nu> [--debug|--release]" << std::endl;
        std::cout << "Examples:" << std::endl;
        std::cout << "  nucleo program.nu" << std::endl;
        std::cout << "  nucleo test.nu --debug" << std::endl;
        std::cout << "  nucleo example.nu --release" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--release") debug = false;
        else if (arg == "--debug") debug = true;
    }

    compile_file(filename);
    return 0;
}