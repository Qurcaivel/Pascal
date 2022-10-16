cmake_minimum_required(VERSION 3.24)
project(Pascal)

set(CMAKE_CXX_STANDARD 17)

# main target

add_executable(Pascal
        main.cpp
        core/Core.cpp
        core/Core.h
        core/Processor.cpp
        core/Processor.h
        lex/Token.cpp
        lex/Token.h
        lex/Source.cpp
        lex/Source.h
        lex/Lexer.cpp
        lex/Lexer.h
        venv/Interpreter.cpp
        venv/Interpreter.h
        optimize/Optimizer.cpp
        optimize/Optimizer.h
        error/Error.cpp
        error/Error.h
        debug/Printer.cpp
        debug/Printer.h
        parse/Parser.cpp
        parse/Parser.h
        resolve/Resolver.cpp
        resolve/Resolver.h
        tree/Tree.h
        tree/Declaration.h
        tree/Expression.h
        tree/Statement.h)

target_include_directories(Pascal PRIVATE core lex parse resolve test tree venv debug error)