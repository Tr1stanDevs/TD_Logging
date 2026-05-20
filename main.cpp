
#include <iostream>
#include "src/Chroma.hpp"
#include "src/flags.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    Chroma::settings |= PRINT_BOLD | PRINT_BLINKING;
    //std::cout << LogLib::settings << std::endl;

    #ifdef _WIN32 
    // set console mode to ansii
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //get output handle
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode); //get the current conole handle
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; //set the bits in DWMODE to activate ANSI/VT100
    SetConsoleMode(hOut, dwMode); // set the new mode
        

    Chroma::print_success("%s\n", "test");
    #else
    Chroma::print_success("%s %s\n", "hi", "lol");
    #endif

    std::cin.get();

}