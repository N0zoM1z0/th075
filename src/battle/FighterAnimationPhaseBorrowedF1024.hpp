#pragma once
#include <stddef.h>

// Independently pinned Japanese TH075 v1.11 native object memory:
// short animation-stage counter +0x62 and signed short
// frame-within-stage counter +0x64. The real originals
// (including a 31,352B auxiliary-state function, effect
// constructors, animation progression and fighter controls)
// use precisely WORD/MOVSX accesses at both offsets.
// This is only a borrowed FOUR-BYTE subobject, NOT a full
// complete historical actor layout or owned instance.
struct FighterAnimationPhaseBorrowedF1024 {
    signed short stageAt62;
    signed short frameAt64;
};
typedef char F1024PhaseSize[
    sizeof(FighterAnimationPhaseBorrowedF1024)==4 ? 1 : -1];
typedef char F1024FrameOffset[
    offsetof(FighterAnimationPhaseBorrowedF1024,frameAt64)==2 ? 1 : -1];
#define F1024_PHASE(actor) (*reinterpret_cast<FighterAnimationPhaseBorrowedF1024*>(reinterpret_cast<unsigned char*>(actor)+0x62))
