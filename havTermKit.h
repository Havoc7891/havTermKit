/*
havTermKit.h

ABOUT

Havoc's single-file terminal utility library for modern C and C++.

REVISION HISTORY

v0.1 (2026-02-23) - First release.

LICENSE

MIT License

Copyright (c) 2026 René Nicolaus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef HAVTERMKIT_H
#define HAVTERMKIT_H

#include <locale.h>

#ifdef _WIN32
  #ifdef _MBCS
    #error "_MBCS is defined, but only Unicode is supported"
  #endif
  #undef _UNICODE
  #define _UNICODE
  #undef UNICODE
  #define UNICODE

  #undef NOMINMAX
  #define NOMINMAX

  #undef STRICT
  #define STRICT

  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WINXP
  #endif
  #ifdef _MSC_VER
    #include <SDKDDKVer.h>
  #endif

  #undef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif

/*
----------------------------------------------------------------
Initialization
----------------------------------------------------------------
*/

static inline void havTermKit_Init(void)
{
#ifdef _WIN32
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD mode = 0;

  if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &mode))
  {
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
  }

  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif

  /* Explicit UTF-8 locale (important on Windows) */
  setlocale(LC_ALL, ".UTF-8");
}

/*
----------------------------------------------------------------
Reset
----------------------------------------------------------------
*/

#define ANSI_RESET "\x1b[0m"

/*
----------------------------------------------------------------
Text attributes (SGR)
----------------------------------------------------------------
*/

/* Widely portable */
#define ANSI_BOLD "\x1b[1m" /* bold OR bright */
#define ANSI_UNDERLINE "\x1b[4m"
#define ANSI_REVERSE "\x1b[7m"
#define ANSI_HIDDEN "\x1b[8m"

/* Supported by Windows VT parser, rendering varies */
#define ANSI_DIM "\x1b[2m"
#define ANSI_ITALIC "\x1b[3m"
#define ANSI_STRIKETHROUGH "\x1b[9m"

/* Attribute reset variants */
#define ANSI_NO_BOLD_DIM "\x1b[22m"
#define ANSI_NO_ITALIC "\x1b[23m"
#define ANSI_NO_UNDERLINE "\x1b[24m"
#define ANSI_NO_REVERSE "\x1b[27m"
#define ANSI_NO_STRIKE "\x1b[29m"

/*
----------------------------------------------------------------
Standard foreground colors (16-color)
----------------------------------------------------------------
*/

#define ANSI_FG_BLACK "\x1b[30m"
#define ANSI_FG_RED "\x1b[31m"
#define ANSI_FG_GREEN "\x1b[32m"
#define ANSI_FG_YELLOW "\x1b[33m"
#define ANSI_FG_BLUE "\x1b[34m"
#define ANSI_FG_MAGENTA "\x1b[35m"
#define ANSI_FG_CYAN "\x1b[36m"
#define ANSI_FG_WHITE "\x1b[37m"

#define ANSI_FG_BRIGHT_BLACK "\x1b[90m"
#define ANSI_FG_BRIGHT_RED "\x1b[91m"
#define ANSI_FG_BRIGHT_GREEN "\x1b[92m"
#define ANSI_FG_BRIGHT_YELLOW "\x1b[93m"
#define ANSI_FG_BRIGHT_BLUE "\x1b[94m"
#define ANSI_FG_BRIGHT_MAGENTA "\x1b[95m"
#define ANSI_FG_BRIGHT_CYAN "\x1b[96m"
#define ANSI_FG_BRIGHT_WHITE "\x1b[97m"

/*
----------------------------------------------------------------
Background colors
----------------------------------------------------------------
*/

#define ANSI_BG_BLACK "\x1b[40m"
#define ANSI_BG_RED "\x1b[41m"
#define ANSI_BG_GREEN "\x1b[42m"
#define ANSI_BG_YELLOW "\x1b[43m"
#define ANSI_BG_BLUE "\x1b[44m"
#define ANSI_BG_MAGENTA "\x1b[45m"
#define ANSI_BG_CYAN "\x1b[46m"
#define ANSI_BG_WHITE "\x1b[47m"

#define ANSI_BG_BRIGHT_BLACK "\x1b[100m"
#define ANSI_BG_BRIGHT_RED "\x1b[101m"
#define ANSI_BG_BRIGHT_GREEN "\x1b[102m"
#define ANSI_BG_BRIGHT_YELLOW "\x1b[103m"
#define ANSI_BG_BRIGHT_BLUE "\x1b[104m"
#define ANSI_BG_BRIGHT_MAGENTA "\x1b[105m"
#define ANSI_BG_BRIGHT_CYAN "\x1b[106m"
#define ANSI_BG_BRIGHT_WHITE "\x1b[107m"

/*
----------------------------------------------------------------
256-color & truecolor (supported in Windows Terminal)
----------------------------------------------------------------
*/

#define ANSI_FG_256(n) "\x1b[38;5;" n "m"
#define ANSI_BG_256(n) "\x1b[48;5;" n "m"

#define ANSI_FG_RGB(r, g, b) "\x1b[38;2;" r ";" g ";" b "m"
#define ANSI_BG_RGB(r, g, b) "\x1b[48;2;" r ";" g ";" b "m"

/*
----------------------------------------------------------------
Cursor control (portable & supported by Windows VT)
----------------------------------------------------------------
*/

#define ANSI_CURSOR_UP(n) "\x1b[" n "A"
#define ANSI_CURSOR_DOWN(n) "\x1b[" n "B"
#define ANSI_CURSOR_FORWARD(n) "\x1b[" n "C"
#define ANSI_CURSOR_BACK(n) "\x1b[" n "D"

#define ANSI_CURSOR_SAVE "\x1b[s"
#define ANSI_CURSOR_RESTORE "\x1b[u"

#define ANSI_CLEAR_SCREEN "\x1b[2J"
#define ANSI_CLEAR_LINE "\x1b[2K"

/*
----------------------------------------------------------------
OSC hyperlinks (Windows Terminal, many Unix terminals)
----------------------------------------------------------------
*/

#define ANSI_LINK_START(url) "\x1b]8;;" url "\x1b\\"
#define ANSI_LINK_END "\x1b]8;;\x1b\\"

#endif
