#include <iostream>
#include "./src/colors.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32 
        std::cout << RED << "Windows\n" << RESET;
        #else
        std::cout << "Linux\n";
    #endif

    std::cin.get();
}