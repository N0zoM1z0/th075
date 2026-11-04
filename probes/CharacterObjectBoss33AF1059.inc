// F1059 genuine Japanese native 0050EF5F..0050F25A (763 CODE B /168 x86).
// This is one INNER action in the ONE still-NONEXACT 81KB CharacterObject.
case 0x33A: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0xD8)=short(RandomBoundaryAt00455580(0,13)+12);
        SELF_FIELD(signed short,0xDA)=short(RandomBoundaryAt00455580(0,0x167));
        SELF_FIELD(float,0x1C)=float(RandomBoundaryAt00455580(0,30)+20)*g_F1059_ScaleBaseAt006590B4;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x1C)*g_F1059_ScaleRatioAt00657478;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
    }
    --SELF_FIELD(signed short,0xD8);
    if (SELF_FIELD(signed short,0xD8)<4)
        SELF_FIELD(signed short,0xD8)=4;
    SetNativeTwoFloatsAt0040FB70(float(SELF_FIELD(signed short,0xDA)),float(SELF_FIELD(signed short,0xD8)));
    SELF_FIELD(float,0x30)=F1057_FloatAtan2At00483300(
        F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion + F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)*g_F1059_ScaleFadeAt006598A8;
    SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)*g_F1059_ScaleFadeAt006598A8;
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1059_UpperBoundAt00657884 ||
        F1037_POSITION(this).yPosition<g_F1059_LowerBoundAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62>1) {
        if (SELF_FIELD(unsigned char,0x11)>=10)
            SELF_FIELD(unsigned char,0x11)-=10;
        else
            SELF_FIELD(unsigned char,0x11)=0;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
