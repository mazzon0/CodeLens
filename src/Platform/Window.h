#ifndef PLATFORM_WINDOW_H
#define PLATFORM_WINDOW_H

#ifdef LP_WINDOWS
    #include "Windows/Win32.h"
#endif

#include "Compatibility.h"

class Window {
public:
    Window();
    Window(WindowData& data);
    ~Window();
    Window& Window::operator =(const Window& other);

    void Open();
    void ProcessEvents();
    void Resize(uint32_t width, uint32_t height);

    void Maximize();
    void Minimize();
    void SetFullscreen();
    void SetWindowed();

    bool IsFullscreen() { return fullscreen; }
    std::string GetName() { return data.name; }

private:
    WindowData data;
    WindowRectangle windowedStatus;
    bool fullscreen;
    void SaveStatus();

#ifdef LP_WINDOWS
private:
    HWND hWnd;
    const LPCSTR className = "WndClass1";
#endif
};

#endif
