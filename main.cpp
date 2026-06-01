
#include <iostream>
#include "src/Chroma.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    Chroma::Settings |= PRINT_BOLD | PRINT_BLINKING | PRINT_TIME;
    Chroma::Init();
    //std::cout << LogLib::settings << std::endl;#

    Chroma::print_success("%s %s\n", "hi", "lol");
    std::cin.get();

    return 0;
}