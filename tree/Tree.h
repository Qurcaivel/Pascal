//
// Created by Inqognitoo on 10.10.2022.
//

#ifndef PASCAL_TREE_H
#define PASCAL_TREE_H

#include <vector>

struct AST
{
    struct Visitor;
    virtual void accept(Visitor& visitor) = 0;
};

// Declarations

struct Declaration : public AST
{
    struct Program;
    struct Block;

    struct Procedure;
    struct Function;

    struct Const;
    struct Var;
    struct Param;
};

// Expressions

struct Expression : public AST
{
    struct Binary;
    struct Unary;
    struct Call;

    struct Variable;

    struct Integer;
    struct Real;
    struct Boolean;
    struct String;
};

// Statements

struct Statement : public AST
{
    struct Compound;
    struct Assign;
    struct Expr;

    struct Loop;
    struct For;
    struct If;

    struct Continue;
    struct Break;
    struct Exit;
    struct Halt;

    struct Empty;
};

// Visitor

struct AST::Visitor
{
    virtual void visit(Declaration::Program& program) = 0;
    virtual void visit(Declaration::Block& block) = 0;

    virtual void visit(Expression::Binary& binary) = 0;
    virtual void visit(Expression::Unary& unary) = 0;
    virtual void visit(Expression::Call& call) = 0;

    virtual void visit(Expression::Variable& variable) = 0;

    virtual void visit(Expression::Integer& integer) = 0;
    virtual void visit(Expression::Real& real) = 0;
    virtual void visit(Expression::Boolean& boolean) = 0;
    virtual void visit(Expression::String& string) = 0;

    virtual void visit(Declaration::Procedure& procedure) = 0;
    virtual void visit(Declaration::Function& function) = 0;

    virtual void visit(Declaration::Const& constant) = 0;
    virtual void visit(Declaration::Var& var) = 0;
    virtual void visit(Declaration::Param& param) = 0;

    virtual void visit(Statement::Compound& compound) = 0;
    virtual void visit(Statement::Assign& assign) = 0;
    virtual void visit(Statement::Expr& expr) = 0;

    virtual void visit(Statement::Loop& loop) = 0;
    virtual void visit(Statement::For& loop) = 0;
    virtual void visit(Statement::If& flow) = 0;

    virtual void visit(Statement::Continue& control) = 0;
    virtual void visit(Statement::Break& control) = 0;
    virtual void visit(Statement::Exit& control) = 0;
    virtual void visit(Statement::Halt& control) = 0;

    virtual void visit(Statement::Empty& empty) = 0;
};

// Shortcuts and aliases

using Program = Declaration::Program;
using Block = Declaration::Block;

typedef std::vector<Declaration*> Declarations;
typedef std::vector<Expression*> Expressions;
typedef std::vector<Statement*> Statements;

typedef std::vector<Declaration::Param*> Params;
typedef std::vector<Declaration::Const*> Consts;
typedef std::vector<Declaration::Var*> Vars;

#include "Declaration.h"
#include "Expression.h"
#include "Statement.h"


#endif //PASCAL_TREE_H
