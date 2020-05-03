#include "LexerTest.h"
#include "../../Lexer/Lexer.h"
#include "../../Lexer/Token.h"
#include <fstream>

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

void LexerTest::test()
{
    auto ifstreamPtr = std::make_shared<std::ifstream>("Tests/Lexer/Data/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(ifstreamPtr);

    std::fstream ofile("Tests/Lexer/Data/lexer.tmp", std::fstream::in | std::fstream::out | std::fstream::trunc);
    for (;;) {
        auto token = lexer.nextToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else {
            ofile << token.value() << " ";
        }
    }

    ofile.close();
    this->assertTrue(compareFiles("Tests/Lexer/Data/lexer_ans.txt", "Tests/Lexer/Data/lexer.tmp"));
}
}