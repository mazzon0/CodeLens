#ifndef EDITOR_EDITOR_H
#define EDITOR_EDITOR_H

#include "Platform/Window.h"

class Editor {
public:
    static void Init() { Get().iInit(); }
    static void Run() { Get().iRun(); }
    static void Destroy() { Get().iDestroy(); }

    static void Close() { Get().iClose(); }
    static void ToggleFullscreen() { Get().iToggleFullscreen(); }   // TODO: remove

private:
    static Editor& Get() {
        static Editor instance;
        return instance;
    }

    void iInit();
    void iRun();
    void iDestroy();

    void iClose() { running = false; }

    void iToggleFullscreen() { // TODO: remove
        if(window.IsFullscreen())
            window.SetWindowed();
        else
            window.SetFullscreen();
    }

    bool running;
    Window window;
};

#endif

