#pragma once
#include <stddef.h>

// Original Japanese TH075 independently calls through effect-queue
// receiver pointer physically at fighter+0x2EC from two distinct
// complete original source objects. The storage from +0x2F0 onward
// is only a BORROWED byte-leading transform, not a guessed full class.
// Template changes only the genuine pointee call interface, preserving
// the 4-byte original 32-bit pointer and adjacent byte placement.
template <class Queue>
struct FighterEffectQueueTailF973 {
    Queue* queuePointerAt2EC;
    unsigned char transformFirstByteAt2F0;
};
// The first byte lies physically four bytes after the 32-bit pointer;
// do not infer a real eight-byte allocation from C++ tail padding.
typedef char FighterEffectPointerBytesF973[(sizeof(void*)==4)?1:-1];
// VC7.1 cannot evaluate dependent-template offsetof in a typedef;
// the full original PE/COFF replay separately verifies the native
// pointer field at +2EC and transform byte at its adjacent +2F0.
struct FighterEffectParameterFirstF973 { float firstFloatAt314; };
typedef char FighterEffectParameterSizeF973[
    sizeof(FighterEffectParameterFirstF973)==4 ? 1 : -1];

#define F973_EFFECT_TAIL(Receiver, Queue) (*reinterpret_cast<FighterEffectQueueTailF973<Queue>*>(reinterpret_cast<unsigned char*>(Receiver)+0x2EC))
#define F973_EFFECT_PARAMETER(Receiver) (*reinterpret_cast<FighterEffectParameterFirstF973*>(reinterpret_cast<unsigned char*>(Receiver)+0x314))
