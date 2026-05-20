
#include <iostream>
#include "src/Chroma.hpp"
#include "src/flags.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    Chroma::Settings |= PRINT_BOLD | PRINT_BLINKING;
    Chroma::Init();
    //std::cout << LogLib::settings << std::endl;#

    Chroma::print_success("%s %s\n", "hi", "lol");

    std::cin.get();

}