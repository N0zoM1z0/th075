#pragma once
#include <stddef.h>

// Real Japanese TH075 original AuxiliaryActor4A80F0 native stage
// uses five adjacent signed short WORDs at actor+D8..E0.
// The gameplay changes semantics with animation/action, so field
// names intentionally specify physical storage, not guessed full
// historical owner layout or allocation.
struct AuxiliaryActorWordWindowF1124 {
    signed short stageAngleAtD8;
    signed short stageSpeedAtDA;
    signed short responseAtDC;
    signed short targetAngleAtDE;
    signed short spareAtE0;
};
typedef char F1124AuxWindowSize[sizeof(AuxiliaryActorWordWindowF1124)==10?1:-1];
typedef char F1124AuxOffsetTarget[offsetof(AuxiliaryActorWordWindowF1124,targetAngleAtDE)==6?1:-1];
typedef char F1124AuxOffsetEnd[offsetof(AuxiliaryActorWordWindowF1124,spareAtE0)==8?1:-1];
#define F1124_AUX_WORDS(owner) (*reinterpret_cast<AuxiliaryActorWordWindowF1124*>(reinterpret_cast<unsigned char*>(owner)+0xD8))
