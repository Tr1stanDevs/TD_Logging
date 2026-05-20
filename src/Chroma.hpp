#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include "./colors.hpp"
#include "./flags.hpp"

//1mb stacksize windows
//8mb stacksize linux
//https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html


namespace Chroma {
    inline int settings = 0;

    inline char* add_setting(char* format) {
        uint64_t start = (uint64_t)format;

        if (settings&PRINT_BOLD) { //code ;1 (1<<0)
            while ((*format) != 0x6D) format++;

            *(format) = 0x3B;
            *(format+1) = 0x31;
            *(format+2) = 0x6D;
        }

        if (settings&PRINT_BLINKING) { //code ;1 (1<<0)
            while ((*format) != 0x6D) format++;

            *(format) = 0x3B;
            *(format+1) = 0x35;
            *(format+2) = 0x6D;
        }




        return (char*)start;
    };
    
    
    template <typename ... Types>
    inline void print_success(const char* format, Types... args) {
        char buffer[256];
        std::strcpy(buffer, add_setting(COLORS::GREEN));
        std::strcat(buffer, format);
        std::strcat(buffer, COLORS::RESET);

        printf(buffer, args...);
    };

    template <typename ... Types>
    inline void print_warning(const char* format, Types... args) {
        char buffer[256];
        std::strcpy(buffer, add_setting(COLORS::YELLOW));
        std::strcat(buffer, format);
        std::strcat(buffer, COLORS::RESET);

        printf(buffer, args...);
    };

    template <typename ... Types>
    inline void print_error(const char* format, Types... args) {
        char buffer[256];
        std::strcpy(buffer, add_setting(COLORS::RED));
        std::strcat(buffer, format);
        std::strcat(buffer, COLORS::RESET);

        printf(buffer, args...);
    };

    


}
