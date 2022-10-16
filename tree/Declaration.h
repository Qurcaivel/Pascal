//
// Created by Inqognitoo on 10.10.2022.
//

#ifndef PASCAL_DECLARATION_H
#define PASCAL_DECLARATION_H

#include "Tree.h"
#include "Token.h"

struct Declaration::Program : public AST
{
    Token m_name;
    Block* m_block;

    Program(Token name, Block* block) : m_name(name), m_block(block){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Declaration::Block : public AST
{
    Declarations m_declarations;
    Statement::Compound* m_compound;

    Block(Declarations declarations, Statement::Compound* compound) : m_declarations(std::move(declarations)), m_compound(compound){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Declaration::Procedure : public Declaration
{
    Token m_name;
    Params m_params;
    Block* m_block;

    Procedure(Token name, Params params, Block* block) : m_name(name), m_params(std::move(params)), m_block(block){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Declaration::Function : public Declaration
{
    Token m_name;
    Params m_params;
    Token m_type;
    Block* m_block;

    Function(Token name, Params params, Token type, Block* block) : m_name(name), m_params(std::move(params)), m_type(type), m_block(block){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Declaration::Const : public Declaration
{
    Token m_name;
    Expression* m_expression;

    Const(Token name, Expression* expression) : m_name(name), m_expression(expression){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Declaration::Var : public Declaration
{
    Token m_name;
    Token m_type;

    Var(Token name, Token type) : m_name(name), m_type(type){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Declaration::Param : public Declaration
{
    Token m_name;
    Token m_type;

    Param(Token name, Token type) : m_name(name), m_type(type){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

#endif //PASCAL_DECLARATION_H
