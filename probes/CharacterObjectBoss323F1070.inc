// F1070: original Japanese PE 0050AD46..0050B150, 1034 CODE B /220 x86.
// Genuine gameplay inside ONE nonexact 81KB CharacterObject advance.
case 0x323: {
    if (SELF_FIELD(int,0x7C)==5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0xD8)=0;
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),
            float(SELF_FIELD(signed short,0xD8))*g_F1057_SpeedScaleAt006590B4+
            g_F1070_InitSpeedAt00657858);
        SELF_FIELD(float,0x1C)=0.1f;
        SELF_FIELD(float,0x20)=0.1f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(float,0x30)=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
    }
    ++SELF_FIELD(signed short,0xD8);
    if (SELF_FIELD(signed short,0x62)<2) {
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),
            float(SELF_FIELD(signed short,0xD8))*g_F1057_SpeedScaleAt006590B4+
            g_F1070_AnimSpeedAt006592A4);
        if (SELF_FIELD(float,0x1C)<g_F1051_ScaleCeilingAt0065747C) {
            SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_SpeedScaleAt006590B4;
            SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1057_SpeedScaleAt006590B4;
        }
    }
    if (SELF_FIELD(int,0x7C)==6) {
        SELF_FIELD(int,0x7C)=0;
        ++SELF_FIELD(signed short,0x80);
    }
    if (SELF_FIELD(int,0x7C)!=0 && SELF_FIELD(signed short,0x62)==1) {
        SetAuxActionAt0040FB40(2);
        SELF_FIELD(float,0x1C)=4.0f;
        SELF_FIELD(float,0x20)=4.0f;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        return;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1059_UpperBoundAt00657884 ||
        F1037_POSITION(this).yPosition<g_F1059_LowerBoundAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)>1) {
        if (SELF_FIELD(unsigned char,0x11)>=25) {
            SELF_FIELD(unsigned char,0x11)-=25;
            SELF_FIELD(unsigned char,0x12)-=25;
            SELF_FIELD(unsigned char,0x13)-=25;
            SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)*g_F1070_FadeScaleAt00659454;
            SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)*g_F1070_FadeScaleAt00659454;
        } else {
            SELF_FIELD(unsigned char,0x11)=0;
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
