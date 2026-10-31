#pragma once
#include <stddef.h>

// Actual ORIGINAL Japanese TH075 fighter short WORD addresses. Independent
// pinned PE source functions in five native C++ translation units confirm
// signed 16-bit loads/stores at +0x3B0,+0x3B2,+0x3B4,+0x3B6,+0x3B8.
// Only a BORROWED ten-byte window: no complete historical fighter object,
// allocation, embedding, unobserved prefix, or artificial padding.
struct FighterGaugeBorrowedF980 {
    signed short meterAt3B0;
    signed short previousAt3B2;
    signed short waitAt3B4;
    signed short cooldownAt3B6;
    signed short scalarAt3B8;
};
typedef char FighterGaugeSizeF980[sizeof(FighterGaugeBorrowedF980)==10 ? 1 : -1];
typedef char FighterGaugeOffsetsF980[
    (offsetof(FighterGaugeBorrowedF980,previousAt3B2)==2 &&
     offsetof(FighterGaugeBorrowedF980,waitAt3B4)==4 &&
     offsetof(FighterGaugeBorrowedF980,cooldownAt3B6)==6 &&
     offsetof(FighterGaugeBorrowedF980,scalarAt3B8)==8) ? 1 : -1];
#define F980_GAUGE(receiver) (*reinterpret_cast<FighterGaugeBorrowedF980*>(reinterpret_cast<unsigned char*>(receiver)+0x3B0))
