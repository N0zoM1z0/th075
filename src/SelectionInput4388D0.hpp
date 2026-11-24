#pragma once
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "InputJoystick.hpp"
#include <string.h>

#include "InputMapping4388D0.hpp"

extern InputMapping4388D0 g_InputMappings[2];
namespace Input { extern unsigned char g_KeyboardState[256]; }
namespace Graphics { void ToggleWindowMode(); }
