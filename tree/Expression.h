//
// Created by Inqognitoo on 10.10.2022.
//

#ifndef PASCAL_EXPRESSION_H
#define PASCAL_EXPRESSION_H

#include <string_view>

#include "Tree.h"
#include "Token.h"

struct Expression::Binary : public Expression
{
    Expression *m_left, *m_right;
    Token m_operation;

    Binary(Expression* left, Token operation, Expression* right) : m_left(left), m_operation(operation), m_right(right){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Expression::Unary : public Expression
{
    Token m_operation;
    Expression* m_expression;

    Unary(Token operation, Expression* expression) : m_operation(operation), m_expression(expression){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Expression::Call : public Expression
{
    Token m_name;
    Expressions m_args;

    Call(Token name, Expressions args) : m_name(name), m_args(std::move(args)){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Expression::Variable : public Expression
{
    Token m_name;

    Variable(Token name) : m_name(name){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Expression::Integer : public Expression
{
    int m_value;

    Integer(int value) : m_value(value){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Expression::Real : public Expression
{
    float m_value;

    Real(float value) : m_value(value){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Expression::Boolean : public Expression
{
    bool m_value;

    Boolean(bool value) : m_value(value){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Expression::String : public Expression
{
    std::string_view m_value;

    String(std::string_view value) : m_value(value){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

#endif //PASCAL_EXPRESSION_H
