// Original 0050CE97..0050CF7A: real action 0x32D (227B/50 x86).
case 0x32D: {
    if (PARENT_FIELD(signed short,0x60) == 0x12D) {
        SELF_FIELD(unsigned int,0x44) = PARENT_FIELD(unsigned int,0x44);
        SELF_FIELD(unsigned int,0x48) = PARENT_FIELD(unsigned int,0x48);
    }
    if (SELF_FIELD(signed short,0x62) == 0 && SELF_FIELD(signed short,0x64) == 0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(float,0x1C) = 1.5f;
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
