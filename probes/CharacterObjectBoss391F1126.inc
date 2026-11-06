// F1126 genuine Japanese 0x391 at original PE 0051CF28..0051D413:
// 1,259 native CODE B /277 x86 in one incomplete 81KB Boss.
case 0x391: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=0.0f;
        SELF_FIELD(float,0x20)=0.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        F1037_MOTION(this).xMotion=3.0f;
        F1037_MOTION(this).yMotion=g_F1095_UpperYAt00659890-float(RandomBoundaryAt00455580(0,9));
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0xDA)=0;
        SELF_FIELD(signed short,0xDC)=0;
        SELF_FIELD(signed short,0x80)=0;
        SELF_FIELD(int,0x7C)=0;
    }
    if (SELF_FIELD(float,0x1C)<g_F1051_ScaleCeilingAt0065747C) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_SpeedScaleAt006590B4;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1057_SpeedScaleAt006590B4;
    } else {
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
    }
    if (SELF_FIELD(signed short,0xDC)==0) {
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1062_ScaleStepAt006583F8;
        if (F1037_MOTION(this).yMotion<g_F1095_LowerYAt00659894)
            SELF_FIELD(signed short,0xDC)=1;
    }
    if (SELF_FIELD(signed short,0xDC)==1) {
        F1037_MOTION(this).yMotion=(*(&F1037_MOTION(this).yMotion))+g_F1062_ScaleStepAt006583F8;
        if (F1037_MOTION(this).yMotion>g_F1095_UpperYAt00659890)
            SELF_FIELD(signed short,0xDC)=0;
    }
    if ((*(&SELF_FIELD(float,0x1C)))==g_F1051_ScaleCeilingAt0065747C &&
        g_F1113_DifficultyAt006714D0>1) {
        if (F1037_MOTION(this).xMotion>g_F1044_GroundAt0065782C &&
            F1037_POSITION(this).xPosition>g_F1083_YBoundAt00658E80) {
            F1037_MOTION(this).xMotion=-F1037_MOTION(this).xMotion;
        }
        if (F1037_MOTION(this).xMotion<g_F1044_GroundAt0065782C &&
            F1037_POSITION(this).xPosition<g_F1044_GroundAt0065782C)
            F1037_MOTION(this).xMotion=-F1037_MOTION(this).xMotion;
    }
    if (SELF_FIELD(signed short,0xDA)==0 &&
        (*(&SELF_FIELD(float,0x1C)))==g_F1051_ScaleCeilingAt0065747C) {
        if (F1037_POSITION(PARENT_GRANDPARENT).yPosition<F1037_POSITION(this).yPosition &&
            F1115_AbsFloatAt00412D90(F1037_POSITION(this).xPosition-
                F1037_POSITION(PARENT_GRANDPARENT).xPosition)<g_F1126_XDistanceAt00657850) {
            SELF_FIELD(signed short,0xDA)=1;
            F1037_MOTION(this).xMotion=0.0f;
            F1037_MOTION(this).yMotion=-30.0f;
            SELF_FIELD(float,0x1C)=0.1f;
            SELF_FIELD(float,0x20)=1.0f;
        }
    }
    if (SELF_FIELD(signed short,0xDA)==1) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            NativeParentExpiredAt0045B830();
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x392,SELF_FIELD(unsigned int,0x44),0,
                SELF_FIELD(signed char,0x66),1);
            return;
        }
    }
    if (F1037_POSITION(this).xPosition>g_F1126_RightAt00659884 ||
        F1037_POSITION(this).xPosition<g_F1126_LeftAt006595E4) {
        NativeParentExpiredAt0045B830();
        return;
    }
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==0x1F && F1024_PHASE(this).frameAt64==0) {
        SetAuxActionAt0040FB40(1);
        return;
    }
    return;
}
