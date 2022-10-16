//
// Created by Inqognitoo on 30.09.2022.
//

#ifndef PASCAL_TOKEN_H
#define PASCAL_TOKEN_H


#include <cstddef>
#include <string>
#include <string_view>

class Token
{
public:
    enum class Type
    {
        Identifier, ILiteral, FLiteral, True, False, SLiteral,                          // Literal // todo: change names
        Integer, Real, Boolean, String,                                                 // Keyword +
        Program,                                                                        // Keyword +
        Begin,                                                                          // Keyword +
        End,                                                                            // Keyword +
        Const, Var, Procedure, Function,                                                // Keyword +
        If, Then, Else,                                                                 // Keyword +
        For, While, Repeat, Until, To, Downo, Do,                                       // Keyword +
        Break, Continue, Exit, Halt,                                                    // Keyword // todo: implement statements
        OpenParen, CloseParen, OpenSquare, CloseSquare,                                 // Keyword +
        Dot, Comma, Colon, Semicolon,                                                   // Keyword +
        Plus, Minus, Asterisk, Slash,                                                   // Keyword +
        Assign, Equal, NotEqual, Less, LessEqual, Greater, GreaterEqual,                // Keyword +
        Not, And, Or, Xor, Div, Mod,                                                    // Keyword +
        Array, Of,                                                                      // Keyword -
        Eof,                                                                            // Literal +
        Unexpected,                                                                     // Literal +
    };

    Token(Type type, std::size_t row, std::size_t col);
    Token(Type type, std::size_t row, std::size_t col, const char* begin, std::size_t length);
    Token(Type type, std::size_t row, std::size_t col, const char* begin, const char* end);

    template <typename... Ts>
    bool is(Type type1, Type type2, Ts... types) const;
    bool is(Type type1, Type type2) const;
    bool is(Type type) const;

    bool is_type() const;
    bool is_literal() const;

    Type type() const;
    std::string_view lexeme() const;
    std::size_t row() const;
    std::size_t col() const;

    static std::string to_string(Type type);
    static Type from_string(const std::string_view& view);

private:
    Type m_type;
    std::string_view m_lexeme;

    std::size_t m_row;
    std::size_t m_col;
};

#endif //PASCAL_TOKEN_H
