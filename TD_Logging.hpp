#pragma once
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <string.h>

#define TD_Logging_COLOR_BUFFER_SIZE 32

#ifdef _WIN32
#include <Windows.h>
#endif
// 1mb stacksize windows
// 8mb stacksize linux
// https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html

namespace TD_Logging {
inline size_t Settings = 0;

inline void Init() {
#ifdef _WIN32
  // set console mode to ansii
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // get output handle
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);                // get the current conole handle
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // set the bits in DWMODE to
                                                // activate ANSI/VT100
  SetConsoleMode(hOut, dwMode);                 // set the new mode
#endif
}

namespace LoggingFlags {
  constexpr size_t PRINT_BOLD     = (1 << 0);  // bit 1
  constexpr size_t PRINT_TIME     = (1 << 1);  // bit 2
  constexpr size_t PRINT_FILE     = (1 << 2);  // bit 3
  constexpr size_t PRINT_BLINKING = (1 << 3);  // bit 4
  constexpr size_t PRINT_PREFIX   = (1 << 4);  // bit 5
}

namespace LoggingLevels {
  constexpr size_t LogLevel_INFO    = (1 << 20);
  constexpr size_t LogLevel_SUCCESS = (1 << 21);
  constexpr size_t LogLevel_WARN    = (1 << 22);
  constexpr size_t LogLevel_ERROR   = (1 << 23);
  constexpr size_t LogLevel_FAIL    = (1 << 24);
  constexpr size_t LogLevel_ALL     = (1 << 25);
}

namespace LoggingColors {
constexpr char RESET[TD_Logging_COLOR_BUFFER_SIZE] = "\033[0m";
constexpr char BLACK[TD_Logging_COLOR_BUFFER_SIZE] = "\033[30m";              /* Black */
constexpr char RED[TD_Logging_COLOR_BUFFER_SIZE] = "\033[31m";                /* Red */
constexpr char GREEN[TD_Logging_COLOR_BUFFER_SIZE] = "\033[32m";              /* Green */
constexpr char YELLOW[TD_Logging_COLOR_BUFFER_SIZE] = "\033[33m";             /* Yellow */
constexpr char BLUE[TD_Logging_COLOR_BUFFER_SIZE] = "\033[34m";               /* Blue */
constexpr char MAGENTA[TD_Logging_COLOR_BUFFER_SIZE] = "\033[35m";            /* Magenta */
constexpr char CYAN[TD_Logging_COLOR_BUFFER_SIZE] = "\033[36m";               /* Cyan */
constexpr char WHITE[TD_Logging_COLOR_BUFFER_SIZE] = "\033[37m";              /* White */
} // namespace ChromaColors

namespace LoggingInternalFunctions {

inline void add_ansi_settings(char *buffer, size_t buffer_size, int LogLevel) {

  uint64_t buffer_base_address = reinterpret_cast<uint64_t>(buffer);
    
  if (LogLevel&LoggingLevels::LogLevel_SUCCESS) {
    strcat_s(buffer, buffer_size, LoggingColors::GREEN);
  }

  if (LogLevel&LoggingLevels::LogLevel_WARN) {
    strcat_s(buffer, buffer_size, LoggingColors::YELLOW);
  }

  if (LogLevel&LoggingLevels::LogLevel_ERROR) {
    strcat_s(buffer, buffer_size, LoggingColors::RED);
  }

  if (LogLevel&LoggingLevels::LogLevel_INFO) {

    strcat_s(buffer, buffer_size, LoggingColors::BLUE);
  }



  if (Settings & (LoggingFlags::PRINT_BOLD )) { // code ;1 (1<<0)
    buffer[strlen(buffer)-1] = '\0';
    strcat_s(buffer, buffer_size, ";1");
    strcat_s(buffer, buffer_size, "m");
  }

  if (Settings &LoggingFlags::PRINT_BLINKING) { // code ;1 (1<<0)
    buffer[strlen(buffer)-1] = '\0';
    strcat_s(buffer, buffer_size, ";5");
    strcat_s(buffer, buffer_size, "m");
  }
};

inline void add_time(char *buffer, size_t buffer_size) {
  if ((Settings & LoggingFlags::PRINT_TIME) == 0) return;
    char output[128];

    time_t timestamp = time(NULL);
    struct tm newtime;
    localtime_s(&newtime,&timestamp);
    
    std::strftime(output, 128, " [%H:%M:%S %d.%m.%Y] ", &newtime);
    strcat_s(buffer , buffer_size, output);
  }
}

inline void add_prefix(char* buffer, size_t buffer_size, size_t LogLevel) {
  if ((Settings&LoggingFlags::PRINT_PREFIX) == 0) return;

  if (LogLevel&LoggingLevels::LogLevel_SUCCESS&Settings) {
    strcat_s(buffer, buffer_size, "[SUCCESS]");
  } else if (LogLevel&LoggingLevels::LogLevel_WARN&Settings) {
    strcat_s(buffer, buffer_size, "[WARN]");
  } else if (LogLevel&LoggingLevels::LogLevel_ERROR&Settings) {
    strcat_s(buffer, buffer_size, "[ERROR]");
  } else if (LogLevel&LoggingLevels::LogLevel_INFO&Settings) {
    strcat_s(buffer, buffer_size, "[INFO]");
  } else {
    strcat_s(buffer, buffer_size, "[???]");
  }
  
}
} // namespace ChromaInternalFunctions

inline void remove_setting(int settings_to_remove, ...) {
  if (Settings & settings_to_remove) {
    Settings = Settings & ~(settings_to_remove);
  }
}

template <typename... Types>
inline void print(const char *format, int LogLevel, Types... args) {
  
  if (((LogLevel & LoggingLevels::LogLevel_SUCCESS & Settings) == 0) && 
    ((LogLevel & LoggingLevels::LogLevel_ERROR & Settings) == 0)  && 
    ((LogLevel & LoggingLevels::LogLevel_WARN & Settings) == 0)   &&
    ((LogLevel & LoggingLevels::LogLevel_INFO & Settings) == 0)   &&
    ((LoggingLevels::LogLevel_ALL & Settings) == 0)) return;

  char buffer[1024]{};
  LoggingInternalFunctions::add_ansi_settings(buffer, sizeof(buffer), LogLevel);
  LoggingInternalFunctions::add_prefix(buffer, sizeof(buffer), LogLevel);
  LoggingInternalFunctions::add_time(buffer, sizeof(buffer));
  strcat_s(buffer, sizeof(buffer), format);
  strcat_s(buffer, sizeof(buffer), LoggingColors::RESET);

  printf(buffer, args...);
};

} // namespace Chroma
