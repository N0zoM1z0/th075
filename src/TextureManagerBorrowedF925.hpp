#pragma once
#include <windows.h>
#include <stddef.h>

// The native vector stores complete 44-byte entries. The bitmap methods
// receive the entry address and access the first group of fields.
struct NativeTextureElementF769 {
    BYTE uploadFormat;
    BYTE unknown01[3];
    int storedWidth;
    int storedHeight;
    int storedStride;
    DWORD encodedSize;
    WORD* palette;
    BYTE ownsPalette;
    BYTE unknown19[3];
    BYTE* pixels;
    BYTE unknown20[8];
    BYTE paletteFlag;
    BYTE unknown29[3];
    NativeTextureElementF769();
    ~NativeTextureElementF769();
};
typedef char NativeTextureElementSizeF925[(sizeof(NativeTextureElementF769)==44)?1:-1];

// Borrowed *receiver tail* view: native mode is a byte at this+0x4C in
// both complete game allocator functions. Never instantiate/embed this
// 0x4D-byte borrowed view as a complete texture-manager object.
struct NativeTextureManagerModeF925 {
    unsigned char unknownBeforeKind[0x4C];
    unsigned char allocationKindAt4C;
};
typedef char NativeTextureManagerModeOffsetF925[
    (offsetof(NativeTextureManagerModeF925, allocationKindAt4C)==0x4C)?1:-1];
