#include "Platform/Window.h"
#include "UI/UI.h"
#include "Editor.h"

void Editor::iInit() {
    //DeserializeData();
    //std::cout << "Running CodeLens version" << GetVersion() << std::endl;

    //Window window(GetWindowInfo());
    WindowData wndData{};
    wndData.name = "CodeLens";
    wndData.width = 700;
    wndData.height = 400;
    wndData.style = WindowStyle::MENU;
    window = Window(wndData);
    
    UI::Init(); // UI::Init(window);
    // initialize other editor features
    running = true;
}

void Editor::iRun() {
    while(running) {
        window.ProcessEvents();
        /*
        UpdateUI();
        UI::Draw();
        */
    }
}

void Editor::iDestroy() {
    // destroy editor features
    UI::Destroy();
}