#include "SemanticAnalyzer.h"
#include "../Parser/Parser.h"


#define assertCorrect()    \
    if (m_errorFlag)      \
        [[unlikely]]      \
        {                 \
            return;       \
        }

#define error(msg)    \
    std::cout << "Error: " << msg << std::endl;    \
    m_errorFlag = true; \
    return;

namespace oneCC::SemanticAnalyzer {

bool SemanticAnalyzer::processTree(AST::Node *program) {
    visitNode(program);

    return !m_errorFlag;
}

void SemanticAnalyzer::visitNode(AST::ProgramNode* program) {
    for (auto* node : program->nodes()){
        visitNode(node);
        assertCorrect();
    }
}

void SemanticAnalyzer::visitNode(AST::FunctionNode* function) {
    // Checking for function redefinition
    if (m_functions[function->identifier()->value()] || m_scoper.findVar(function->identifier()->value())) {
        error("Redefinition of " << function->identifier()->value());
    }
    // Checking for argument redefinition
    bool wasDefault = false;
    for (auto* arg : function->arguments()) {
        auto expr = reinterpret_cast<AST::FunctionArgumentNode*>(arg)->expression();
        if (expr){
            wasDefault = true;
        } else if (wasDefault){
            error("Function \"" << function->identifier()->value() << "\", default arguments should go after each other")
        }
        auto ident = reinterpret_cast<AST::FunctionArgumentNode*>(arg)->identifier();
        if (!m_scoper.addNode(ident, 1)) {
            error("Redefinition of function argument " << ident->value());
        }
    }


    m_functions[function->identifier()->value()] = function;
    visitNode(function->statement());
}

void SemanticAnalyzer::visitNode(AST::BlockStatementNode* blockStatement) {
    m_scoper.enterScope();
    for (auto* statement : blockStatement->statements()){
        visitNode(statement);
        assertCorrect();
    }
    m_scoper.exitScope();
}

void SemanticAnalyzer::visitNode(AST::TernaryOperationNode* ternaryOperation) {
    if (ternaryOperation->operation() == Lexer::TokenType::Assign) {
        visitNode(ternaryOperation->rightChild());
        assertCorrect();

        auto identifierNode = reinterpret_cast<AST::IdentifierNode*>(ternaryOperation->middleChild());
        identifierNode->setExpressionType(reinterpret_cast<AST::TypeNode*>(ternaryOperation->leftChild())->type());

        if (!m_scoper.addNode(identifierNode)) {
            error("Redefinition of variable" << identifierNode->value());
        }
    }
}

void SemanticAnalyzer::visitNode(AST::ReturnStatementNode* returnNode) {
    visitNode(returnNode->returnedExpression());
    assertCorrect();
    auto returnedType = reinterpret_cast<AST::Expression*>(returnNode->returnedExpression())->expressionType();
    //TODO: When we will add more types, do not forget to check for void
    auto functionType = reinterpret_cast<AST::FunctionNode*>(returnNode->function())->identifier()->expressionType();
    if (!isConvertationCorrect(returnedType, functionType)) {
        //TODO: more information here
        error("Convertation" );
    }
}

void SemanticAnalyzer::visitNode(AST::BinaryOperationNode* binaryOperation) {
    visitNode(binaryOperation->leftChild());
    assertCorrect();
    visitNode(binaryOperation->rightChild());
    assertCorrect();

    // TODO: support implicit conversion (int * float, int / int), as soon as we add more types
    switch (binaryOperation->operation()) {
        case Lexer::TokenType::Assign:
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
        error("Variable " << identifier->value() << " referenced before assignment");
    }
}

void SemanticAnalyzer::visitNode(AST::FunctionCallNode* functionCall) {
    if (m_functions.count(functionCall->name()) == 0) {
        error("Function " << functionCall->name() << " isn\'t defined");
    }
    auto definedFunction = m_functions[functionCall->name()];
    if (definedFunction->arguments().size() < functionCall->arguments().size()) {
        error(functionCall->name() << " requires " << definedFunction->arguments().size()
                  << " arguments, given " << functionCall->arguments().size());
    }

    // Here goes checking for type and existence each argument in the scope
    int index = 0;
    for (auto* arg: functionCall->arguments()) {
        visitNode(arg);
        assertCorrect();

        auto argType = reinterpret_cast<AST::Expression*>(arg)->expressionType();
        auto definedFunctionArgType = reinterpret_cast<AST::FunctionArgumentNode*>(definedFunction->arguments()[index])->identifier()->expressionType();
        if (definedFunctionArgType != argType) {
            if (!isConvertationCorrect(argType, definedFunctionArgType)) {
                //TODO: more information here
                error("Convertation" );
            }
        }
        index++;
    }

    while (index < definedFunction->arguments().size()) {
        if (!reinterpret_cast<AST::FunctionArgumentNode*>(definedFunction->arguments()[index])->expression()){
            error(functionCall->name() << " requires " << definedFunction->arguments().size()
                      << " arguments, given " << index);
        }

    }

    functionCall->setExpressionType(definedFunction->identifier()->expressionType());
}

}