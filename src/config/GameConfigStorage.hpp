#pragma once

#include <stddef.h>
#include "input/InputMapping4388D0.hpp"

typedef char InputBindingKeysLayout[(
    sizeof(InputBindingKeys) == 0x28 &&
    offsetof(InputBindingKeys, left) == 0x04 &&
    offsetof(InputBindingKeys, buttons) == 0x14) ? 1 : -1];

extern InputBindingKeys g_PlayerKeyBindings[2];
extern unsigned char g_StreamVolumeAt006714B7;
extern unsigned char g_SoundVolumeAt006714B6;
