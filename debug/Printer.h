//
// Created by Inqognitoo on 06.10.2022.
//

#ifndef PASCAL_PRINTER_H
#define PASCAL_PRINTER_H

#include "Tree.h"

class Printer : public AST::Visitor
{
public:
    void visit(Declaration::Program &program) override;
    void visit(Declaration::Block &block) override;

    void visit(Expression::Binary &binary) override;
    void visit(Expression::Unary &unary) override;
    void visit(Expression::Call &call) override;

    void visit(Expression::Variable &variable) override;
    void visit(Expression::Integer &integer) override;
    void visit(Expression::Real &real) override;
    void visit(Expression::Boolean &boolean) override;
    void visit(Expression::String &string) override;

    void visit(Declaration::Procedure &procedure) override;
    void visit(Declaration::Function &function) override;
    void visit(Declaration::Const &constant) override;
    void visit(Declaration::Var &var) override;
    void visit(Declaration::Param &param) override;

    void visit(Statement::Compound &compound) override;
    void visit(Statement::Assign &assign) override;
    void visit(Statement::Expr &expr) override;

    void visit(Statement::Loop &loop) override;
    void visit(Statement::For &loop) override;
    void visit(Statement::If &flow) override;

    void visit(Statement::Continue &control) override;
    void visit(Statement::Break &control) override;
    void visit(Statement::Exit &control) override;
    void visit(Statement::Halt &control) override;

    void visit(Statement::Empty &empty) override;

private:
    std::string prefix;

    inline void inc();
    inline void dec();
};


#endif //PASCAL_PRINTER_H
