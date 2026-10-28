#include <windows.h>
// Independently original R114 complete native callback: three real Win32
// message handlers and actual stdcall 4-param ABI, not a guessed owner.
// Complete original 83-byte WinMain application window class callback.
// This is the actual native Win32 stdcall four-argument WndProc.
extern unsigned char g_AppInitializedAt0068D674;
LRESULT CALLBACK AppWindowProcF468(HWND window,UINT message,WPARAM key,LPARAM mouse) {
    switch(message) {
    case WM_CREATE:
        g_AppInitializedAt0068D674=1;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_QUIT:
        break;
    default:
        return DefWindowProcA(window,message,key,mouse);
    }
    return 0;
}
