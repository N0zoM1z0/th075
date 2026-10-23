#include "AnimationProgress40FA30.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

short AnimationProgress40FA30::AdvanceNestedFrame() {
    ++FIELD(short, 0x64);
    if (FIELD(short, 0x64) >= FIELD(short, 0x72)) {
        FIELD(short, 0x64) = 0;
        ++FIELD(short, 0x62);
        if (FIELD(short, 0x62) >= FIELD(short, 0x70)) {
            FIELD(short, 0x62) = 0;
            OnSecondaryCounterReset();
            return FIELD(short, 0x70);
        }
        OnSecondaryCounterReset();
        return FIELD(short, 0x62);
    }
    return 0;
}

#undef FIELD
