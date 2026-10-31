#pragma once
#include <stddef.h>

// Original Japanese TH075 actor native field addresses: signed 16-bit
// health current +0x324 and adjacent recoverable health +0x326.
// Five independent COMPLETE original function source objects load and
// store these WORD fields. This is only a BORROWED 4-byte native window:
// it does not establish or allocate a full fighter class or prefix.
struct FighterVitalBorrowedF999 {
    signed short currentAt324;
    signed short recoverableAt326;
};
typedef char FighterVitalBorrowedSizeF999[
    sizeof(FighterVitalBorrowedF999)==4 ? 1 : -1];
typedef char FighterVitalBorrowedOffsetF999[
    offsetof(FighterVitalBorrowedF999,recoverableAt326)==2 ? 1 : -1];
#define F999_VITAL(receiver) (*reinterpret_cast<FighterVitalBorrowedF999*>(reinterpret_cast<unsigned char*>(receiver)+0x324))
