
#include "TD_Logging.hpp"

int main() {
    TD_Logging::Settings |= PRINT_BOLD | PRINT_BLINKING | PRINT_TIME | LogLevel_ALL;
    TD_Logging::Init();
    //std::cout << LogLib::settings << std::endl;#

    //Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "lol");
    TD_Logging::print("%s %s\n",LogLevel_ERROR, "hi", "test");
    TD_Logging::print("%s %s\n",LogLevel_SUCCESS, "hi", "fdsaf");
    TD_Logging::print("%s %s\n",LogLevel_ERROR, "hi", "53425");
    TD_Logging::print("%s %s\n",LogLevel_SUCCESS, "hi", "543252");
    TD_Logging::print("%s %s\n",LogLevel_ERROR, "hi", "uztru");
    TD_Logging::print("%s %s\n",LogLevel_WARN, "hi", "jghfj");
    TD_Logging::print("%s %s\n",LogLevel_INFO, "hi", "hhhhhhhhhhhhhhhhhh");

    return 0;
}