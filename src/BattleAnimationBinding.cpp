#include "BattleAnimationBinding.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FRAME_WORD(offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(FIELD(AnimationFrameF139*, 0x74)) + (offset)))

void BattleAnimationBindingF139::BindAnimation()
{
    FIELD(AnimationFrameF139*, 0x74) =
        &FIELD(AnimationRowsF139*, 0xC4)->at(FIELD(short, 0x60))->at(FIELD(short, 0x62));
    FIELD(AnimationFrameF139*, 8) = FIELD(AnimationFrameF139*, 0x74);
    FIELD(unsigned short, 0x72) = FRAME_WORD(4);
    FIELD(short, 0x70) = FIELD(AnimationRowsF139*, 0xC4)->at(FIELD(short, 0x60))->size();
    FIELD(AnimationRowF139*, 0x78) = FIELD(AnimationRowsF139*, 0xC4)->at(FIELD(short, 0x60));
}

#undef FRAME_WORD
#undef FIELD
