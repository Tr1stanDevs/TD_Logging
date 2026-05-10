#pragma once
#include <iostream>
#include "./colors.hpp"
#include "./flags.hpp"

namespace LogLib {

    inline void print_success(const char message[]) {
        std::cout << GREEN << message << RESET << std::endl;
    };

    inline void print_warning(const char message[]) {
        std::cout << YELLOW << message << RESET << std::endl;
    };
    inline void print_error(const char message[]) {
        std::cout << RED << message << RESET << std::endl;
    };
    


}
