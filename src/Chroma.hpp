#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include "./colors.hpp"
#include "./flags.hpp"

#ifdef _WIN32 
#include <Windows.h>
#endif
//1mb stacksize windows
//8mb stacksize linux
//https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html


namespace Chroma {
    inline int Settings = 0;

    inline void Init() {
    #ifdef _WIN32 
    // set console mode to ansii
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //get output handle
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode); //get the current conole handle
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; //set the bits in DWMODE to activate ANSI/VT100
    SetConsoleMode(hOut, dwMode); // set the new mode
    #endif
    }

    inline char* add_setting(char* format) {
        uint64_t color_code_base_address = reinterpret_cast<uint64_t>(format);

        if (Settings&PRINT_BOLD) { //code ;1 (1<<0)
            while ((*format) != 0x6D) format++;

            *(format) = 0x3B;
            *(format+1) = 0x31;
            *(format+2) = 0x6D;
        }

        if (Settings&PRINT_BLINKING) { //code ;1 (1<<0)
            while ((*format) != 0x6D) format++;

            *(format) = 0x3B;
            *(format+1) = 0x35;
            *(format+2) = 0x6D;
        }

        return (char*)color_code_base_address;
    };

    inline void remove_setting(int settings_to_remove, ...) {
        if (Settings&settings_to_remove) {
            Settings = Settings & ~(settings_to_remove); 
        }
    }
    
    
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

    template <typename ... Types>
    inline void print_color(const char* format, char* color, Types... args) {
        char buffer[256];
        std::strcpy(buffer, add_setting(color));
        std::strcat(buffer, format);
        std::strcat(buffer, COLORS::RESET);

        printf(buffer, args...);
    }

    


}
