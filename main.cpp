#include "Core.h"

int main(int argc, char** argv)
{
    //Core::run_script("source.txt");

    /*if(argc == 1){
        Core::run_prompt();
    }
    else*/
    if(argc == 2){
        Core::run_script(std::string(argv[1]));
    }
    else{
        Core::error("usage: pascal [-script]");
        std::exit(64);
    }
}