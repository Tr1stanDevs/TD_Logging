
#include "TD_Logging.hpp"

int main() {
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_BOLD | TD_Logging::LoggingFlags::PRINT_TIME | TD_Logging::LoggingLevels::LogLevel_ALL;
    TD_Logging::Init();
    //std::cout << LogLib::settings << std::endl;#

    //Chroma::print("%s %s\n",LogLevel_ERROR, "hi", "lol");
    TD_Logging::print("%s %s\n",TD_Logging::LoggingLevels::LogLevel_ERROR, "hi", "test");

    return 0;
}