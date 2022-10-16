//
// Created by Inqognitoo on 06.10.2022.
//

#include <iostream>

#include "Printer.h"

void Printer::inc()
{
    prefix.push_back(' ');
    prefix.push_back(' ');
    prefix.push_back(' ');
    prefix.push_back(' ');
}

void Printer::dec()
{
    prefix.pop_back();
    prefix.pop_back();
    prefix.pop_back();
    prefix.pop_back();
}

void Printer::visit(Declaration::Program &program)
{
    std::cout << prefix << "program\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "name = " << program.m_name.lexeme() << "\n";
        program.m_block->accept(*this);
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Declaration::Block &block)
{
    std::cout << prefix << "block\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "declarations\n"
                  << prefix << "{\n";

        inc();
            for(auto declaration : block.m_declarations)
            {
                declaration->accept(*this);
            }
        dec();

        std::cout << prefix << "}\n";

        block.m_compound->accept(*this);
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Declaration::Procedure &procedure)
{
    std::cout << prefix << "procedure\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "name = " << procedure.m_name.lexeme() << "\n";

        std::cout << prefix << "params\n"
                  << prefix << "{\n";

        inc();
            for(auto param : procedure.m_params)
            {
                param->accept(*this);
            }

            procedure.m_block->accept(*this);
        dec();

        std::cout << prefix << "}\n";
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Declaration::Function &function)
{
    std::cout << prefix << "function\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "name = " << function.m_name.lexeme() << "\n"
                  << prefix << "type = " << function.m_type.lexeme() << "\n";

        std::cout << prefix << "params\n"
                  << prefix << "{\n";
        inc();
            for(auto param : function.m_params)
            {
                param->accept(*this);
            }

            function.m_block->accept(*this);
        dec();

        std::cout << prefix << "}\n";
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Declaration::Const &constant)
{
    std::cout << prefix << "const\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "name = " << constant.m_name.lexeme() << "\n";
        std::cout << prefix << "init = ";

        constant.m_expression->accept(*this);
        std::cout << "\n";
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Declaration::Var &var)
{
    std::cout << prefix << "var\n"
              << prefix << "{\n"
              << prefix << "\tname = " << var.m_name.lexeme() << "\n"
              << prefix << "\ttype = " << var.m_type.lexeme() << "\n"
              << prefix << "}\n";
}

void Printer::visit(Declaration::Param &param)
{
    std::cout << prefix << "var\n"
              << prefix << "{\n"
              << prefix << "\tname = " << param.m_name.lexeme() << "\n"
              << prefix << "\ttype = " << param.m_type.lexeme() << "\n"
              << prefix << "}\n";
}

void Printer::visit(Expression::Binary &binary)
{
    binary.m_left->accept(*this);
    std::cout << ' ' << binary.m_operation.lexeme() << ' ';
    binary.m_right->accept(*this);
}

void Printer::visit(Expression::Unary &unary)
{
    std::cout << unary.m_operation.lexeme();
    unary.m_expression->accept(*this);
}

void Printer::visit(Expression::Call &call)
{
    std::cout << call.m_name.lexeme() << "(";

    for(auto arg : call.m_args)
    {
        arg->accept(*this);
        if(arg != call.m_args.back()) std::cout << ", ";
    }

    std::cout << ")";
}

void Printer::visit(Expression::Variable &variable)
{
    std::cout << variable.m_name.lexeme();
}

void Printer::visit(Expression::Integer &integer)
{
    std::cout << integer.m_value;
}

void Printer::visit(Expression::Real &real)
{
    std::cout << real.m_value;
}

void Printer::visit(Expression::Boolean &boolean)
{
    std::cout << (boolean.m_value ? "true" : "false");
}

void Printer::visit(Expression::String &string)
{
    std::cout << string.m_value;
}

void Printer::visit(Statement::Compound &compound)
{
    std::cout << prefix << "compound\n"
              << prefix << "{\n";

    inc();
        for(auto statement : compound.m_statements)
        {
            statement->accept(*this);
        }
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Statement::Assign &assign)
{
    std::cout << prefix << "assign\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "name = " << assign.m_name.lexeme() << "\n"
                  << prefix << "expression = ";

        assign.m_expression->accept(*this);
        std::cout << "\n";
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Statement::Expr &expr)
{
    std::cout << prefix << "expr\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix;
        expr.m_expression->accept(*this);
        std::cout << "\n";
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Statement::Loop &loop)
{
    std::cout << prefix << "loop\n"
              << prefix << "{\n";

    inc();
        std::cout << "type = " << loop.m_type.lexeme() << "\n"
                  << prefix << "condition =  ";

        loop.m_condition->accept(*this);
        std::cout << "\n";

        loop.m_statement->accept(*this);
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Statement::For &loop)
{
    std::cout << prefix << "for\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "direction = " << loop.m_direction.lexeme() << "\n";

        loop.m_assign->accept(*this);

        std::cout << prefix << "expression = ";
        loop.m_expression->accept(*this);
        std::cout << "\n";

        loop.m_statement->accept(*this);
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Statement::If &flow)
{
    std::cout << prefix << "if\n"
              << prefix << "{\n";

    inc();
        std::cout << prefix << "condition = ";
        flow.m_condition->accept(*this);
        std::cout << "\n";

        std::cout << prefix << "1:\n";
        flow.m_if_branch->accept(*this);

        std::cout << prefix << "0:\n";
        flow.m_else_branch->accept(*this);
    dec();

    std::cout << prefix << "}\n";
}

void Printer::visit(Statement::Continue &control)
{
    std::cout << prefix << "continue\n";
}

void Printer::visit(Statement::Break &control)
{
    std::cout << prefix << "break\n";
}

void Printer::visit(Statement::Exit &control)
{
    std::cout << prefix << "exit\n";
}

void Printer::visit(Statement::Halt &control)
{
    std::cout << prefix << "halt\n";
}

void Printer::visit(Statement::Empty& empty){}