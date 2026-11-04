#include "BattleAnimationBinding.hpp"
#include "AnimationBindingWindowF1086.hpp"
typedef AnimationBindingWindowF1086<AnimationFrameF139,AnimationRowF139> F1086NativeWindow_AnimationFrameF139;
typedef char F1086NativeWindowLayout_AnimationFrameF139[
    sizeof(F1086NativeWindow_AnimationFrameF139)==12 &&
    offsetof(F1086NativeWindow_AnimationFrameF139,frameDurationAt72)==2 &&
    offsetof(F1086NativeWindow_AnimationFrameF139,currentFrameAt74)==4 &&
    offsetof(F1086NativeWindow_AnimationFrameF139,currentRowAt78)==8 ? 1 : -1];

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FRAME_WORD(offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(FIELD(AnimationFrameF139*, 0x74)) + (offset)))
#define BINDING F1086_BINDING(this,AnimationFrameF139,AnimationRowF139)

void BattleAnimationBindingF139::BindAnimation()
{
    BINDING.currentFrameAt74 =
        &FIELD(AnimationRowsF139*, 0xC4)->at(FIELD(short, 0x60))->at(FIELD(short, 0x62));
    FIELD(AnimationFrameF139*, 8) = BINDING.currentFrameAt74;
    BINDING.frameDurationAt72 = FRAME_WORD(4);
    BINDING.sequenceFrameCountAt70 = FIELD(AnimationRowsF139*, 0xC4)->at(FIELD(short, 0x60))->size();
    BINDING.currentRowAt78 = FIELD(AnimationRowsF139*, 0xC4)->at(FIELD(short, 0x60));
}

#undef BINDING
#undef FRAME_WORD
#undef FIELD
