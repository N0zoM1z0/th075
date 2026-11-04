// F1120: original Japanese 0x38B, PE 0051C3ED..0051C82D:
// 1,088 original CODE B /226 native x86 in ONE NONEXACT 81KB Boss.
case 0x38B: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=0.1f;
        SELF_FIELD(float,0x20)=0.1f;
        SELF_FIELD(unsigned char,0x11)=0;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0x80;
        F1037_MOTION(this).xMotion=20.0f;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0xDA)=0;
        SELF_FIELD(signed short,0xDC)=0;
        SELF_FIELD(signed short,0x80)=0;
        SELF_FIELD(int,0x7C)=0;
    }
    if (SELF_FIELD(signed short,0xDC)==0) {
        F1037_MOTION(this).xMotion=F1037_MOTION(this).xMotion-g_F1120_XBrakingAt00659090;
        if (F1037_MOTION(this).xMotion<g_F1051_ScaleCeilingAt0065747C) {
            F1037_MOTION(this).xMotion=1.0f;
            SELF_FIELD(signed short,0xDC)=1;
        }
    }
    if (SELF_FIELD(signed short,0xDC)>0 && SELF_FIELD(signed short,0xDC)<30)
        ++SELF_FIELD(signed short,0xDC);
    if (SELF_FIELD(signed short,0xDC)>29)
        F1037_MOTION(this).xMotion=(*(&F1037_MOTION(this).xMotion))+g_F1059_ScaleRatioAt00657478;
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
    if (SELF_FIELD(int,0x7C)==6) {
        SELF_FIELD(int,0x7C)=0;
        ++SELF_FIELD(signed short,0x80);
    }
    if (SELF_FIELD(int,0x7C)!=0) {
        ++SELF_FIELD(signed short,0xD8);
        if (SELF_FIELD(signed short,0xD8)>5) {
            SELF_FIELD(signed short,0xD8)=0;
            SELF_FIELD(int,0x7C)=0;
        }
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (SELF_FIELD(signed short,0x80)==0 && F1024_PHASE(this).stageAt62<0x17 && SELF_FIELD(signed short,0xD8)>0) {
        SetAuxActionAt0040FB40(0x17);
        return;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0x17 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
