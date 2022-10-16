//
// Created by Inqognitoo on 30.09.2022.
//

#include "Core.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Processor.h"
#include "Lexer.h"
#include "Parser.h"
#include "Printer.h"

constexpr const char* prompt = ">>> ";

bool Core::has_error = false;

void Core::report(const std::string &message)
{
    std::cerr << message << std::endl;
}

void Core::error(const std::string &message)
{
    report(message);
    has_error = true;
}

void Core::run_script(const std::string &script)
{
    std::ifstream stream(script);

    if(!stream.is_open())
    {
        std::cerr << "error: unable to lead '" << script << "' script" << std::endl;
        std::exit(64);
    }

    std::string source((std::istreambuf_iterator<char>(stream)),
                       std::istreambuf_iterator<char>());

    run(source);
}

//void Core::run_prompt()
//{
//    while(std::cin.good())
//    {
//        std::string source;
//
//        std::cout << prompt;
//        std::getline(std::cin, source);
//
//        run(source);
//        has_error = false;
//    }
//}

// Run

inline void debug_print_tokens(const Tokens& tokens)
{
    for(auto token : tokens)
    {
        std::cout << '{'
                  << std::setw(2) << token.row() + 1
                  << ':'
                  << std::setw(2) << token.col() + 1
                  << ' '
                  << '|'
                  << ' '
                  << std::setw(14) << Token::to_string(token.type())
                  << ' '
                  << '|'
                  << ' '
                  << std::setw(14) << token.lexeme()
                  << ' '
                  << '}'
                  << std::endl;
    }
}

void Core::run(const std::string &source)
{
    Processor processor([]{ return not has_error; });

    Source stream(source.begin().base());
    Tokens tokens;
    Program* program;

    processor.post([&]
    {;
        Lexer lexer(stream);
        tokens = lexer.tokenize();
    });

    processor.post([&]
    {
        Parser parser(tokens);
        program = parser.parse();
    });

    processor.post([&]
    {
        Printer printer;
        printer.visit(*program);
    });

    processor.run();
}