#ifdef LP_WINDOWS

#include <iostream>
#include "Win32.h"
#include "Editor/Editor.h"
#include "Platform/Platform.h"
#include "Platform/Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // TODO: implement this function outside the platform library and pass it to the Window class, to make it customizable
    switch(msg) {
    case WM_CLOSE: Editor::Close(); break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window() {
    hWnd = NULL;
}

Window::Window(WindowData data) {
    this->data = data;
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

    ShowWindow(hWnd, SW_SHOW);
    active = true;
}

Window& Window::operator =(const Window& other) {
    if(active) {
        std::cout << "ERROR: trying to assign to an active window" << std::endl;
        return *this;
    }

    Window* wnd = new Window(other.data);
    return *wnd;
}

Window::~Window() {
    DestroyWindow(hWnd);
    UnregisterClass(className, GetModuleHandle(0));
}

void Window::ProcessEvents() {
    MSG msg;
    PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

#endif
