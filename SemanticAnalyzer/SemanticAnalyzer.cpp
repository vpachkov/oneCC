#include "SemanticAnalyzer.h"
#include "../Parser/Parser.h"
#include "FunctionCollector/FunctionCollector.h"

namespace oneCC::SemanticAnalyzer {

bool SemanticAnalyzer::processTree(AST::Node *program) {
    m_functions = FunctionCollector().getFunctions(program);

    return m_errorFlag;
}

void SemanticAnalyzer::visitNode(AST::ProgramNode* program) {
    for (auto* func : program->funcs()){
        visitNode(func);
    }
}

void SemanticAnalyzer::visitNode(AST::FunctionNode* function) {
    // TODO: add global variables support
    for (auto* identifier : function->arguments()) {
        if (!m_scoper.addNode(reinterpret_cast<AST::IdentifierNode *>(identifier), 1)) {
            //TODO: output more information
            std::cout << "Redefinition of variable" << std::endl;
            m_errorFlag = true;
            return;
        }
    }
    visitNode(function->statement());
}

void SemanticAnalyzer::visitNode(AST::BlockStatementNode* blockStatement) {
    m_scoper.enterScope();
    for (auto* statement : blockStatement->statements()){
        visitNode(statement);
    }
    m_scoper.exitScope();
}

void SemanticAnalyzer::visitNode(AST::TernaryOperationNode* ternaryOperation) {
    if (ternaryOperation->operation() == Lexer::TokenType::Assign) {
        visitNode(ternaryOperation->rightChild());
        reinterpret_cast<AST::IdentifierNode*>(ternaryOperation->middleChild())->setType(reinterpret_cast<AST::TypeNode*>(ternaryOperation->leftChild())->type());
        if (!m_scoper.addNode(reinterpret_cast<AST::IdentifierNode*>(ternaryOperation->middleChild()))) {
            //TODO: output more information
            std::cout << "Redefinition of variable" << std::endl;
            m_errorFlag = true;
            return;
        }
    }
}

void SemanticAnalyzer::visitNode(AST::BinaryOperationNode* binaryOperation) {
    // TODO: somewhere here we need to add type for local root based on child's type -> (half way done)
    visitNode(binaryOperation->leftChild());
    visitNode(binaryOperation->rightChild());

    // TODO: support implicit conversion (int * float, int / int)
    switch (binaryOperation->operation()) {
        case Lexer::TokenType::Equal: {
            binaryOperation->setType(Lexer::TokenType::TypeBoolean);
            break;
        }
        case Lexer::TokenType::Plus:
        case Lexer::TokenType::Minus:
        case Lexer::TokenType::Multiply: binaryOperation->setType(Lexer::TokenType::TypeInt);
        default: break;
    }
}

void SemanticAnalyzer::visitNode(AST::IdentifierNode* identifier) {
    auto* var = m_scoper.findVar(identifier->value());
    if (!var){
        std::cout << "Variable " << identifier->value() << " referenced before assignment" << std::endl;
        m_errorFlag = true;
        return;
    }
}

void SemanticAnalyzer::visitNode(AST::FunctionCallNode* functionCall) {
    if (m_functions.count(functionCall->name()) == 0) {
        std::cout << "Function " << functionCall->name() << " isn\'t defined" << std::endl;
        return;
    }
    auto definedFunction = m_functions[functionCall->name()];
    if (definedFunction->arguments().size() < functionCall->arguments().size()) {
        std::cout << "Too much arguments for function " << functionCall->name() << std::endl;
    }

    // TODO: here goes checking for type and existence each argument in the scope
    for (auto* arg: functionCall->arguments()) {
        visitNode(arg);
        auto argName = reinterpret_cast<AST::FunctionArgumentNode*>(arg)->name(); // TODO: expression here
        auto* var = m_scoper.findVar(argName);
        if (!var) {
            std::cout << "Variable " << argName << " referenced before assignment" << std::endl;
            m_errorFlag = true;
            return;
        }
        // TODO: all expressions should be inherited from expression class with type field, then check this way
        // if (var->type() != currentArg
    }
}

}