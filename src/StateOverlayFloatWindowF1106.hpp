#pragma once
#include <stddef.h>

// Seven adjacent native 32-bit float fields within the original
// StateFramePolicies overlay renderer at owner+0x70..+0x88.
// This is a borrowed field window only, not the full original owner.
struct StateOverlayFloatWindowF1106 {
    float at70;
    float at74;
    float at78;
    float at7C;
    float at80;
    float at84;
    float at88;
};
typedef char F1106OverlayFloatSize[sizeof(StateOverlayFloatWindowF1106)==28?1:-1];
typedef char F1106OverlayFloatEnd[offsetof(StateOverlayFloatWindowF1106,at88)==24?1:-1];
typedef char F1106OverlayFloatMiddle[offsetof(StateOverlayFloatWindowF1106,at7C)==12?1:-1];
#define F1106_OVERLAY(owner) (*reinterpret_cast<StateOverlayFloatWindowF1106*>(reinterpret_cast<unsigned char*>(owner)+0x70))
