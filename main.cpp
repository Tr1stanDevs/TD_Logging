
#include <iostream>
#include "src/Chroma.hpp"
#include "src/colors.hpp"
#include "src/flags.hpp"

#ifdef _WIN32 
#include <windows.h>
#endif

int main() {
    Chroma::Settings |= PRINT_BOLD | PRINT_BLINKING;
    Chroma::Init();
    //std::cout << LogLib::settings << std::endl;#

    Chroma::print_success("%s %s\n", "hi", "lol");
    Chroma::remove_setting(PRINT_BOLD);
    Chroma::remove_setting(PRINT_BLINKING);
    Chroma::print_color("%s\n", COLORS::BLUE, "hi");

    std::cin.get();

}