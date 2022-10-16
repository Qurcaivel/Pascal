//
// Created by Inqognitoo on 30.09.2022.
//

#ifndef PASCAL_ERROR_H
#define PASCAL_ERROR_H


#include <stdexcept>
#include <vector>

#include "Token.h"

class unexpected_token_error : public std::exception
{
public:
    unexpected_token_error(Token token) : m_token(token){}

    Token token() const
    {
        return m_token;
    }

private:
    Token m_token;
};

#endif //PASCAL_ERROR_H
