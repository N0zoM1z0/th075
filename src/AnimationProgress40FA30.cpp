#include "FighterAnimationPhaseBorrowedF1024.hpp"
#include "AnimationProgress40FA30.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

short AnimationProgress40FA30::AdvanceNestedFrame() {
    ++F1024_PHASE(this).frameAt64;
    if (F1024_PHASE(this).frameAt64 >= FIELD(short, 0x72)) {
        F1024_PHASE(this).frameAt64 = 0;
        ++F1024_PHASE(this).stageAt62;
        if (F1024_PHASE(this).stageAt62 >= FIELD(short, 0x70)) {
            F1024_PHASE(this).stageAt62 = 0;
            OnSecondaryCounterReset();
            return FIELD(short, 0x70);
        }
        OnSecondaryCounterReset();
        return F1024_PHASE(this).stageAt62;
    }
    return 0;
}

#undef FIELD
