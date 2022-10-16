//
// Created by Inqognitoo on 30.09.2022.
//

#include "Source.h"

Source::Source(const char *begin)
{
    m_ptr = begin;
    m_row = 1;
    m_col = 1;
}

char Source::current()
{
    return *m_ptr;
}

char Source::advance()
{
    if(*m_ptr)
    {
        m_col++;

        if(*m_ptr == (char) 10)
        {
            m_col=1;
            m_row++;
            m_rows.push_back(m_ptr + 1);
        }

        return *m_ptr++;
    }

    return (char) 0;
}

const char *Source::ptr() const
{
    return m_ptr;
}

std::size_t Source::row() const
{
    return m_row;
}

std::size_t Source::col() const
{
    return m_col;
}

const char *Source::row_by_index(std::size_t index) const
{
    return m_rows.at(index);
}