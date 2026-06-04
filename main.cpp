
#include <iostream>
#include "src/Chroma.hpp"

int main() {
    Chroma::Settings |= PRINT_BOLD | PRINT_BLINKING | PRINT_TIME | LogLevel_SUCCESS;
    Chroma::Init();
    //std::cout << LogLib::settings << std::endl;#

    //Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "lol");
    Chroma::print("%s %s\n",LogLevel_WARN, "hi", "fds");

    return 0;
}