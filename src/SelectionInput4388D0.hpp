#pragma once
#include "GameSharedState.hpp"
#include "InputJoystick.hpp"
#include <string.h>

struct HeldInputBlock4388D0 { int counts[7]; };
typedef char HeldInputBlockSize4388D0[(sizeof(HeldInputBlock4388D0) == 28) ? 1 : -1];

struct InputBindingKeys {
    signed char device;
    unsigned char unknown001[3];
    int left, right, up, down;
    int buttons[5];
};

class InputMapping4388D0 : private InputResourceClient {
    unsigned char unknown000[4];
    InputBindingKeys keys;

public:
    InputMapping4388D0();
    ~InputMapping4388D0();
    void SetBindings(const void* source);
    void UpdateHeldCounts();
    bool IsKeyDown(unsigned char key);

    HeldInputBlock4388D0 held;
};
typedef char InputMappingSize[(sizeof(InputMapping4388D0) == 72) ? 1 : -1];

extern InputMapping4388D0 g_InputMappings[2];
extern signed char g_SelectActiveSideAt006714B8;
namespace Input { extern unsigned char g_KeyboardState[256]; }
namespace Graphics { void ToggleWindowMode(); }
