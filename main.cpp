
#include "TD_Logging.hpp"

int main() {
    TD_Logging::Settings |= PRINT_BOLD | PRINT_TIME | LogLevel_ALL;
    TD_Logging::Init();
    //std::cout << LogLib::settings << std::endl;#

    //Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "lol");
    TD_Logging::print("%s %s\n",LogLevel_ERROR, "hi", "test");

    return 0;
}