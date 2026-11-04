#pragma once
#include <stddef.h>

// Physical 16-byte borrowed window of the independently original TH075
// ComboCounter HUD receiver, starting at native owner+4. All fields are
// independently read/written by its accepted 59B constructor / 154B
// update callables. This does not establish a complete historical HUD owner.
struct ComboHudWindowF1060 {
    signed short countAt04;
    signed short damageAt06;
    signed short ratioAt08;
    unsigned char opacityAt0A;
    signed char sideAt0B;
    signed short holdAt0C;
    signed short phaseAt0E;
    float verticalAt10;
};
typedef char F1060HudSizeCheck[sizeof(ComboHudWindowF1060)==16?1:-1];
typedef char F1060HudOpacityCheck[offsetof(ComboHudWindowF1060,opacityAt0A)==6?1:-1];
typedef char F1060HudSideCheck[offsetof(ComboHudWindowF1060,sideAt0B)==7?1:-1];
typedef char F1060HudFloatCheck[offsetof(ComboHudWindowF1060,verticalAt10)==12?1:-1];
#define F1060_HUD(receiver) (*reinterpret_cast<ComboHudWindowF1060*>(reinterpret_cast<unsigned char*>(receiver)+4))
