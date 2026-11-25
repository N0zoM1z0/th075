#pragma once
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "input/InputJoystick.hpp"
#include <string.h>

#include "input/InputMapping4388D0.hpp"

extern InputMapping4388D0 g_InputMappings[2];
namespace Input { extern unsigned char g_KeyboardState[256]; }
namespace Graphics { void ToggleWindowMode(); }
