// Pinned original native 0050CD7A..0050CE97, action 0x32C, 285B/63 x86.
// This remains an INNER state in one nonexact 81KB CharacterObject function.
case 0x32C: {
    SELF_FIELD(unsigned char,0x66) = PARENT_FIELD(unsigned char,0x66);
    if (PARENT_FIELD(signed short,0x60) == 0x131) {
        SELF_FIELD(unsigned int,0x44) = PARENT_FIELD(unsigned int,0x44);
        SELF_FIELD(unsigned int,0x48) = PARENT_FIELD(unsigned int,0x48);
    } else {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62 == 0 &&
        F1024_PHASE(this).frameAt64 == 0 &&
        SELF_FIELD(signed short,0xD8) == 0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(float,0x1C) = 1.0f;
        SELF_FIELD(float,0x20) = 1.0f;
        SELF_FIELD(unsigned char,0x11) = 0xFF;
        SELF_FIELD(unsigned char,0x12) = 0xFF;
        SELF_FIELD(unsigned char,0x13) = 0xFF;
        SELF_FIELD(unsigned char,0x14) = 0xFF;
    }
    if (GetNativeActionAt0040FA30() == SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
