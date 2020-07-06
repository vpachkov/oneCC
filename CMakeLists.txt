cmake_minimum_required(VERSION 3.15)
project(oneCC)

set(CMAKE_CXX_STANDARD 20)

include_directories(ArgsParser)
include_directories(AST)
include_directories(Config)
include_directories(Lexer)
include_directories(Parser)
include_directories(Tests)
include_directories(Tests/ArgsParser)
include_directories(Tests/Config)
include_directories(Tests/Lexer)
include_directories(Utils)
include_directories(Utils/Debug)


add_executable(
        oneCC_executable
        ArgsParser/ArgsParser.cpp
        Config/Config.cpp
        Lexer/KeywordManager.cpp
        Lexer/Lexer.cpp
        Lexer/TextSequencer.cpp
        Lexer/Token.cpp
        Parser/Parser.cpp
        Tests/ArgsParser/ArgsParserTest.cpp
        Tests/Config/ConfigTest.cpp
        Tests/Lexer/LexerTest.cpp
#        Tests/main.cpp
        main.cpp
)

enable_testing()
