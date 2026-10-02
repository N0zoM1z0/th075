#include "Input.hpp"
#include <windows.h>

namespace Input
{
extern HWND g_Window;

void ShowError(const char *message)
{
    MessageBoxA(g_Window, message, "DInput-Error", 0);
}
}
