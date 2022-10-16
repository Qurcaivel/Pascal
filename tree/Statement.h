//
// Created by Inqognitoo on 10.10.2022.
//

#ifndef PASCAL_STATEMENT_H
#define PASCAL_STATEMENT_H

#include "Tree.h"
#include "Token.h"

struct Statement::Compound : public Statement
{
    Statements m_statements;

    Compound(Statements statements) : m_statements(std::move(statements)){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Assign : public Statement
{
    Token m_name;
    Expression* m_expression;

    Assign(Token name, Expression* expression) : m_name(name), m_expression(expression){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Expr : public Statement
{
    Expression* m_expression;

    Expr(Expression* expression) : m_expression(expression){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Loop : public Statement
{
    Token m_type;
    Expression* m_condition;
    Statement* m_statement;

    Loop(Token type, Expression* condition, Statement* statement) : m_type(type), m_condition(condition), m_statement(statement){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::For : public Statement
{
    Assign* m_assign;
    Token m_direction;
    Expression* m_expression;
    Statement* m_statement;

    For(Assign* assign, Token direction, Expression* expression, Statement* statement) : m_assign(assign), m_direction(direction), m_expression(expression), m_statement(statement){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::If : public Statement
{
    Expression *m_condition;
    Statement *m_if_branch, *m_else_branch;

    If(Expression* condition, Statement* if_branch, Statement* else_branch) : m_condition(condition), m_if_branch(if_branch), m_else_branch(else_branch){}
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Continue : public Statement
{
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Break : public Statement
{
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Exit : public Statement
{
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Halt : public Statement
{
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

struct Statement::Empty : public Statement
{
    void accept(AST::Visitor &visitor) override{visitor.visit(*this);}
};

#endif //PASCAL_STATEMENT_H
