#include <iostream>
#include "src/LogLib.hpp"
#include "src/flags.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    LogLib::settings |= PRINT_BOLD | PRINT_TIME;
    std::cout << LogLib::settings << std::endl;
    
    #ifdef _WIN32 
        LogLib::print_success("hi");
        #else
        LogLib::print_success((char*)"%s %s\n", "hi", "lol");
    #endif

}