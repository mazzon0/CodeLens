#ifdef LP_WINDOWS

#include "Platform/Platform.h"

DWORD Platform::ToWinStyle(WindowStyle style) {
    switch(style) {
    case WindowStyle::POPUP:     return WS_POPUP;
    case WindowStyle::MENU:      return WS_CAPTION|WS_SYSMENU;
    case WindowStyle::CUSTOM:    return 0;
    default: return WS_CAPTION|WS_SYSMENU;
    }
}

#endif
