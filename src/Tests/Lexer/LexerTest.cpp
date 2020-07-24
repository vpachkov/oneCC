#include "LexerTest.h"
#include "../../Lexer/Lexer.h"
#include "../../Lexer/Token.h"
#include <fstream>
#include <iostream>
#include <chrono>

namespace oneCC::Tests {

bool LexerTest::compareFiles(const std::string& filename1, const std::string& filename2)
{
    std::ifstream file1(filename1, std::ifstream::ate);
    std::ifstream file2(filename2, std::ifstream::ate);

    if (file1.tellg() != file2.tellg()) {
        return false;
    }

    file1.seekg(0);
    file2.seekg(0);

    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);

    return std::equal(begin1, std::istreambuf_iterator<char>(), begin2);
}

void LexerTest::testCorrectness()
{
    auto ifstreamPtr = std::make_unique<std::ifstream>("Tests/Lexer/Data/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(std::move(ifstreamPtr));
    lexer.tokinizeFile();

    std::fstream ofile("Tests/Lexer/Data/lexer.tmp", std::fstream::in | std::fstream::out | std::fstream::trunc);
    for (;;) {
        auto token = lexer.skipToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else if (token.type() == oneCC::Lexer::TokenType::Error) {
            this->assertTrue(0);
            return;
        } else {
            ofile << token.lexeme() << "(" << oneCC::Lexer::Token::typeToString(token) << ") ";
        }
    }

    ofile.close();
    this->assertTrue(compareFiles("Tests/Lexer/Data/lexer_ans.txt", "Tests/Lexer/Data/lexer.tmp"));
}

void LexerTest::testSpeed()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto ifstreamPtr = std::make_unique<std::ifstream>("Tests/Lexer/Data/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(std::move(ifstreamPtr));
    lexer.tokinizeFile();
    for (;;) {
        auto token = lexer.skipToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\u001b[34mInfo: \u001b[0m" << name() << ": " << duration.count() << "ms\n";
}

void LexerTest::test()
{
    testSpeed();
    testCorrectness();
}
}