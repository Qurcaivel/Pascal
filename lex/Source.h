//
// Created by Inqognitoo on 30.09.2022.
//

#ifndef PASCAL_SOURCE_H
#define PASCAL_SOURCE_H


#include <cstddef>
#include <vector>

class Source
{
public:
    Source(const char* begin);

    char current();
    char advance();

    const char* ptr() const;
    std::size_t row() const;
    std::size_t col() const;

    const char* row_by_index(std::size_t index) const;

private:
    const char* m_ptr;
    std::size_t m_row;
    std::size_t m_col;

    std::vector<const char*> m_rows; // to store newlines
};


#endif //PASCAL_SOURCE_H
