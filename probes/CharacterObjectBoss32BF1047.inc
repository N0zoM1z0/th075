// Original 0050CCC3..0050CD7A: one actual action 0x32B (183B/39 x86).
case 0x32B: {
    if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(signed short,0x80) = 1;
        SELF_FIELD(int,0x7C) = 0;
        SELF_FIELD(float,0x1C) = 2.0f;
        SELF_FIELD(float,0x20) = 2.0f;
        SELF_FIELD(unsigned char,0x11) = 0xFF;
        SELF_FIELD(unsigned char,0x12) = 0xFF;
        SELF_FIELD(unsigned char,0x13) = 0xFF;
        SELF_FIELD(unsigned char,0x14) = 0xFF;
    }
    if (GetNativeActionAt0040FA30() == SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
