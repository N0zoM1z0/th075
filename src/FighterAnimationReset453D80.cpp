#include "FighterAnimationReset453D80.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define SEQUENCES reinterpret_cast<AnimationSequencesF156*>(reinterpret_cast<unsigned char*>(this) + 0x468)

void FighterAnimationReset453D80::BindAnimation()
{
    FIELD(AnimationFrameF156*, 0x74) =
        &SEQUENCES->At(FIELD(short, 0x60))->At(FIELD(short, 0x62));
    FIELD(AnimationFrameF156*, 0x08) = FIELD(AnimationFrameF156*, 0x74);
    FIELD(short, 0x72) = *reinterpret_cast<short*>(
        reinterpret_cast<unsigned char*>(FIELD(AnimationFrameF156*, 0x74)) + 4);
    FIELD(short, 0x70) = static_cast<short>(SEQUENCES->At(FIELD(short, 0x60))->Count());
    FIELD(AnimationSequenceF156*, 0x78) = SEQUENCES->At(FIELD(short, 0x60));
}

#undef SEQUENCES
#undef FIELD
