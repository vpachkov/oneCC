#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Utils/ASTReader/ASTReader.h"
#include "SemanticAnalyzer/SemanticAnalyzer.h"
#include "CodeGenerator/CodeGenerator.h"
#include "Utils/Utils.h"
#include <iostream>
#include <vector>

#define DEBUG_TOKINIZE_FILE
// #define DEBUG_VIZ

inline bool exists_test0(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

int main()
{
#ifdef DEBUG_TOKINIZE_FILE
    auto lexer = oneCC::Lexer::Lexer("demos/example.txt");

    try {
        lexer.tokinizeFile();
    } catch (std::exception& e) {
        std::cout << "\n"
                  << e.what() << "\n";
        return 1;
    }
    for (;;) {
        auto token = lexer.skipToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else {
            std::cout << token.lexeme() << "(" << oneCC::Lexer::Token::typeToString(token) << ") ";
        }
    }
    std::cout << "\n\n";
#endif // DEBUG_TOKINIZE_FILE
    
    auto ifstreamPtr4Parser = std::make_unique<std::ifstream>("demos/example.txt");
    auto lexer4Parser = std::make_unique<oneCC::Lexer::Lexer>(std::move(ifstreamPtr4Parser));
    auto parser = oneCC::Parser::Parser(std::move(lexer4Parser));
    oneCC::AST::Node* root;
    
    try {
        root = parser.parse();
    } catch (std::exception& e) {
        std::cout << "\n" << e.what() << "\n";
        return 1;
    }
    std::cout << "Parsed\n";
    
    auto a = oneCC::SemanticAnalyzer::SemanticAnalyzer().processTree(root);
    std::cout << "Checks passed\n";

#ifdef DEBUG_VIZ
    auto viz = oneCC::ASTUtils::Visualizer();
    viz.genTreePng(root);
#endif // DEBUG_VIZ

    auto codeGen = oneCC::CodeGenerator::CodeGenerator(oneCC::CodeGenerator::TargetPlatform::aarch32);
    codeGen.start(root);

    return 0;
}
