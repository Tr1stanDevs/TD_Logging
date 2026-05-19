#pragma once
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include "./colors.hpp"
#include "./flags.hpp"

//1mb stacksize windows
//8mb stacksize linux
//https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html


namespace LogLib {
    inline int settings = 0;
    
    template <typename ... Types>
    inline void print_success(char format[], Types... args) {
        char buffer[256];
        std::strcpy(buffer, COLORS::GREEN);
        std::strcat(buffer, format);
        std::strcat(buffer, COLORS::RESET);

        printf(buffer, args...);
    };

    template <typename ... Types>
    inline void print_warning(char format[], Types... args) {
        char buffer[256];
        std::strcpy(buffer, COLORS::YELLOW);
        std::strcat(buffer, format);
        std::strcat(buffer, COLORS::RESET);

        printf(buffer, args...);
    };

    template <typename ... Types>
    inline void print_error(char format[], Types... args) {
        char buffer[256];
        std::strcpy(buffer, COLORS::RED);
        std::strcat(buffer, format);
        std::strcat(buffer, COLORS::RESET);

        printf(buffer, args...);
    };

    


}
