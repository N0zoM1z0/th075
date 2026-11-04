// F1046: Original 0050AC27..0050AD46 action 0x322, 287 native CODE
// bytes / 56 x86. True game behavior, NOT an independent callable.
case 0x322: {
    if (SELF_FIELD(int,0x7C) == 5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(int,0x7C) == 6) {
        SELF_FIELD(int,0x7C) = 0;
        SELF_FIELD(signed short,0x80) = 1;
    }
    if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(signed short,0x80) = 1;
        SELF_FIELD(int,0x7C) = 0;
        SELF_FIELD(signed short,0xD8) = 0;
        SELF_FIELD(float,0x1C) = 1.0f;
        SELF_FIELD(float,0x20) = 1.0f;
        SELF_FIELD(unsigned char,0x11) = 0xFF;
        SELF_FIELD(unsigned char,0x12) = 0xFF;
        SELF_FIELD(unsigned char,0x13) = 0xFF;
        SELF_FIELD(unsigned char,0x14) = 0xFF;
        SELF_FIELD(float,0x30) = 15.0f;
    }
    if (GetNativeActionAt0040FA30() == SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
