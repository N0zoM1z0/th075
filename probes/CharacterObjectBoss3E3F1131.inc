// F1131: genuine Japanese native 0x3E3 at PE 0051D70F..0051DAE8,
// original 985 CODE B/200 x86 inside ONE nonexact 81KB game callable.
case 0x3E3: {
    SELF_FIELD(signed char,0x66)=1;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=-1.0f;
        SELF_FIELD(signed short,0xD8)=short(RandomBoundaryAt00455580(0,360)-180);
        SELF_FIELD(signed short,0xDA)=15;
    }
    if (F1024_PHASE(this).stageAt62==0) {
        --SELF_FIELD(signed short,0xDA);
        if (SELF_FIELD(signed short,0xDA)<3)
            SELF_FIELD(signed short,0xDA)=3;
    }
    SetNativeTwoFloatsAt0040FB70(float(SELF_FIELD(signed short,0xD8)),
        float(SELF_FIELD(signed short,0xDA))*g_F1120_XBrakingAt00659090);
    if (F1024_PHASE(this).stageAt62==1) {
        SELF_FIELD(signed short,0xD8)=short(F1057_FloatAtan2At00483300(
            (*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1057_YOffsetAt00657888-F1037_POSITION(this).yPosition,
            F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition) /
            g_F1057_AngleDivAt00657828);
        SetNativeTwoFloatsAt0040FB70(float(SELF_FIELD(signed short,0xD8)),20.0f);
        if (F1037_POSITION(this).xPosition-F1037_POSITION(PARENT_GRANDPARENT).xPosition<g_F1115_DistanceAt0065786C &&
            F1037_POSITION(this).xPosition-F1037_POSITION(PARENT_GRANDPARENT).xPosition>g_F1131_LeftHitAt00659230 &&
            F1037_POSITION(this).yPosition-F1037_POSITION(PARENT_GRANDPARENT).yPosition<g_F1131_TopHitAt006590A8 &&
            F1037_POSITION(this).yPosition-F1037_POSITION(PARENT_GRANDPARENT).yPosition>g_F1131_BottomHitAt00658268) {
            NativeParentExpiredAt0045B830();
            if (PARENT_GRANDPARENT_FIELD(signed char,0x366)<2)
                ++PARENT_GRANDPARENT_FIELD(signed char,0x366);
            else {
                PARENT_GRANDPARENT_FIELD(int,0x2D0)+=0x4E20;
                NativeHitAt0045B860(0x2E);
                return;
            }
        }
    }
    F1037_POSITION(this).xPosition=F1037_POSITION(this).xPosition+F1037_MOTION(this).xMotion;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        SetAuxActionAt0040FB40(1);
    return;
}
