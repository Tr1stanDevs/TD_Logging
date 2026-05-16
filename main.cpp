#include <iostream>
#include "src/LogLib.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32 
        LogLib::print_success("hi");
        #else
        LogLib::print_success((char*)"%s %s\n", "hi", "lol");
    #endif

}