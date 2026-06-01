#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <ctime>

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
    #define PRINT_BOLD (1<<0) //bit 1
    #define PRINT_TIME (1<<1) //bit 2
    #define PRINT_FILE (1<<2) //bit 3
    #define PRINT_BLINKING (1<<3) //bit 4
}

namespace ChromaColors {
    inline char RESET[32] =  "\033[0m";
    inline char BLACK[32] = "\033[30m";      /* Black */
    inline char RED[32] =   "\033[31m";      /* Red */
    inline char GREEN[32] = "\033[32m";      /* Green */
    inline char YELLOW[32] ="\033[33m";      /* Yellow */
    inline char BLUE[32] =  "\033[34m";      /* Blue */
    inline char MAGENTA[32]="\033[35m";      /* Magenta */
    inline char CYAN[32] =  "\033[36m";      /* Cyan */
    inline char WHITE[32] = "\033[37m";      /* White */
    inline char BOLDBLACK[32] =   "\033[1m\033[30m";      /* Bold Black */
    inline char BOLDRED[32] =     "\033[1m\033[31m";      /* Bold Red */
    inline char BOLDGREEN[32] =   "\033[1m\033[32m";      /* Bold Green */
    inline char BOLDYELLOW[32] =  "\033[1m\033[33m";      /* Bold Yellow */
    inline char BOLDBLUE[32] =    "\033[1m\033[34m";      /* Bold Blue */
    inline char BOLDMAGENTA[32] = "\033[1m\033[35m";      /* Bold Magenta */
    inline char BOLDCYAN[32] =    "\033[1m\033[36m";      /* Bold Cyan */
    inline char BOLDWHITE[32] =   "\033[1m\033[37m";      /* Bold White */
}

namespace ChromaInternalFunctions {

static inline char *add_ansi_settings(char *ansi_color_buffer) {
  uint64_t color_code_base_address =
      reinterpret_cast<uint64_t>(ansi_color_buffer);

  if (Settings & PRINT_BOLD) { // code ;1 (1<<0)
    while ((*ansi_color_buffer) != 0x6D)
      ansi_color_buffer++;

    *(ansi_color_buffer) = 0x3B;
    *(ansi_color_buffer + 1) = 0x31;
    *(ansi_color_buffer + 2) = 0x6D;
  }

  if (Settings & PRINT_BLINKING) { // code ;1 (1<<0)
    while ((*ansi_color_buffer) != 0x6D)
      ansi_color_buffer++;

    *(ansi_color_buffer) = 0x3B;
    *(ansi_color_buffer + 1) = 0x35;
    *(ansi_color_buffer + 2) = 0x6D;
  }

  return (char *)color_code_base_address;
};

inline time_t timestamp = time(NULL);
inline struct tm datetime = *localtime(&timestamp);

inline void add_time(char *buffer) {
  if (Settings & PRINT_TIME) {
    char output[50];
    strftime(output, 50, "%B %e, %Y", &datetime);

    std::strcat(buffer, output);
  }
}

inline void add_current_file(char *buffer) {
  if (Settings & PRINT_FILE) {
    std::strcat(buffer, __FUNCTION__);
  }
}
} // namespace InternalFunctions

inline void remove_setting(int settings_to_remove, ...) {
  if (Settings & settings_to_remove) {
    Settings = Settings & ~(settings_to_remove);
  }
}



template <typename... Types>
inline void print_success(const char *format, Types... args) {
  char buffer[256];
  std::strcpy(buffer, ChromaInternalFunctions::add_ansi_settings(ChromaColors::GREEN));
  ChromaInternalFunctions::add_time(buffer);
  ChromaInternalFunctions::add_current_file(buffer);
  std::strcat(buffer, format);
  std::strcat(buffer, ChromaColors::RESET);

  printf(buffer, args...);
};

template <typename... Types>
inline void print_warning(const char *format, Types... args) {
  char buffer[256];
  std::strcpy(buffer, ChromaInternalFunctions::add_ansi_settings(ChromaColors::YELLOW));
  std::strcat(buffer, format);
  std::strcat(buffer, ChromaColors::RESET);

  printf(buffer, args...);
};

template <typename... Types>
inline void print_error(const char *format, Types... args) {
  char buffer[256];
  std::strcpy(buffer, ChromaInternalFunctions::add_ansi_settings(ChromaColors::RED));
  std::strcat(buffer, format);
  std::strcat(buffer, ChromaColors::RESET);

  printf(buffer, args...);
};

template <typename... Types>
inline void print_color(const char *format, char *color, Types... args) {
  char buffer[256];
  std::strcpy(buffer, ChromaInternalFunctions::add_ansi_settings(color));
  std::strcat(buffer, format);
  std::strcat(buffer, ChromaColors::RESET);

  printf(buffer, args...);
}

} // namespace Chroma
