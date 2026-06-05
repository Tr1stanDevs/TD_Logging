
#include <iostream>
#include <numbers>
#include "src/Chroma.hpp"

int main() {
    Chroma::Settings |= PRINT_BOLD | PRINT_BLINKING | PRINT_TIME | LogLevel_ALL;
    Chroma::Init();
    //std::cout << LogLib::settings << std::endl;#

    //Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "lol");
    Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "test");
    Chroma::print("%s %s\n",LogLevel_SUCCESS, "hi", "fdsaf");
    Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "53425");
    Chroma::print("%s %s\n",LogLevel_SUCCESS, "hi", "543252");
    Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "uztru");
    Chroma::print("%s %s\n",LogLevel_WARN, "hi", "jghfj");
    Chroma::print("%s %s\n",LogLevel_INFO, "hi", "hhhhhhhhhhhhhhhhhh");

    return 0;
}