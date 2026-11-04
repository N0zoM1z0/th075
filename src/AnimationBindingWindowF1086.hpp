#pragma once
#include <stddef.h>

// True 12B borrowed +0x70..+0x7B native actor animation-binding window
// shared by two independently accepted complete 149B original functions.
// Frame and Row pointer types remain source-specific. This is NOT an
// allocated original animation owner, complete fighter class or array.
template<class NativeFrame,class NativeRow>
struct AnimationBindingWindowF1086 {
    signed short sequenceFrameCountAt70;
    unsigned short frameDurationAt72;
    NativeFrame* currentFrameAt74;
    NativeRow* currentRowAt78;
};
typedef char F1086PointerSizeMustBe4[sizeof(void*)==4 ? 1 : -1];
#define F1086_BINDING(owner,frame,row) (*reinterpret_cast<AnimationBindingWindowF1086<frame,row>*>(reinterpret_cast<unsigned char*>(owner)+0x70))
