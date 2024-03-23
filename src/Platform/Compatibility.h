#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#include <string>

enum class WindowStyle {POPUP, MENU, CUSTOM};

struct WindowData {
    int width, height;
    std::string name;
    WindowStyle style;

    WindowData() {
        width = 0; height = 0;
        name = "Uninitialized";
        style = WindowStyle::MENU;
    }
};

#ifdef LP_WINDOWS
#include "Windows/Win32.h"

DWORD ToWinStyle(WindowStyle& style);
#endif

#ifdef LP_APPLE

#endif

#ifdef LP_LINUX

#endif

#endif
