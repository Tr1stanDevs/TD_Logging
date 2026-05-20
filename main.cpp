#include <iostream>
#include "src/Chroma.hpp"
#include "src/flags.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    Chroma::settings |= PRINT_BOLD | PRINT_TIME;
    //std::cout << LogLib::settings << std::endl;

    #ifdef _WIN32 
        Chroma::print_success("%s\n", "test");
        #else
        Chroma::print_success("%s %s\n", "hi", "lol");
    #endif

}