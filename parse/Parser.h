//
// Created by Inqognitoo on 09.10.2022.
//

#ifndef PASCAL_PARSER_H
#define PASCAL_PARSER_H

#include "Lexer.h"
#include "Tree.h"

class Parser
{
public:
    Parser(Tokens tokens);
    Program* parse();

private:
    Tokens m_tokens;
    Tokens::iterator m_current;

    Token peek();
    Token next();
    Token prev();
    Token consume();

    template <typename... Types>
    Token require(Token::Type type1, Token::Type type2, Types... types);
    Token require(Token::Type type1, Token::Type type2);
    Token require(Token::Type type);

    template <typename... Types>
    bool match(Token::Type type1, Token::Type type2, Types... types);
    bool match(Token::Type type1, Token::Type type2);
    bool match(Token::Type type);

    // Parsing

    Consts const_list();
    Vars var_list();
    Params param_list();            // todo: var and param is similar
    Params param_formal_list();     // todo: var and param

    Declarations declaration_part();
    Statements statement_list();

    Declaration::Program* program_declaration();
    Declaration::Block* block_declaration();

    Statement::Compound* compound_statement();
    Statement::Assign* assign_statement();
    Statement::Expr* expr_statement();

    Statement::Loop* loop_statement();
    Statement::For* for_statement();
    Statement::If* if_statement();

    Statement* statement();

    Expression* expression();
    Expression* equality();
    Expression* comparison();
    Expression* term();
    Expression* factor();
    Expression* unary();
    Expression* primary();
};

#endif //PASCAL_PARSER_H
