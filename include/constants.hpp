#pragma once
#include <iostream>

// Completely yoinked!
namespace codes
{
    constexpr const char *reset = "\033[0m";
    constexpr const char *new_line = "\n";

    constexpr const char *arrow = " ➤  ";
    constexpr const char *bold = "\033[1m";
    constexpr const char *underline = "\033[4m";

    constexpr const char *red = "\033[31m";
    constexpr const char *green = "\033[32m";
    constexpr const char *yellow = "\033[33m";
    constexpr const char *blue = "\033[34m";
    constexpr const char *magenta = "\033[35m";
    constexpr const char *cyan = "\033[36m";
    constexpr const char *white = "\033[37m";
}
