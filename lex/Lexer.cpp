//
// Created by Inqognitoo on 30.09.2022.
//

#include <stdexcept>
#include "Lexer.h"

// Character

bool Character::is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

bool Character::is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Character::is_ident(char c)
{
    return is_digit(c) || is_alpha(c) || (c == '_');
}

// Lexer

using namespace Character;

Lexer::Lexer(Source &source) : m_source(source)
{
    m_temp_ptr = nullptr;
    m_temp_row = 1;
    m_temp_col = 1;
}

char Lexer::current()
{
    return m_source.current();
}

char Lexer::advance()
{
    return m_source.advance();
}

bool Lexer::match(char expected)
{
    if(m_source.current() == expected)
    {
        m_source.advance();
        return true;
    }
    return false;
}

Token Lexer::read(Token::Type type)
{
    return {type,
            m_temp_row,
            m_temp_col,
            m_temp_ptr,
            m_source.ptr()};
}

Token Lexer::next()
{
    while(true)
    {
        m_temp_ptr = m_source.ptr();
        m_temp_row = m_source.row();
        m_temp_col = m_source.col();

        char current = advance();

        switch(current)
        {
            case Wsp:
            case Tab:
            case Car:
            case New: break;

            case Eof: return read(Token::Type::Eof);

            case '(': return read(Token::Type::OpenParen);
            case ')': return read(Token::Type::CloseParen);

            case '[': return read(Token::Type::OpenSquare);
            case ']': return read(Token::Type::CloseSquare);

            case '+': return read(Token::Type::Plus);
            case '-': return read(Token::Type::Minus);
            case '*': return read(Token::Type::Asterisk);
            case '=': return read(Token::Type::Equal);

            case ':': return read(match('=') ? Token::Type::Assign : Token::Type::Colon);
            case '>': return read(match('=') ? Token::Type::GreaterEqual : Token::Type::Greater);
            case '<': return read(match('=') ? Token::Type::LessEqual : (match('>') ? Token::Type::NotEqual : Token::Type::Less));

            case '.': return read(Token::Type::Dot);
            case ',': return read(Token::Type::Comma);
            case ';': return read(Token::Type::Semicolon);

            case '"': return read_string(); // todo: change to '

            case '/': if(match('/'))
                      {
                          skip_row_comment();
                          break;
                      }
                      return read(Token::Type::Slash);

            case '{': skip_col_comment();
                      break;

            default:  if(is_alpha(current)) return read_unique();
                      if(is_digit(current)) return read_number();

                      return read(Token::Type::Unexpected); // todo: throw an exception less returning special type
        }
    }
}

void Lexer::skip_row_comment()
{
    while(!(match(New) || match(Eof)))
    {
        advance();
    }
}

void Lexer::skip_col_comment()
{
    while(!match('}'))
    {
        if(current() == Eof)
        {
            throw std::runtime_error("syntax error: unterminated multiline comment");
        }
        advance();
    }
}

Token Lexer::read_number()
{
    while(is_digit(current()))
    {
        advance();
    }
    if(match('.'))
    {
        while(is_digit(current()))
        {
            advance();
        }
        return read(Token::Type::FLiteral);
    }
    return read(Token::Type::ILiteral);
}

Token Lexer::read_string()
{
    while(!match('"')) // todo: change to '
    {
        if(current() == Eof)
        {
            throw std::runtime_error("syntax error: unexpected string literal");
        }
        advance();
    }

    return {Token::Type::SLiteral,
            m_temp_row,
            m_temp_col,
            m_temp_ptr + 1,
            m_source.ptr() - 1};
}

Token Lexer::read_unique()
{
    while(is_ident(current()))
    {
        advance();
    }

    std::string_view view(m_temp_ptr, std::distance(m_temp_ptr, m_source.ptr()));
    return read(Token::from_string(view));
}

Tokens Lexer::tokenize()
{
    Tokens tokens;

    while(true)
    {
        auto token = next();
        tokens.push_back(token);

        if(token.is(Token::Type::Eof))
        {
            break;
        }
    }

    // todo: throw errors to core

    return tokens;
}
