#pragma once
#include <stddef.h>

// Borrowed partial native entry layout, observed in two independently
// complete exact game functions at 0040C590 and 0040C8C0.
// Bytes between observed offsets are unknown occupied storage; this
// view is NEVER instantiated, allocated or embedded as a full entry.
// The pinned original getter uses these five observed entry offsets:
// signed 32-bit metadata at +4/+8/+0xC, bytes at +0 and +0x28.
// This is a BORROWED incomplete entry view; do not instantiate it,
// infer the full entry layout, or treat the unknown spans as fields.
struct NativeSpriteEntryViewF920 {
    unsigned char uploadFormatAt0;
    unsigned char unknown01to03[3];
    int storedWidthAt4;
    int storedHeightAt8;
    int metadataAt0C;
    unsigned char otherOccupied10to27[0x18];
    unsigned char paletteFlagAt28;
};
typedef char EntryF920FormatOffset[(offsetof(NativeSpriteEntryViewF920, uploadFormatAt0)==0)?1:-1];
typedef char EntryF920WidthOffset[(offsetof(NativeSpriteEntryViewF920, storedWidthAt4)==4)?1:-1];
typedef char EntryF920HeightOffset[(offsetof(NativeSpriteEntryViewF920, storedHeightAt8)==8)?1:-1];
typedef char EntryF920MetadataOffset[(offsetof(NativeSpriteEntryViewF920, metadataAt0C)==12)?1:-1];
typedef char EntryF920PaletteOffset[(offsetof(NativeSpriteEntryViewF920, paletteFlagAt28)==0x28)?1:-1];
