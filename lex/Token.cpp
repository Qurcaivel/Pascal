//
// Created by Inqognitoo on 30.09.2022.
//

#include <unordered_map>

#include "Token.h"

Token::Token(Token::Type type, std::size_t row, std::size_t col)
{
    m_type = type;
    m_row = row;
    m_col = col;
}

Token::Token(Token::Type type, std::size_t row, std::size_t col, const char *begin, std::size_t length)
{
    m_type = type;
    m_row = row;
    m_col = col;
    m_lexeme = std::string_view(begin, length);
}

Token::Token(Token::Type type, std::size_t row, std::size_t col, const char *begin, const char *end)
{
    m_type = type;
    m_row = row;
    m_col = col;
    m_lexeme = std::string_view(begin, std::distance(begin, end));
}

template <typename... Ts>
bool Token::is(Token::Type type1, Token::Type type2, Ts ...types) const
{
    return is(type1) || is(type2, types...);
}

bool Token::is(Token::Type type1, Token::Type type2) const
{
    return is(type1) || is(type2);
}

bool Token::is(Token::Type type) const
{
    return m_type == type;
}

bool Token::is_type() const
{
    return is(Type::Integer, Type::Real, Type::Boolean, Type::String);
}

bool Token::is_literal() const
{
    return is(Type::ILiteral, Type::FLiteral, Type::True, Type::False, Type::SLiteral);
}

Token::Type Token::type() const
{
    return m_type;
}

std::string_view Token::lexeme() const
{
    return m_lexeme;
}

std::size_t Token::row() const
{
    return m_row;
}

std::size_t Token::col() const
{
    return m_col;
}

std::string Token::to_string(Token::Type type)
{
    const static char* const names[]
    {
        "Identifier", "ILiteral", "FLiteral", "True", "False", "SLiteral",
        "Integer", "Real", "Boolean", "String",
        "Program",
        "Begin",
        "End",
        "Const", "Var", "Procedure", "Function",
        "If", "Then", "Else",
        "For", "While", "Repeat", "Until", "To", "Downto", "Do",
        "Break", "Continue", "Exit", "Halt",
        "OpenParen", "CloseParen", "OpenSquare", "CloseSquare",
        "Dot", "Comma", "Colon", "Semicolon",
        "Plus", "Minus", "Asterisk", "Slash",
        "Assign", "Equal", "NotEqual", "Less", "LessEqual", "Greater", "GreaterEqual",
        "Not", "And", "Or", "Xor", "Div", "Mod",
        "Array", "Of",
        "Eof",
        "Unexpected",
    };

    return {names[static_cast<int>(type)]};
}

Token::Type Token::from_string(const std::string_view &view)
{
    const static std::unordered_map<std::string_view, Token::Type> ids
    {
        {"true", Type::True}, {"false", Type::False},
        {"integer", Type::Integer}, {"real", Type::Real}, {"boolean",Type::Boolean}, {"string", Type::String},
        {"program", Type::Program},
        {"begin", Type::Begin},
        {"end", Type::End},
        {"const", Type::Const}, {"var", Type::Var}, {"procedure", Type::Procedure}, {"function", Type::Function},
        {"if", Type::If}, {"then", Type::Then}, {"else", Type::Else},
        {"for", Type::For}, {"while", Type::While}, {"repeat", Type::Repeat}, {"until", Type::Until}, {"to", Type::To}, {"downto", Type::Downo}, {"Do", Type::Do},
        {"break", Type::Break}, {"continue", Type::Continue}, {"exit", Type::Exit}, {"halt", Type::Halt},
        {"not", Type::Not}, {"and", Type::And}, {"or", Type::Or}, {"xor", Type::Xor}, {"div", Type::Div}, {"mod", Type::Mod},
        {"array", Type::Array}, {"of", Type::Of},
    };

    auto it = ids.find(view);

    return (it == ids.end() ? Type::Identifier : it->second);
}