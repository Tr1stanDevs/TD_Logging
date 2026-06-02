#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <iostream>


#ifdef _WIN32
#include <Windows.h>
#endif
// 1mb stacksize windows
// 8mb stacksize linux
// https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html

namespace Chroma {
inline int Settings = 0;

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
inline char RESET[32] = "\033[0m";
inline char BLACK[32] = "\033[30m";              /* Black */
inline char RED[32] = "\033[31m";                /* Red */
inline char GREEN[32] = "\033[32m";              /* Green */
inline char YELLOW[32] = "\033[33m";             /* Yellow */
inline char BLUE[32] = "\033[34m";               /* Blue */
inline char MAGENTA[32] = "\033[35m";            /* Magenta */
inline char CYAN[32] = "\033[36m";               /* Cyan */
inline char WHITE[32] = "\033[37m";              /* White */
} // namespace ChromaColors

namespace ChromaInternalFunctions {

inline char *add_ansi_settings(char *ansi_buffer, int LogLevel) {
  uint64_t buffer_base_address = reinterpret_cast<uint64_t>(ansi_buffer);
    
  if (LogLevel&LogLevel_SUCCESS) {
    std::strcpy(ansi_buffer, ChromaColors::GREEN);
  }

  if (LogLevel&LogLevel_WARN) {
    std::strcpy(ansi_buffer, ChromaColors::YELLOW);
  }

  if (LogLevel&LogLevel_ERROR) {
    std::strcpy(ansi_buffer, ChromaColors::RED);
  }

  if (Settings & PRINT_BOLD) { // code ;1 (1<<0)
    while ((*ansi_buffer) != 0x6D)
      ansi_buffer++;

    *(ansi_buffer) = 0x3B;
    *(ansi_buffer + 1) = 0x31;
    *(ansi_buffer + 2) = 0x6D;
  }

  if (Settings & PRINT_BLINKING) { // code ;1 (1<<0)
    while ((*ansi_buffer) != 0x6D)
      ansi_buffer++;

    *(ansi_buffer) = 0x3B;
    *(ansi_buffer + 1) = 0x35;
    *(ansi_buffer + 2) = 0x6D;
  }

  

  return (char *)buffer_base_address;
};

inline void add_time(char *buffer) {
  if (Settings & PRINT_TIME) {
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char output[50];
    strftime(output, 50, " [%H:%M:%S %d.%m.%Y] ", &datetime);

    std::strcat(buffer, output);
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
  char buffer[256];
  char ansi_buffer[64]{}; //add a \0 at the end
  std::strcpy(buffer, ChromaInternalFunctions::add_ansi_settings(ansi_buffer, LogLevel));
  ChromaInternalFunctions::add_time(buffer);
  std::strcat(buffer, format);
  std::strcat(buffer, ChromaColors::RESET);

  printf(buffer, args...);
};

} // namespace Chroma
