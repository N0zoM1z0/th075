// F1054: Real native action 0x345, original 155B/35 x86; one 81KB parent.
case 0x345: {
    if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0) {
        SetNativeMotionAt0040FBB0(0,0,0);
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
