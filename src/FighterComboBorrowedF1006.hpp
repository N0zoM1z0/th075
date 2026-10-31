#pragma once
#include <stddef.h>

// The SHA-pinned Japanese TH075 original uses two adjacent signed
// 16-bit WORDs: fighter +0x3C4 (combo count) and +0x3C6 (damage).
// Independently verified from original collision, combat, gauge,
// and round reset whole callable disassemblies. BORROWED 4-byte
// window, never a full original actor layout or allocated owner.
struct FighterComboBorrowedF1006 {
    signed short countAt3C4;
    signed short damageAt3C6;
};
typedef char FighterComboBorrowedSizeF1006[
    sizeof(FighterComboBorrowedF1006)==4 ? 1 : -1];
typedef char FighterComboBorrowedOffsetF1006[
    offsetof(FighterComboBorrowedF1006,damageAt3C6)==2 ? 1 : -1];
#define F1006_COMBO(actor) (*reinterpret_cast<FighterComboBorrowedF1006*>(reinterpret_cast<unsigned char*>(actor)+0x3C4))
