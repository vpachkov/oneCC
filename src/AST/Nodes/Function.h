#pragma once
#include "../ASTNode.h"
#include "BlockStatement.h"
#include "FunctionArgument.h"
#include "Identifier.h"
#include <string>
#include <utility>
#include <vector>

namespace oneCC::AST {

class FunctionNode : public Node {
public:
    FunctionNode()
        : Node(servedType())
    {
    }

    FunctionNode(IdentifierNode* identifier, const std::vector<FunctionArgumentNode*>& arguments, BlockStatementNode* statement)
        : Node(servedType())
        , m_identifier(identifier)
        , m_arguments(arguments)
        , m_statement(statement)
    {
    }

    FunctionNode(IdentifierNode* identifier, std::vector<FunctionArgumentNode*>&& arguments, BlockStatementNode* statement)
        : Node(servedType())
        , m_identifier(identifier)
        , m_arguments(std::move(arguments))
        , m_statement(statement)
    {
    }

    ~FunctionNode() override = default;

    void setIdentifier(IdentifierNode* identifier) { m_identifier = identifier; }
    void setArguments(std::vector<FunctionArgumentNode*> arguments) { m_arguments = arguments; }
    void setArguments(std::vector<FunctionArgumentNode*>&& arguments) { m_arguments = std::move(arguments); }
    void setStatement(BlockStatementNode* statement) { m_statement = statement; }

    IdentifierNode* identifier() const { return m_identifier; }
    BlockStatementNode* statement() const { return m_statement; }
    const std::vector<FunctionArgumentNode*>& arguments() const { return m_arguments; }

    static NodeType servedType() { return Function; }

private:
    IdentifierNode* m_identifier {};
    std::vector<FunctionArgumentNode*> m_arguments {};
    BlockStatementNode* m_statement {};
};

}
