// F1083: real Japanese original 00512BA7..00512D43, 412 CODE B/85 x86.
// Actual 0x34B animation/ground physics inside the ONE nonexact 81KB Boss.
case 0x34B: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0x80)=99;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=0;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
    }
    SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1057_SpeedScaleAt006590B4;
    if (F1037_POSITION(this).yPosition>g_F1083_YBoundAt00658E80) {
        NativeParentExpiredAt0045B830();
        return;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==15 && F1024_PHASE(this).frameAt64==0)
        F1037_MOTION(this).yMotion=-40.0f;
    return;
}
