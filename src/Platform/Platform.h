#ifndef PLATFORM_PLATFORM_H
#define PLATFORM_PLATFORM_H

#include "Compatibility.h"
#ifdef LP_WINDOWS
    #include "Windows/Win32.h"
#endif

class Platform {
    public:
    // Input

    // File management

    // Dialog

    // Memory management

    // Compatibility
#ifdef LP_WINDOWS
    static DWORD ToWinStyle(WindowStyle style);
#endif

    private:
    /*static Platform& Get() {
        static Platform instance;
        return instance;
    }*/
};

#endif
