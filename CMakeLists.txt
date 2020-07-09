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
        AST/Nodes/TernaryOperaion.h AST/Nodes/Identifier.h AST/Nodes/Type.h
        Utils/Debug/ASTReader.cpp
        AST/Nodes/Function.h AST/Nodes/IfStatement.h AST/Nodes/WhileStatement.h AST/Nodes/ReturnStatement.h AST/Nodes/BlockStatement.h AST/Nodes/FunctionCall.h)

file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Lexer/Data/assign_expression.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Tests/Lexer/Data/
)
file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Lexer/Data/lexer.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Tests/Lexer/Data/
)

enable_testing()
