#pragma once
#include <iostream>
#include "./colors.hpp"
#include "./flags.hpp"

namespace LogLib {

    inline void print_success(const char message[]) {
        std::cout << LogLib_COLORS::GREEN << message << LogLib_COLORS::RESET << std::endl;
    };

    inline void print_warning(const char message[]) {
        std::cout << LogLib_COLORS::YELLOW << message << LogLib_COLORS::RESET << std::endl;
    };
    inline void print_error(const char message[]) {
        std::cout << LogLib_COLORS::RED << message << LogLib_COLORS::RESET << std::endl;
    };
    


}
