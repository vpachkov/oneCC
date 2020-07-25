cmake_minimum_required(VERSION 3.15)
project(oneCC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CURRENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
string(APPEND CMAKE_CURRENT_SOURCE_DIR "/src")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ArgsParser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/AST)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Config)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Lexer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Tests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Tests/ArgsParser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Tests/Config)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Tests/Lexer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils/ASTReader)

set(COMMON_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ArgsParser/ArgsParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Config/Config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/KeywordManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/TextSequencer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Token.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Parser/Parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/ASTReader/ASTReader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AST/Nodes/Function.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/AST/Nodes/IfStatement.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/AST/Nodes/WhileStatement.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/AST/Nodes/ReturnStatement.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/AST/Nodes/BlockStatement.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/AST/Nodes/FunctionCall.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/SemanticAnalyzer/SemanticAnalyzer.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/SemanticAnalyzer/SemanticAnalyzer.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/SemanticAnalyzer/Scoper/Scoper.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/SemanticAnalyzer/Scoper/Scoper.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/AST/Nodes/Expression.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/CodeGenerator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/RegisterManager/RegisterManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/RegisterManager/RegisterManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Common/ModRM.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Common/Regs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Common/TypesX86_32.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Translators/AbstractX86_32Translator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Translators/AsmTranslator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Translators/AsmTranslator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Common/Regs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator/x86_32/Common/Regs.h)

set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

set(TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests/ArgsParser/ArgsParserTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Config/ConfigTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Lexer/LexerTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests/main.cpp)


add_executable(oneCC_executable ${COMMON_SOURCES} ${TARGET_SOURCES})
add_executable(oneCC_test ${COMMON_SOURCES} ${TEST_SOURCES})

file(
    COPY ${CMAKE_CURRENT_BASE_DIR}/demos/assign_expression.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/demos/
)

file(
    COPY ${CMAKE_CURRENT_BASE_DIR}/demos/example.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/demos/
)

file(
    COPY ${CMAKE_CURRENT_BASE_DIR}/demos/function_definition.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/demos/
)

enable_testing()
