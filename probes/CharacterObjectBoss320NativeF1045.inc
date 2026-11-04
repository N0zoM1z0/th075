// Native 0050A658..0050A80F (439 original CODE B, 91 x86) is action 0x320
// of the ONE, still NONEXACT 81KB CharacterObject Advance. This body is a
// natural C++ source reconstruction, not separately callable CODE or ASM.
case 0x320: {
    // The actual original parent chain is this+E4. Its native action and
    // stage fields gate a real helper call before any local motion update.
    if (PARENT_FIELD(signed short,0x60) != 0x2BC ||
        (PARENT_FIELD(signed short,0x60) == 0x2BC &&
         PARENT_FIELD(signed short,0x62) > 12)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    SELF_FIELD(float,0x44) = F1037_POSITION(PARENT).xPosition + float(SELF_FIELD(signed char,0x66) * 66);
    if (SELF_FIELD(signed short,0x62) == 0 &&
        SELF_FIELD(signed short,0x64) == 0) {
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
        SELF_FIELD(float,0x54) = 10.0f;
    }
    F1037_POSITION(this).yPosition = F1037_POSITION(this).yPosition + F1037_MOTION(this).yMotion;
    SELF_FIELD(float,0x54) = SELF_FIELD(float,0x54) - g_F1044_GravityAt0065747C;
    if (SELF_FIELD(float,0x54) < g_F1044_GroundAt0065782C)
        SELF_FIELD(float,0x54) = 0.0f;
    if (GetNativeActionAt0040FA30() == SELF_FIELD(signed short,0x70))
        SetAuxActionAt0040FB40(1);
    return;
}
