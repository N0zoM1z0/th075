#pragma once

// The round-outcome byte at Fighter+0x3CE has two native interpretations:
// hit processing sign-extends it, while knockout/round-reset paths write it
// as an unsigned byte. Keep both views in one byte of actual fighter storage.
union FighterOutcomeByteF992 {
    signed char signedAt3CE;
    unsigned char unsignedAt3CE;
};
typedef char FighterOutcomeByteF992SizeCheck[
    sizeof(FighterOutcomeByteF992) == 1 ? 1 : -1];
