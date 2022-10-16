//
// Created by Inqognitoo on 30.09.2022.
//

#ifndef PASCAL_LEXER_H
#define PASCAL_LEXER_H

#include "Token.h"
#include "Source.h"

typedef std::vector<Token> Tokens;

class Lexer
{
public:
    Lexer(Source& source);

    Tokens tokenize();

private:
    Source& m_source;

    const char* m_temp_ptr;
    std::size_t m_temp_row;
    std::size_t m_temp_col;

    Token next();
    Token read(Token::Type type);

    void skip_row_comment();
    void skip_col_comment();

    Token read_number();
    Token read_unique();
    Token read_string();

    inline bool match(char expected);
    inline char current();
    inline char advance();
};

namespace Character
{
    inline bool is_digit(char c);
    inline bool is_alpha(char c);
    inline bool is_ident(char c);

    constexpr char Wsp = ' ';
    constexpr char Tab = '\t';
    constexpr char Car = '\r';
    constexpr char New = '\n';
    constexpr char Eof = '\0';
}


#endif //PASCAL_LEXER_H
