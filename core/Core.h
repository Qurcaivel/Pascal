//
// Created by Inqognitoo on 30.09.2022.
//

#ifndef PASCAL_CORE_H
#define PASCAL_CORE_H

#include <string>

class Core
{
public:
    static void run_script(const std::string& script);
//    static void run_prompt();

    static void report(const std::string& message);
    static void error(const std::string& message);

private:
    static bool has_error;
    static void run(const std::string& source);
};

#endif //PASCAL_CORE_H
