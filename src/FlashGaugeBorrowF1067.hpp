#pragma once
#include <stddef.h>

// Borrow-only native fields independently used by the original complete
// TH075 DamageFlash render game function. These are not complete owners.
// Fighter+0x3C8 stores a signed 16-bit visible flash-bar span.
struct FighterFlashGaugeBorrowF1067 {
    signed short barLengthAt3C8;
};
// Fighter+0x74 holds a genuine collision/frame pointer. The actual
// +0x3C bit flags are inside *that* referenced frame, not the fighter.
struct FlashFrameFlagsBorrowF1067 {
    unsigned int flagsAt3C;
};
typedef char F1067GaugeSize[sizeof(FighterFlashGaugeBorrowF1067)==2?1:-1];
typedef char F1067FlagsSize[sizeof(FlashFrameFlagsBorrowF1067)==4?1:-1];
typedef char F1067GaugeOffset[offsetof(FighterFlashGaugeBorrowF1067,barLengthAt3C8)==0?1:-1];
typedef char F1067FlagsOffset[offsetof(FlashFrameFlagsBorrowF1067,flagsAt3C)==0?1:-1];
#define F1067_FLASH_BAR(actor) (*reinterpret_cast<FighterFlashGaugeBorrowF1067*>(reinterpret_cast<unsigned char*>(actor)+0x3C8))
#define F1067_FRAME_FLAGS(frame) (*reinterpret_cast<FlashFrameFlagsBorrowF1067*>(reinterpret_cast<unsigned char*>(frame)+0x3C))
