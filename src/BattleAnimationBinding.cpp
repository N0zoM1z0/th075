#include "BattleAnimationBinding.hpp"
#include "AnimationBindingWindowF1086.hpp"
typedef AnimationBindingWindowF1086<AnimationFrameF139,AnimationRowF139> F1086NativeWindow_AnimationFrameF139;
typedef char F1086NativeWindowLayout_AnimationFrameF139[
    sizeof(F1086NativeWindow_AnimationFrameF139)==12 &&
    offsetof(F1086NativeWindow_AnimationFrameF139,frameDurationAt72)==2 &&
    offsetof(F1086NativeWindow_AnimationFrameF139,currentFrameAt74)==4 &&
    offsetof(F1086NativeWindow_AnimationFrameF139,currentRowAt78)==8 ? 1 : -1];

#define FRAME_WORD(offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(field074) + (offset)))
#define BINDING F1086_BINDING(this,AnimationFrameF139,AnimationRowF139)

void BattleAnimationBindingF139::BindAnimation()
{
    BINDING.currentFrameAt74 =
        &field0C4->at(field060)->at(field062);
    field008 = BINDING.currentFrameAt74;
    BINDING.frameDurationAt72 = FRAME_WORD(4);
    BINDING.sequenceFrameCountAt70 = field0C4->at(field060)->size();
    BINDING.currentRowAt78 = field0C4->at(field060);
}

#undef BINDING
#undef FRAME_WORD
