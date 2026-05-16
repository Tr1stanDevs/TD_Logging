#pragma once
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include "./colors.hpp"
#include "./flags.hpp"



namespace LogLib {
    
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
