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
        reinterpret_cast<AST::IdentifierNode*>(ternaryOperation->middleChild())->setExpressionType(reinterpret_cast<AST::TypeNode*>(ternaryOperation->leftChild())->type());
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

    // TODO: support implicit conversion (int * float, int / int), as soon as we add more types
    switch (binaryOperation->operation()) {
        case Lexer::TokenType::Equal: {
            binaryOperation->setExpressionType(Lexer::TokenType::TypeBoolean);
            break;
        }
        case Lexer::TokenType::Plus:
        case Lexer::TokenType::Minus:
        case Lexer::TokenType::Multiply: binaryOperation->setExpressionType(Lexer::TokenType::TypeInt);
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
        m_errorFlag = true;
        return;
    }
    auto definedFunction = m_functions[functionCall->name()];
    if (definedFunction->arguments().size() < functionCall->arguments().size()) {
        std::cout << functionCall->name() << " requires " << definedFunction->arguments().size()
                  << " arguments, given " << functionCall->arguments().size() << std::endl;
        m_errorFlag = true;
        return;
    }

    // Here goes checking for type and existence each argument in the scope
    int index = 0;
    for (auto* arg: functionCall->arguments()) {
        visitNode(arg);
        auto argType = static_cast<AST::Expression*>(arg)->expressionType(); // TODO: expression here
        auto definedFunctionArgType = reinterpret_cast<AST::FunctionArgumentNode*>(definedFunction->arguments()[index])->type();
        if (definedFunctionArgType != argType) {
            if (!isConvertationCorrect(argType, definedFunctionArgType)) {
                std::cout << "Convertation";
                m_errorFlag = true;
                return;
            }
        }
        index++;
    }

    // TODO: support arguments with default value, then uncomment
//    while (index < definedFunction->arguments().size()) {
//        if (!reinterpret_cast<AST::FunctionArgumentNode*>(definedFunction->arguments()[index]).defaultExpression()){
//            std::cout << functionCall->name() << " requires " << definedFunction->arguments().size()
//                      << " arguments, given " << index << std::endl;
//            m_errorFlag = true;
//            return;
//        }
//    }

    functionCall->setExpressionType(definedFunction->type());
}

}