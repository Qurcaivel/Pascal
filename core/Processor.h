//
// Created by Inqognitoo on 01.10.2022.
//

#ifndef PASCAL_PROCESSOR_H
#define PASCAL_PROCESSOR_H

#include <functional>
#include <queue>

class Processor
{
public:
    typedef std::function<void(void)> process_t;
    typedef std::function<bool(void)> statement_t;

    Processor(statement_t statement);

    void post(process_t process);

    void run();

private:
    std::queue<process_t> m_processes;
    statement_t m_statement;
};

#endif //PASCAL_PROCESSOR_H
