#ifndef PLATFORM_COMPATIBILITY_H
#define PLATFORM_COMPATIBILITY_H

#include <string>

enum class WindowStyle {POPUP, MENU, CUSTOM};

struct WindowData {
    int width, height;
    std::string name;
    WindowStyle style;
    bool defaultFullscreen;

    WindowData() {
        width = 0; height = 0;
        name = "Uninitialized";
        style = WindowStyle::MENU;
        defaultFullscreen = false;
    }
};

struct WindowRectangle {
    uint32_t x, y;
    uint32_t width, height;
};

#endif
