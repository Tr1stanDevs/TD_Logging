#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <string.h>
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
    
  if ((LogLevel&LogLevel_SUCCESS) & (Settings&LogLevel_SUCCESS)) {
    strcpy_s(ansi_buffer, strlen(ChromaColors::GREEN)+1, ChromaColors::GREEN);
  }

  if ((LogLevel&LogLevel_WARN) & (Settings&LogLevel_WARN)) {
    strcpy_s(ansi_buffer, strlen(ChromaColors::YELLOW)+1, ChromaColors::YELLOW);
  }

  if ((LogLevel&LogLevel_ERROR) & (Settings&LogLevel_ERROR)) {
    strcpy_s(ansi_buffer, strlen(ChromaColors::RED)+1, ChromaColors::RED);
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
    char output[50];

    time_t timestamp = time(NULL);
    struct tm newtime;
    localtime_s(&newtime,&timestamp);
    
    std::strftime(output, 64, " [%H:%M:%S %d.%m.%Y] ", &newtime);
    strcat_s(buffer , 64, output);
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
  if (
  (Settings&LogLevel_SUCCESS) != LogLevel & 
  (Settings&LogLevel_ERROR) != LogLevel  & 
  (Settings&LogLevel_WARN) != LogLevel) return;

  char buffer[256];
  char ansi_buffer[64]{}; //add a \0 at the end
  strcpy_s(buffer, sizeof(buffer), ChromaInternalFunctions::add_ansi_settings(ansi_buffer, LogLevel));
  ChromaInternalFunctions::add_time(buffer);
  strcat_s(buffer, sizeof(buffer), format);
  strcat_s(buffer, sizeof(buffer), ChromaColors::RESET);

  printf(buffer, args...);
};

} // namespace Chroma
