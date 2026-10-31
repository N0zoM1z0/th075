#pragma once
#include <windows.h>
#include <stddef.h>

// The original two native allocations both construct/destruct one complete
// 44-byte texture slot VALUE. The original element's internal fields remain
// unknown: physicalWords describes observed occupied storage, not a
// reconstructed historical vendor/private element class.
struct NativeTextureElementF769 {
    DWORD physicalWords[11];
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
