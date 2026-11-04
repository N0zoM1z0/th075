// F1065/F1066: independent native actions 0x333, 0x334, and 0x336.
// Initial signed float at the real motion call is +30.0 for 333/334,
// -30.0 for 336; all three keep the authentic native game calls.
// F1065: independent native actions 0x333 and 0x334, physical original
// 0050D929..0050DDCF and 0050DDCF..0050E274, 249 x86 each.
// Shared C++ gameplay grammar, distinct native switch entries, never two
// original independent callable functions (ONE nonexact 81KB parent).
case F1065_ACTION: {
    if (PARENT_FIELD(signed short,0x60)>0x45 &&
        PARENT_FIELD(signed short,0x60)<0x96 &&
        SELF_FIELD(signed short,0x62)<0x17) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<8;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48), 1, 1);
        }
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48), 1, 1);
        }
        return;
    }
    if (SELF_FIELD(int,0x7C)==5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(float,0x1C)=0.1f;
        SELF_FIELD(float,0x20)=0.1f;
        SELF_FIELD(unsigned char,0x11)=0;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0xDA)=0;
        SELF_FIELD(signed short,0xDC)=0xAA;
        SELF_FIELD(signed short,0x80)=0;
        SELF_FIELD(int,0x7C)=0;
    }
    SetNativeTwoFloatsAt0040FB70(F1066_INITIAL_ANGLE,
        float(SELF_FIELD(signed short,0xDC))*g_F1057_SpeedScaleAt006590B4);
    SELF_FIELD(signed short,0xDC)=short(SELF_FIELD(signed short,0xDC)-6);
    if (SELF_FIELD(signed short,0xDC)<20)
        SELF_FIELD(signed short,0xDC)=20;
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
            SELF_FIELD(signed short,0x80)=10;
        }
    }
    if ((SELF_FIELD(int,0x7C)==6 || SELF_FIELD(int,0x7C)==4) &&
        SELF_FIELD(signed short,0x80)>0)
        SELF_FIELD(int,0x7C)=0;
    if (SELF_FIELD(int,0x7C)!=0)
        ++SELF_FIELD(signed short,0xD8);
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion + F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (SELF_FIELD(signed short,0x80)==0 &&
        SELF_FIELD(signed short,0x62)<0x17 && SELF_FIELD(signed short,0xD8)>0) {
        SetAuxActionAt0040FB40(0x17);
        return;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0x17 && SELF_FIELD(signed short,0x64)==0 &&
        SELF_FIELD(signed short,0xDA)<0) {
        SetAuxActionAt0040FB40(1);
        ++SELF_FIELD(signed short,0xDA);
    }
    return;
}
