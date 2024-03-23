#ifndef PLATFORM_H
#define PLATFORM_H

#include "Compatibility.h"

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
