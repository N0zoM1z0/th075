#pragma once
#include "Input.hpp"
#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace Input
{
bool Initialize(HWND window, HINSTANCE instance);
bool CreateKeyboard();
void PollKeyboard();
}
