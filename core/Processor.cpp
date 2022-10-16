//
// Created by Inqognitoo on 01.10.2022.
//

#include <utility>

#include "Processor.h"

Processor::Processor(Processor::statement_t statement) : m_statement(std::move(statement)){}

void Processor::post(Processor::process_t process)
{
    m_processes.push(std::move(process));
}

void Processor::run()
{
    while(m_statement() && !m_processes.empty())
    {
        process_t process = m_processes.front();
        m_processes.pop();
        process();
    }
}
