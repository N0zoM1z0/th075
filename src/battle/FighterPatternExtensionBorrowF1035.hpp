#pragma once

// Borrowed 36-byte extension window of a pattern frame during .pat loading.
// The original file reads its first WORD then writes the overlapping byte at
// +1 separately. The other byte and the naturally aligned gap at +5 have no
// independently recovered meaning. This is NOT the full owner type; the
// frame continues to own the pointer, never an embedded extension object.
struct FighterPatternExtensionBorrowF1035 {
    union {
        short wordAt00;
        unsigned char flagBytesAt00[2];
    } firstWord;
    unsigned char byteAt02;
    unsigned char byteAt03;
    unsigned char byteAt04;
    short wordAt06;
    short wordAt08;
    short wordAt0A;
    float scaledAt0C;
    float scaledAt10;
    float scaledAt14;
    float valueAt18;
    float valueAt1C;
    float valueAt20;
};
typedef char F1035ExtensionSize[(sizeof(FighterPatternExtensionBorrowF1035)==36)?1:-1];
typedef char F1035OverlappingByte[(offsetof(FighterPatternExtensionBorrowF1035, firstWord.flagBytesAt00)==0)?1:-1];
typedef char F1035FirstShort[(offsetof(FighterPatternExtensionBorrowF1035, wordAt06)==6)?1:-1];
typedef char F1035FloatBegin[(offsetof(FighterPatternExtensionBorrowF1035, scaledAt0C)==12)?1:-1];
typedef char F1035FloatEnd[(offsetof(FighterPatternExtensionBorrowF1035, valueAt20)==32)?1:-1];
