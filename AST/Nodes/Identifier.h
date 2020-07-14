#pragma once
#include "../ASTNode.h"
#include <string>

namespace oneCC::AST {

class IdentifierNode : public Node {
public:
    IdentifierNode()
        : Node(servedType())
    {
    }

    explicit IdentifierNode(const std::string& value)
        : Node(servedType())
        , m_value(value)
    {
    }

    explicit IdentifierNode(std::string&& value)
        : Node(servedType())
        , m_value(std::move(value))
    {
    }

    ~IdentifierNode() override = default;

    const std::string& value() const { return m_value; }

    static NodeType servedType() { return Identifier; }

private:
    std::string m_value {};
};

}