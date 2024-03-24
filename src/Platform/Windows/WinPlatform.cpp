#ifdef LP_WINDOWS

#include "Platform/Platform.h"

DWORD Platform::ToWinStyle(WindowStyle style) {
    switch(style) {
    case WindowStyle::POPUP:     return WS_POPUP;
    case WindowStyle::MENU:      return WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_THICKFRAME;
    case WindowStyle::CUSTOM:    return WS_POPUP|WS_THICKFRAME;
    default: return WS_SYSMENU;
    }
}

#endif
