#pragma once
// Borrowed read-only-in-context view of the independently observed
// original actor float at this+0x44. The preceding bytes are NOT a
// recovered full object layout. Never instantiate/embed this view.
struct FighterProjectileXViewF917 {
    unsigned int unspecifiedBeforeX[17];
    float coordinateXAt44;
};
typedef char FighterProjectileXViewF917Size[
    sizeof(FighterProjectileXViewF917) == 0x48 ? 1 : -1];
