// F1130: original Japanese 0x3E5 at 0051E01F..0051E215:
// 502 native original CODE B /96 x86 inside ONE nonexact 81KB Boss.
case 0x3E5: {
    SELF_FIELD(unsigned int,0x44)=PARENT_FIELD(unsigned int,0x44);
    F1037_POSITION(this).yPosition=0.0f;
    SELF_FIELD(signed short,0x8A)=1;
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=3.0f;
        SELF_FIELD(float,0x20)=3.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0x1A)=0x4E2;
        SELF_FIELD(float,0x2C)=0.0f;
        SELF_FIELD(float,0x30)=0.0f;
        SELF_FIELD(float,0x28)=-80.0f;
        SELF_FIELD(signed short,0xD8)=PARENT_FIELD(signed short,0x3A0);
    }
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    SELF_FIELD(float,0x1C)=float(PARENT_FIELD(signed short,0x3A0))/SELF_FIELD(signed short,0xD8)*2.0f;
    SELF_FIELD(float,0x20)=float(PARENT_FIELD(signed short,0x3A0))/SELF_FIELD(signed short,0xD8)*2.0f;
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1051_ScaleCeilingAt0065747C;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        SetAuxActionAt0040FB40(10);
        return;
    }
    return;
}
