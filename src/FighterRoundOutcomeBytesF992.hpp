#pragma once
#include <stddef.h>

// The pinned original Japanese game uses a SIGNED char test at fighter
// +0x3CE in hit processing, yet unsigned-byte writes at that address
// in round reset and knockout paths. The adjacent original +0x3CF
// is an independent unsigned status/continuation BYTE.
// This is a BORROWED TWO-BYTE WINDOW, NOT a whole original fighter.
union FighterOutcomeByteF992 {
    signed char signedAt3CE;
    unsigned char unsignedAt3CE;
};
struct FighterRoundOutcomeBytesF992 {
    FighterOutcomeByteF992 outcomeAt3CE;
    unsigned char continuationAt3CF;
};
typedef char FighterOutcomeByteSizeF992[
    sizeof(FighterRoundOutcomeBytesF992)==2 ? 1 : -1];
typedef char FighterOutcomeByteOffsetF992[
    offsetof(FighterRoundOutcomeBytesF992,continuationAt3CF)==1 ? 1 : -1];
#define F992_OUTCOME(actor) (*reinterpret_cast<FighterRoundOutcomeBytesF992*>(reinterpret_cast<unsigned char*>(actor)+0x3CE))
