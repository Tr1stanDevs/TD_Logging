
#include <iostream>
#include "src/Chroma.hpp"

int main() {
    Chroma::Settings |= PRINT_BOLD | PRINT_BLINKING | PRINT_TIME;
    Chroma::Init();
    //std::cout << LogLib::settings << std::endl;#

    Chroma::print_success("%s %s\n", "hi", "lol");
    std::cin.get();

    return 0;
}