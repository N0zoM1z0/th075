#include "Graphics.hpp"

namespace Graphics {
extern PresentCallback g_PresentCallback;
extern bool g_Windowed;
extern bool g_Use16BitBackBuffer;
extern D3DPRESENT_PARAMETERS g_PresentationParameters;
extern D3DDISPLAYMODE g_DisplayMode;
extern int g_ClientWidth, g_ClientHeight;
extern HWND g_Window;
void ResetDevice();

void ToggleWindowMode() {
    if (g_PresentCallback)
        return;
    if (g_Windowed) {
        g_Windowed = false;
        ShowCursor(FALSE);
        if (g_Use16BitBackBuffer)
            g_PresentationParameters.BackBufferFormat = D3DFMT_R5G6B5;
        else
            g_PresentationParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
        g_PresentationParameters.Windowed = FALSE;
        ResetDevice();
        SetWindowPos(g_Window, 0, 0, 0, g_ClientWidth, g_ClientHeight, SWP_FRAMECHANGED);
    } else {
        int width, x, screenHeight, y;
        g_Windowed = true;
        ShowCursor(TRUE);
        g_PresentationParameters.BackBufferFormat = g_DisplayMode.Format;
        g_PresentationParameters.Windowed = TRUE;
        ResetDevice();
        width = GetSystemMetrics(SM_CXEDGE) + g_ClientWidth
            + GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CXDLGFRAME);
        screenHeight = GetSystemMetrics(SM_CYEDGE) + g_ClientHeight
            + GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYDLGFRAME)
            + GetSystemMetrics(SM_CYCAPTION);
        x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
        // Target computes vertical centering, then passes x for both coordinates.
        y = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
        SetWindowPos(g_Window, 0, x, x, width, screenHeight, SWP_FRAMECHANGED);
    }
}
}
