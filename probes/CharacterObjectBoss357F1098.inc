// F1098: genuine Japanese original 005159A0..00515C0E,
// 622 original CODE B /131 x86, one interior of NONEXACT 81KB boss.
case 0x357: {
    if (PARENT_FIELD(signed short,0x60)>0x31 &&
        PARENT_FIELD(signed short,0x60)<0x96 &&
        SELF_FIELD(signed short,0x62)<0x17) {
        SetAuxActionAt0040FB40(0x17);
        return;
    }
    if (PARENT_FIELD(signed short,0x60)==0x189 && SELF_FIELD(signed short,0x62)<0x17) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(SELF_FIELD(signed char,0x66)*120);
        F1037_POSITION(this).yPosition=120.0f;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=0.1f;
        SELF_FIELD(float,0x20)=0.1f;
        SELF_FIELD(unsigned char,0x11)=0;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0xDA)=0;
    }
    if (SELF_FIELD(signed short,0xD8)==0) {
        if (SELF_FIELD(float,0x1C)<g_F1051_ScaleCeilingAt0065747C) {
            SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_SpeedScaleAt006590B4;
            SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1057_SpeedScaleAt006590B4;
            SELF_FIELD(unsigned char,0x11)=unsigned char(SELF_FIELD(unsigned char,0x11)+25);
        } else {
            SELF_FIELD(float,0x1C)=1.0f;
            SELF_FIELD(float,0x20)=1.0f;
            SELF_FIELD(unsigned char,0x11)=0xFF;
        }
        if (SELF_FIELD(unsigned char,0x11)==0xFF && SELF_FIELD(signed short,0xD8)==0) {
            ++SELF_FIELD(signed short,0xD8);
            SELF_FIELD(signed short,0x80)=1;
        }
    }
    if (PARENT_FIELD(signed short,0x82)==0 &&
        GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    return;
}
