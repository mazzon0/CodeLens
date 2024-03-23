#ifndef PLATFORM_WINDOW_H
#define PLATFORM_WINDOW_H

#include "Compatibility.h"

class Window {
public:
    Window();
    Window(WindowData data);
    ~Window();
    Window& Window::operator =(const Window& other);

    void ProcessEvents();

private:
    WindowData data;
    bool active = false;

#ifdef LP_WINDOWS
    HWND hWnd;
    const LPCSTR className = "WndClass1";
#endif
};

#endif
