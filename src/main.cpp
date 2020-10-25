#include "ArgsParser/ArgsParser.h"
#include "CodeGenerator/CodeGenerator.h"
#include "Config/Config.h"
#include "Helpers/Defines.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "SemanticAnalyzer/SemanticAnalyzer.h"
#include "Utils/ASTReader/ASTReader.h"
#include "Utils/Utils.h"

#include <iostream>
#include <vector>

// #define DEBUG_TOKINIZE_FILE
// #define DEBUG_VIZ

// TODO: Normal args dump.
void helpHandler()
{
    std::cout << "oneCC Compiler\n";
    std::cout << "\nAvailbale commands:\n";
    std::cout << "-f --file     : input C file\n";
    std::cout << "-p --platform : x86_32 or aarch32\n";
    std::cout << "   --version  : prints version of the compiler\n";
    std::cout << "-h --help     : helps you\n\n";
    std::cout << "Written by Plunkerusr & nimelehin\n\n";
    exit(0);
}

void versionHandler()
{
    std::cout << VERSION << "\n" << GIT_HASH << " @" << GIT_BRANCH;
    exit(0);
}

int main(int argc, char* argv[])
{
#ifdef DEBUG_TOKINIZE_FILE
    auto lexer = oneCC::Lexer::Lexer("demos/example.c");

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
    auto* configInstnace = oneCC::Config::Config::get();
    auto* argsParser = new oneCC::ArgsParser::ArgsParser(argc, argv);
    argsParser->registerHandler(configInstnace->version, versionHandler, "--version");
    argsParser->registerHandler(configInstnace->help, helpHandler, "--help", "-h");
    argsParser->registerArgument(configInstnace->filename, "--file", "-f", false);
    argsParser->registerArgument(configInstnace->platform, "--platform", "-p", false);

    if (configInstnace->filename.empty()) {
        std::cout << "No input file provided. Exiting...\n\n";
        return 1;
    }

    auto ifstreamPtr4Parser = std::make_unique<std::ifstream>(configInstnace->filename);
    auto lexer4Parser = std::make_unique<oneCC::Lexer::Lexer>(std::move(ifstreamPtr4Parser));
    auto parser = oneCC::Parser::Parser(std::move(lexer4Parser));
    oneCC::AST::Node* root;

    try {
        root = parser.parse();
    } catch (std::exception& e) {
        std::cout << "Parser error\n"
                  << e.what() << "\n";
        return 1;
    }

    try {
        if (!oneCC::SemanticAnalyzer::SemanticAnalyzer().processTree(root)) {
            return -1;
        }
    } catch (std::exception& e) {
        std::cout << "Unexpected error in SemanticAnalyzer" << e.what() << "\n";
        return -1;
    }

#ifdef DEBUG_VIZ
    auto viz = oneCC::ASTUtils::Visualizer();
    viz.genTreePng(root);
#endif // DEBUG_VIZ

    try {
        oneCC::CodeGenerator::TargetPlatform target;
        if (configInstnace->platform == "x86_32") {
            target = oneCC::CodeGenerator::TargetPlatform::x86_32;
        } else if (configInstnace->platform == "aarch32") {
            target = oneCC::CodeGenerator::TargetPlatform::aarch32;
        } else {
            std::cout << "Undefined platform: " << configInstnace->platform << "\n";
        }
        oneCC::CodeGenerator::CodeGenerator codeGen(target);
        codeGen.start(root);
    } catch (std::exception& e) {
        std::cout << "Unexpected error in CodeGenerator " << e.what() << "\n";
    }

    return 0;
}
