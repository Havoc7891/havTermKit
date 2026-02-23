# havTermKit

Havoc's single-file terminal utility library for modern C and C++.

It provides ANSI escape macros for text styling, colors, cursor control, screen clearing, and hyperlinks, plus a small init function to enable VT support and UTF-8 behavior on Windows.

## Table of Contents

- [Features](#features)
- [Quick Start](#quick-start)
- [Minimal C Example](#minimal-c-example)
- [Minimal C++ Example](#minimal-cpp-example)
- [Basic API](#basic-api)
- [Contributing](#contributing)
- [License](#license)

## Features

- Header-only (`havTermKit.h`)
- Works with C and C++
- ANSI text styles: bold, underline, italic, reverse, hidden, strike, reset variants
- 16-color foreground / background palettes (normal + bright)
- 256-color and truecolor helper macros
- Cursor movement, save / restore, clear line / screen macros
- OSC hyperlink macros
- Windows-friendly initialization (`havTermKit_Init`) for VT processing + UTF-8 console setup

## Quick Start

1. Copy `havTermKit.h` into your project.
2. Include the header:

```c
#include "havTermKit.h"
```

3. Call init once at startup:

```c
havTermKit_Init();
```

4. Use the provided macros in output:

```c
printf(ANSI_FG_BRIGHT_GREEN "Success" ANSI_RESET "\n");
printf(ANSI_UNDERLINE "Underlined text" ANSI_RESET "\n");
```

## Minimal C Example

```c
#include <stdio.h>

#include "havTermKit.h"

int main(void)
{
  havTermKit_Init();

  printf(ANSI_FG_BRIGHT_GREEN "\u2714  Success" ANSI_RESET "\n");
  printf(ANSI_FG_BRIGHT_RED "\u2716  Error" ANSI_RESET "\n");
  printf(ANSI_UNDERLINE "Underlined text" ANSI_RESET "\n");
  printf(ANSI_LINK_START("https://test.com") "Open test.com" ANSI_LINK_END "\n");

  return 0;
}
```

### Build

Linux / macOS (GCC / Clang):

```bash
gcc main.c -o app
./app
```

Windows (GCC in PowerShell / CMD):

```bat
gcc main.c -o app.exe
app.exe
```

<a name="minimal-cpp-example"></a>
## Minimal C++ Example

```cpp
#include <iostream>

#include "havTermKit.h"

int main()
{
  havTermKit_Init();

  std::cout << ANSI_FG_BRIGHT_GREEN << "\u2714  Success" << ANSI_RESET << "\n";
  std::cout << ANSI_FG_BRIGHT_RED << "\u2716  Error" << ANSI_RESET << "\n";
  std::cout << ANSI_UNDERLINE << "Underlined text" << ANSI_RESET << "\n";
  std::cout << ANSI_LINK_START("https://test.com") << "Open test.com" << ANSI_LINK_END
            << "\n";

  return 0;
}
```

### Build

Linux / macOS (G++ / Clang++):

```bash
g++ main.cpp -o app
./app
```

Windows (G++ in PowerShell / CMD):

```bat
g++ main.cpp -o app.exe
app.exe
```

## Basic API

### Initialization

- `havTermKit_Init()`

### Common Macros

- Reset: `ANSI_RESET`
- Styles: `ANSI_BOLD`, `ANSI_UNDERLINE`, `ANSI_ITALIC`, `ANSI_STRIKETHROUGH`, etc.
- Foreground colors: `ANSI_FG_RED`, `ANSI_FG_BRIGHT_CYAN`, etc.
- Background colors: `ANSI_BG_BLUE`, `ANSI_BG_BRIGHT_YELLOW`, etc.
- 256 colors: `ANSI_FG_256("196")`, `ANSI_BG_256("27")`
- RGB colors: `ANSI_FG_RGB("255","120","0")`, `ANSI_BG_RGB("20","20","20")`
- Cursor / screen: `ANSI_CURSOR_UP("2")`, `ANSI_CLEAR_LINE`, `ANSI_CLEAR_SCREEN`
- Hyperlinks: `ANSI_LINK_START("https://test.com") "Open test.com" ANSI_LINK_END`

## Contributing

Thank you for your interest! Suggestions for features and bug reports are always welcome via issues.

To maintain a consistent design and quality for this library, changes are implemented by the maintainer rather than via direct pull requests.

## License

Copyright &copy; 2026 Ren&eacute; Nicolaus

This library is released under the [MIT license](/LICENSE).