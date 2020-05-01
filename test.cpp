#include "Lexer/Lexer.h"
#include <iostream>

bool compareFiles(const std::string& filename1, const std::string& filename2)
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

bool testLexer()
{
    auto ifstreamPtr = std::make_shared<std::ifstream>("tests/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(ifstreamPtr);
    
    std::fstream ofile("tests/lexer.tmp", std::fstream::in | std::fstream::out | std::fstream::trunc);
    for (;;) {
        auto token = lexer.nextToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else {
            ofile << token.value() << " ";
        }
    }

    ofile.close();
    return compareFiles("tests/lexer_ans.txt", "tests/lexer.tmp");
}

int main()
{
    assert(testLexer() && "Lexer test not passed");
    return 0;
}