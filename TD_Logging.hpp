#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define CHROMA_COLOR_BUFFER_SIZE 32
#define BUFFER_256 256
#define BUFFER_512 512

#ifdef _WIN32
#include <Windows.h>
#endif
// 1mb stacksize windows
// 8mb stacksize linux
// https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html

namespace Chroma {
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

namespace ChromaFlags {
#define PRINT_BOLD (1 << 0)     // bit 1
#define PRINT_TIME (1 << 1)     // bit 2
#define PRINT_FILE (1 << 2)     // bit 3
#define PRINT_BLINKING (1 << 3) // bit 4
#define PRINT_PREFIX (1<<4)
} // namespace ChromaFlags

namespace ChromaLogLevels {
#define LogLevel_INFO (1<<20)
#define LogLevel_SUCCESS (1<<21)
#define LogLevel_WARN (1<<22)
#define LogLevel_ERROR (1<<23)
#define LogLevel_FAIL (1<<24)
#define LogLevel_ALL (1<<25)
}

namespace ChromaColors {
constexpr char RESET[CHROMA_COLOR_BUFFER_SIZE] = "\033[0m";
constexpr char BLACK[CHROMA_COLOR_BUFFER_SIZE] = "\033[30m";              /* Black */
constexpr char RED[CHROMA_COLOR_BUFFER_SIZE] = "\033[31m";                /* Red */
constexpr char GREEN[CHROMA_COLOR_BUFFER_SIZE] = "\033[32m";              /* Green */
constexpr char YELLOW[CHROMA_COLOR_BUFFER_SIZE] = "\033[33m";             /* Yellow */
constexpr char BLUE[CHROMA_COLOR_BUFFER_SIZE] = "\033[34m";               /* Blue */
constexpr char MAGENTA[CHROMA_COLOR_BUFFER_SIZE] = "\033[35m";            /* Magenta */
constexpr char CYAN[CHROMA_COLOR_BUFFER_SIZE] = "\033[36m";               /* Cyan */
constexpr char WHITE[CHROMA_COLOR_BUFFER_SIZE] = "\033[37m";              /* White */
} // namespace ChromaColors

namespace ChromaInternalFunctions {

inline char *add_ansi_settings(char *buffer, int LogLevel) {
  uint64_t buffer_base_address = reinterpret_cast<uint64_t>(buffer);
    
  if (LogLevel&LogLevel_SUCCESS) {
    strcat_s(buffer, sizeof(buffer), ChromaColors::GREEN);
  }

  if (LogLevel&LogLevel_WARN) {
    strcat_s(buffer, sizeof(buffer), ChromaColors::YELLOW);
  }

  if (LogLevel&LogLevel_ERROR) {
    strcat_s(buffer, sizeof(buffer), ChromaColors::RED);
  }

  if (LogLevel&LogLevel_INFO) {
    strcat_s(buffer, sizeof(buffer), ChromaColors::BLUE);
  }

  if (Settings & PRINT_BOLD) { // code ;1 (1<<0)
    while ((*buffer) != 'm')
      buffer++;

    *(buffer) = ';';
    *(buffer + 1) = '1';
    *(buffer + 2) = 'm';
  }

  if (Settings & PRINT_BLINKING) { // code ;1 (1<<0)
    while ((*buffer) != 'm')
      buffer++;

    *(buffer) = ';';
    *(buffer + 1) = '5';
    *(buffer + 2) = 'm';
  }

  

  return (char *)buffer_base_address;
};

inline void add_time(char *buffer) {
  if (Settings & PRINT_TIME) {
    char output[50];

    time_t timestamp = time(NULL);
    struct tm newtime;
    localtime_s(&newtime,&timestamp);
    
    std::strftime(output, 64, " [%H:%M:%S %d.%m.%Y] ", &newtime);
    strcat_s(buffer , 64, output);
  }
}

inline void add_prefix(char* buffer, int LogLevel) {
  if (LogLevel&LogLevel_SUCCESS) {
    strcat_s(buffer, BUFFER_256, "[SUCCESS]");
  } else if (LogLevel&LogLevel_WARN) {
    strcat_s(buffer, BUFFER_256, "[WARN]");
  } else if (LogLevel&LogLevel_ERROR) {
    strcat_s(buffer, BUFFER_256, "[ERROR]");
  } else if (LogLevel&LogLevel_INFO) {
    strcat_s(buffer, BUFFER_256, "[INFO]");
  } else {
    strcat_s(buffer, BUFFER_256, "[???]");
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
  
  if (((LogLevel & LogLevel_SUCCESS & Settings) == 0) && 
    ((LogLevel & LogLevel_ERROR & Settings) == 0)  && 
    ((LogLevel & LogLevel_WARN & Settings) == 0)   &&
    ((LogLevel & LogLevel_INFO & Settings) == 0)   &&
    ((LogLevel_ALL & Settings) == 0)) return;

  char buffer[256]{};
  strcpy_s(buffer, BUFFER_256, ChromaInternalFunctions::add_ansi_settings(buffer, LogLevel));
  ChromaInternalFunctions::add_prefix(buffer, LogLevel);
  ChromaInternalFunctions::add_time(buffer);
  strcat_s(buffer, BUFFER_256, format);
  strcat_s(buffer, BUFFER_256, ChromaColors::RESET);

  printf(buffer, args...);
};

} // namespace Chroma
