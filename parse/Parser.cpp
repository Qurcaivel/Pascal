//
// Created by Inqognitoo on 09.10.2022.
//

#include <utility>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "Parser.h"
#include "Error.h"
#include "Core.h"

Parser::Parser(Tokens tokens)
{
    m_tokens = std::move(tokens);
    m_current = m_tokens.begin();
}

Token Parser::peek()
{
    return *m_current;
}

Token Parser::next()
{
    return *(m_current + 1);
}

Token Parser::prev()
{
    return *(m_current - 1);
}

Token Parser::consume()
{
    return *m_current++;
}

template <typename... Types>
Token Parser::require(Token::Type type1, Token::Type type2, Types ...types)
{
    if(match(type1, type2, types...))
    {
        return prev();
    }
    throw unexpected_token_error(peek());
}
Token Parser::require(Token::Type type1, Token::Type type2)
{
    if(match(type1, type2))
    {
        return prev();
    }
    throw unexpected_token_error(peek());
}
Token Parser::require(Token::Type type)
{
    if(match(type))
    {
        return prev();
    }
    throw unexpected_token_error(peek());
}

template <typename... Types>
bool Parser::match(Token::Type type1, Token::Type type2, Types ...types)
{
    return match(type1) || match(type2, types...);
}
bool Parser::match(Token::Type type1, Token::Type type2)
{
    return match(type1) || match(type2);
}
bool Parser::match(Token::Type type)
{
    if(m_current->is(type))
    {
        m_current++;
        return true;
    }
    return false;
}

// Parsing lists

Consts Parser::const_list()
{
    Consts consts;

    do{
        auto name = require(Token::Type::Identifier);
        require(Token::Type::Equal);
        auto expr = expression();

        consts.push_back(new Declaration::Const(name, expr));
    }
    while(match(Token::Type::Comma));

    return consts;
}

Vars Parser::var_list()
{
    Tokens names;
    Vars vars;

    do{
        auto name = require(Token::Type::Identifier);
        names.push_back(name);
    }
    while(match(Token::Type::Comma));

    require(Token::Type::Colon);

    auto type = consume();

    for(auto& name : names)
    {
        vars.push_back(new Declaration::Var(name, type));
    }

    return vars;
}

Params Parser::param_list()
{
    Tokens names;
    Params params;

    do{
        auto name = require(Token::Type::Identifier);
        names.push_back(name);
    }
    while(match(Token::Type::Comma));

    require(Token::Type::Colon);

    auto type = consume();

    for(auto& name : names)
    {
        params.push_back(new Declaration::Param(name, type));
    }

    return params;
}

Params Parser::param_formal_list()
{
    Params params;

    do{
        auto curr = param_list();
        params.insert(params.end(), curr.begin(), curr.end());
    }
    while(match(Token::Type::Semicolon));

    return params;
}

// Parsing declarations

Declarations Parser::declaration_part()
{
    Declarations decls;

    if(match(Token::Type::Const))
    {
        auto curr = const_list();
        decls.insert(decls.end(), curr.begin(), curr.end());
        require(Token::Type::Semicolon);
    }

    if(match(Token::Type::Var))
    {
        do{
            auto curr = var_list();
            decls.insert(decls.end(), curr.begin(), curr.end());
            require(Token::Type::Semicolon);
        }
        while(peek().is(Token::Type::Identifier));
    }

    while(match(Token::Type::Function, Token::Type::Procedure))
    {
        auto kind = prev();
        auto name = require(Token::Type::Identifier);

        Params params;

        if(match(Token::Type::OpenParen))
        {
            params = param_formal_list();
            require(Token::Type::CloseParen);
        }

        if(kind.is(Token::Type::Function))
        {
            auto type = consume();

            if(!type.is_type()){
                throw unexpected_token_error(type);
            }

            require(Token::Type::Semicolon);

            auto block = block_declaration();
            require(Token::Type::Semicolon);

            decls.push_back(new Declaration::Function(name, params, type, block));
        }
        else
        {
            require(Token::Type::Semicolon);

            auto block = block_declaration();
            require(Token::Type::Semicolon);

            decls.push_back(new Declaration::Procedure(name, params, block));
        }
    }

    return decls;
}

Declaration::Block *Parser::block_declaration()
{
    auto head = declaration_part();
    auto main = compound_statement();

    return new Declaration::Block(head, main);
}

Declaration::Program *Parser::program_declaration()
{
    require(Token::Type::Program);
    auto name = require(Token::Type::Identifier);
    require(Token::Type::Semicolon);

    auto block = block_declaration();
    require(Token::Type::Dot);

    return new Declaration::Program(name, block);
}

// Parsing statements

Statements Parser::statement_list()
{
    Statements statements;

    do{
        statements.push_back(statement());
    }
    while(match(Token::Type::Semicolon));

    return statements;
}

Statement *Parser::statement()
{
    switch(peek().type())
    {
        case Token::Type::Begin:    return compound_statement();

        case Token::Type::For:      return for_statement();
        case Token::Type::If:       return if_statement();
        case Token::Type::Repeat:
        case Token::Type::While:    return loop_statement();

        case Token::Type::Continue: return new Statement::Continue;
        case Token::Type::Break:    return new Statement::Break;
        case Token::Type::Exit:     return new Statement::Exit;
        case Token::Type::Halt:     return new Statement::Halt;

        default:
        {
            if(peek().is(Token::Type::Identifier) && next().is(Token::Type::Assign))
            {
                return assign_statement();
            }
            else
            {
                try{
                    return expr_statement();
                }
                catch(...){
                    return new Statement::Empty();
                }
            }
        }
    }
}

Statement::Compound *Parser::compound_statement()
{
    require(Token::Type::Begin);

    Statements statements;

    if(!match(Token::Type::End))
    {
        statements = statement_list();
    }

    require(Token::Type::End);

    return new Statement::Compound(statements);
}

Statement::Assign *Parser::assign_statement()
{
    auto name = require(Token::Type::Identifier);
    require(Token::Type::Assign);
    auto expr = expression();

    return new Statement::Assign(name, expr);
}

Statement::Expr *Parser::expr_statement()
{
    return new Statement::Expr(expression());
}

Statement::Loop *Parser::loop_statement()
{
    auto type = require(Token::Type::Repeat, Token::Type::While);
    Expression* condition;
    Statement* body;

    if(type.is(Token::Type::While))
    {
        condition = expression();
        body = statement();
    }
    else
    {
        body = statement();
        condition = expression();
    }

    return new Statement::Loop(type, condition, body);
}

Statement::For *Parser::for_statement()
{
    require(Token::Type::For);

    auto assign = assign_statement();
    auto direction = require(Token::Type::To, Token::Type::Downo);
    auto expr = expression();
    auto body = statement();

    return new Statement::For(assign, direction, expr, body);
}

Statement::If *Parser::if_statement()
{
    require(Token::Type::If);
    auto condition = expression();
    require(Token::Type::Then);

    auto if_branch = statement();
    auto else_branch = match(Token::Type::Else) ? statement() : nullptr;

    return new Statement::If(condition, if_branch, else_branch);
}

// Parsing expression

Expression* Parser::expression()
{
    return equality();
}

Expression* Parser::equality()
{
    auto expr = comparison();

    while(match(Token::Type::Not, Token::Type::NotEqual))
    {
        auto operation = prev();
        auto right = comparison();
        expr = new Expression::Binary(expr, operation, right);
    }

    return expr;
}

Expression *Parser::comparison()
{
    auto* expr = term();

    while(match(Token::Type::Less, Token::Type::LessEqual, Token::Type::Greater, Token::Type::GreaterEqual))
    {
        auto operation = prev();
        auto right = term();
        expr = new Expression::Binary(expr, operation, right);
    }

    return expr;
}

Expression *Parser::term()
{
    auto expr = factor();

    while(match(Token::Type::Plus, Token::Type::Minus, Token::Type::Or, Token::Type::Xor))
    {
        auto operation = prev();
        auto right = factor();
        expr = new Expression::Binary(expr, operation, right);
    }

    return expr;
}

Expression *Parser::factor()
{
    auto expr = unary();

    while(match(Token::Type::Asterisk, Token::Type::Slash, Token::Type::And, Token::Type::Div, Token::Type::Mod))
    {
        auto operation = prev();
        auto right = unary();
        expr = new Expression::Binary(expr, operation, right);
    }

    return expr;
}

Expression *Parser::unary()
{
    if(match(Token::Type::Not, Token::Type::Plus, Token::Type::Minus))
    {
        auto operation = prev();
        auto right = primary();
        return new Expression::Unary(operation, right);
    }

    return primary();
}

Expression *Parser::primary()
{
    auto view = peek().lexeme();

    if(match(Token::Type::SLiteral)) // String
    {
        return new Expression::String(view);
    }
    if(match(Token::Type::ILiteral)) // Integer
    {
        return new Expression::Integer(std::stoi(view.data()));
    }
    if(match(Token::Type::FLiteral)) // Floating
    {
        return new Expression::Real(std::stof(view.data()));
    }
    if(match(Token::Type::True)) // True
    {
        return new Expression::Boolean(true);
    }
    if(match(Token::Type::False)) // False
    {
        return new Expression::Boolean(false);
    }

    if(match(Token::Type::Identifier)) // Variable
    {
        auto name = prev();

        if(match(Token::Type::OpenParen)) // Function call (and procedure 'statement')
        {
            std::vector<Expression*> args;
            do{
                args.push_back(expression());
            }
            while(match(Token::Type::Comma));

            require(Token::Type::CloseParen);

            return new Expression::Call(name, args);
        }

        return new Expression::Variable(name);
    }

    if(match(Token::Type::OpenParen)) // Grouping expression
    {
        auto expr = expression();

        require(Token::Type::CloseParen);

        return expr;
    }

    throw unexpected_token_error(peek());
}

// Main parse

Program *Parser::parse()
{
    try {
        return program_declaration();
    }
    catch(const unexpected_token_error& e)
    {
        auto token = e.token();
        Core::error((std::stringstream() << "unexpected at" << std::setw(2) << token.row() << ":" << std::setw(2) << token.col()).str());
    }

    return nullptr;
}