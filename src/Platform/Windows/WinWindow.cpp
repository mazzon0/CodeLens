#ifdef LP_WINDOWS

#include <iostream>
#include "Win32.h"
#include "Editor/Editor.h"
#include "Platform/Platform.h"
#include "Platform/Compatibility.h"
#include "Platform/Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // TODO: implement this function outside the platform library and pass it to the Window class, to make it customizable
    switch(msg) {
    case WM_CLOSE: Editor::Close(); break;
    case WM_KEYDOWN: Editor::ToggleFullscreen(); break;
    case WM_SIZE: 
        Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        window->Resize(LOWORD(lParam), HIWORD(lParam)); break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window() {
    hWnd = NULL;
}

Window::Window(WindowData& data) {
    this->data = data;
	hWnd = NULL;
}

Window& Window::operator =(const Window& other) {
    this->data.width = other.data.width;
    this->data.height = other.data.height;
    this->data.name = other.data.name;
    this->data.defaultFullscreen = other.data.defaultFullscreen;
    return *this;
}

Window::~Window() {
    DestroyWindow(hWnd);
    UnregisterClass(className, GetModuleHandle(0));
}

void Window::Open() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    //Creating window class
    WNDCLASSEX wndClass{};
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_OWNDC;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = nullptr;
    wndClass.hCursor = nullptr;
    wndClass.hbrBackground = nullptr;
    wndClass.lpszMenuName = nullptr;
    wndClass.lpszClassName = className;
    wndClass.hIconSm = nullptr;
    RegisterClassEx(&wndClass);

    //Creating window
    DWORD wndStyle = Platform::ToWinStyle(data.style);
    RECT windowRect = {};
    windowRect.left = 100;
    windowRect.right = windowRect.left + data.width;
    windowRect.top = 100;
    windowRect.bottom = windowRect.top + data.height;
    AdjustWindowRect(&windowRect, wndStyle, FALSE);

    hWnd = CreateWindowEx(
        0, className, data.name.c_str(), wndStyle, CW_USEDEFAULT, CW_USEDEFAULT,
        data.width, data.height, nullptr, nullptr, hInstance, this);
    
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
    ShowWindow(hWnd, SW_SHOW);
    SaveStatus();
    if(data.defaultFullscreen)
        SetFullscreen();
    else
        fullscreen = false;
}

void Window::ProcessEvents() {
    // TODO: check if it process multiple events or only one
    MSG msg;
    PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

void Window::Resize(uint32_t width, uint32_t height) {
    data.width = width;
    data.height = height;
}

void Window::Maximize() {
    PostMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
}

void Window::Minimize() {
    PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void Window::SetFullscreen() {
    SaveStatus();

    // Getting screen size
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO monitorInfo{};
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(hMonitor, &monitorInfo);
    int screenWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
    int screenHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

    // Get window style
    DWORD style = GetWindowLong(hWnd, GWL_STYLE);

    // Set fullscreen
    SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
    SetWindowPos(hWnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_NOZORDER | SWP_FRAMECHANGED);

    fullscreen = true;
}

void Window::SetWindowed() {
    // Get window style
    DWORD style = GetWindowLong(hWnd, GWL_STYLE);

    // Set windowed
    SetWindowLong(hWnd, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
    SetWindowPos(hWnd, HWND_TOP, windowedStatus.x, windowedStatus.y, windowedStatus.width, windowedStatus.height,
        SWP_NOZORDER | SWP_FRAMECHANGED);
    
    fullscreen = false;
}

void Window::SaveStatus() {
    RECT rect;
    if (GetWindowRect(hWnd, &rect))
    {
#ifdef LC_DEBUG
        int w = rect.right - rect.left;
        int h = rect.bottom - rect.top;
        if((w!=data.width) || (h!=data.height)) {
            std::cout << "ERROR: incompatible window size" << std::endl;
            std::cout << "rect: " << w << ", " << h << std::endl << "saved: " << data.width << ", " << data.height << std::endl;
        }
#endif
        windowedStatus.x = rect.left;
        windowedStatus.y = rect.top;
        windowedStatus.width = w;
        windowedStatus.height = h;
    }
    else {
        std::cout << "ERROR: Failed to get the window rect: error " << GetLastError() << std::endl;
    }
}

#endif
