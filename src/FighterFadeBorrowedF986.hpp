#pragma once
#include <stddef.h>

// Independently native-observed two adjacent unsigned BYTE fields
// in the pinned Japanese TH075 original actor: +0x538 fade lifetime,
// +0x539 drawing style/mode. Borrow ONLY the 2-byte window;
// never allocate or claim a full original fighter layout.
struct FighterFadeBorrowedF986 {
    unsigned char fadeAlphaAt538;
    unsigned char drawModeAt539;
};
typedef char FighterFadeWindowSizeF986[
    sizeof(FighterFadeBorrowedF986)==2 ? 1 : -1];
typedef char FighterFadeWindowOffsetF986[
    offsetof(FighterFadeBorrowedF986,drawModeAt539)==1 ? 1 : -1];
#define F986_FADE(receiver) (*reinterpret_cast<FighterFadeBorrowedF986*>(reinterpret_cast<unsigned char*>(receiver)+0x538))
