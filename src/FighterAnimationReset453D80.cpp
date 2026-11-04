#include "FighterAnimationReset453D80.hpp"
#include "AnimationBindingWindowF1086.hpp"
typedef AnimationBindingWindowF1086<AnimationFrameF156,AnimationSequenceF156> F1086NativeWindow_AnimationFrameF156;
typedef char F1086NativeWindowLayout_AnimationFrameF156[
    sizeof(F1086NativeWindow_AnimationFrameF156)==12 &&
    offsetof(F1086NativeWindow_AnimationFrameF156,frameDurationAt72)==2 &&
    offsetof(F1086NativeWindow_AnimationFrameF156,currentFrameAt74)==4 &&
    offsetof(F1086NativeWindow_AnimationFrameF156,currentRowAt78)==8 ? 1 : -1];

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define SEQUENCES reinterpret_cast<AnimationSequencesF156*>(reinterpret_cast<unsigned char*>(this) + 0x468)
#define BINDING F1086_BINDING(this,AnimationFrameF156,AnimationSequenceF156)

void FighterAnimationReset453D80::BindAnimation()
{
    BINDING.currentFrameAt74 =
        &SEQUENCES->At(FIELD(short, 0x60))->At(FIELD(short, 0x62));
    FIELD(AnimationFrameF156*, 0x08) = BINDING.currentFrameAt74;
    BINDING.frameDurationAt72 = *reinterpret_cast<short*>(
        reinterpret_cast<unsigned char*>(BINDING.currentFrameAt74) + 4);
    BINDING.sequenceFrameCountAt70 = static_cast<short>(SEQUENCES->At(FIELD(short, 0x60))->Count());
    BINDING.currentRowAt78 = SEQUENCES->At(FIELD(short, 0x60));
}

#undef BINDING
#undef SEQUENCES
#undef FIELD
