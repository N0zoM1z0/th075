// F1125 original Japanese action 0x390 at 0051CB4A..0051CF28:
// 990 native CODE B /212 x86 inside ONE still-NONEXACT 81KB boss.
case 0x390: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0xD8)=0;
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),
            float(SELF_FIELD(signed short,0xD8))*g_F1057_SpeedScaleAt006590B4+g_F1085_LastYAt006592A4);
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
    if (F1024_PHASE(this).stageAt62<2) {
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),
            float(SELF_FIELD(signed short,0xD8))*g_F1057_SpeedScaleAt006590B4+g_F1085_LastYAt006592A4);
        if (SELF_FIELD(float,0x1C)<g_F1051_ScaleCeilingAt0065747C) {
            SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_SpeedScaleAt006590B4;
            SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1057_SpeedScaleAt006590B4;
        }
    }
    if (SELF_FIELD(int,0x7C)!=0 && F1024_PHASE(this).stageAt62==1) {
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
        F1037_POSITION(this).yPosition>g_F1125_YUpperAt00657884 ||
        F1037_POSITION(this).yPosition<g_F1101_LeftAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62>1) {
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
