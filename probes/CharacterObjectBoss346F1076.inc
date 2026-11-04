// F1076: genuine Japanese native 00511D25..005123B9 (1684B/365 x86).
// Real 0x346 source inside ONE original 81KB CharacterObject, NONEXACT.
case 0x346: {
    if (SELF_FIELD(int,0x7C)==5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (PARENT_FIELD(signed short,0x60)>0x31 &&
        PARENT_FIELD(signed short,0x60)<0x96 &&
        F1024_PHASE(this).stageAt62<5) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<3;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0 &&
        SELF_FIELD(signed short,0xD8)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(signed short,0xD8)=15;
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),
                                    float(SELF_FIELD(signed short,0xD8)));
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (F1024_PHASE(this).stageAt62==1) {
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),
                                    float(SELF_FIELD(signed short,0xD8)));
        --SELF_FIELD(signed short,0xD8);
        if (SELF_FIELD(signed short,0xD8)<0)
            SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1076_AngleNudgeAt00658294;
    }
    if (F1024_PHASE(this).stageAt62==2) {
        ++SELF_FIELD(signed short,0xD8);
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_SpeedScaleAt006590B4;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)*g_F1076_ScaleMulAt00659450;
        SetNativeTwoFloatsAt0040FB70(float(SELF_FIELD(signed short,0xDC)),
                                     float(SELF_FIELD(signed short,0xD8)));
        SELF_FIELD(float,0x30)=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
        PARENT_FIELD(float,0x310)=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
    }
    if (F1024_PHASE(this).stageAt62==3) {
        ++SELF_FIELD(signed short,0xD8);
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_SpeedScaleAt006590B4;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)*g_F1076_ScaleMulAt00659450;
        SetNativeTwoFloatsAt0040FB70(float(SELF_FIELD(signed short,0xDC)),
                                     float(SELF_FIELD(signed short,0xD8)));
        SELF_FIELD(float,0x30)=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
        if (SELF_FIELD(unsigned char,0x11)>10)
            SELF_FIELD(unsigned char,0x11)-=10;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (SELF_FIELD(int,0x7C)!=2 && SELF_FIELD(int,0x7C)==4 && F1024_PHASE(this).stageAt62==2) {
        SetAuxActionAt0040FB40(3);
        return;
    }
    if (F1037_POSITION(this).xPosition>g_F1076_RightAt00659424 ||
        F1037_POSITION(this).xPosition<g_F1076_LeftAt006595EC ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1076_LeftAt006595EC) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0) {
        SELF_FIELD(signed short,0xDC)=short(F1057_FloatAtan2At00483300(
          ((*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1076_TargetYOffsetAt00658398-F1037_POSITION(this).yPosition),
          (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition)*int(SELF_FIELD(signed char,0x66))) /
          g_F1057_AngleDivAt00657828);
    }
    if (F1024_PHASE(this).stageAt62==3 && F1024_PHASE(this).frameAt64==0)
        NativeParentExpiredAt0045B830();
    return;
}
