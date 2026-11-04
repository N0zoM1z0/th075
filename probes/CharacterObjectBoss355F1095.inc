// F1095: independent Japanese original game action 0x355,
// 00514FE8..005154ED = 1285 original CODE B /270 native x86.
// One authentic state inside the still-NONEXACT 81KB CharacterObject.
case 0x355: {
    if (PARENT_FIELD(signed short,0x60)>0x45 &&
        PARENT_FIELD(signed short,0x60)<0x96) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<10;++shot) {
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
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=0.0f;
        SELF_FIELD(float,0x20)=0.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        F1037_MOTION(this).xMotion=10.0f;
        F1037_MOTION(this).yMotion=6.0f;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0xDA)=0;
        SELF_FIELD(signed short,0xDC)=0;
        SELF_FIELD(signed short,0x80)=0;
        SELF_FIELD(int,0x7C)=0;
    }
    if (SELF_FIELD(float,0x1C)<g_F1095_ScaleCeilingAt00659898) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_SpeedScaleAt006590B4;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1057_SpeedScaleAt006590B4;
    } else if (SELF_FIELD(signed short,0xD8)==0) {
        SELF_FIELD(signed short,0x80)=10;
        ++SELF_FIELD(signed short,0xD8);
    }
    if (F1037_MOTION(this).xMotion>g_F1059_ScaleRatioAt00657478) {
        F1037_MOTION(this).xMotion=F1037_MOTION(this).xMotion-g_F1059_ScaleRatioAt00657478;
        if (F1037_MOTION(this).xMotion<g_F1059_ScaleRatioAt00657478)
            F1037_MOTION(this).xMotion=0.5f;
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
    if (SELF_FIELD(int,0x7C)==4 && SELF_FIELD(signed short,0x80)>0)
        SELF_FIELD(int,0x7C)=0;
    if (SELF_FIELD(int,0x7C)!=0 && F1024_PHASE(this).stageAt62<0x1F) {
        SetAuxActionAt0040FB40(0x1F);
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        SELF_FIELD(signed short,0xDC)=2;
    }
    if (F1024_PHASE(this).stageAt62==0x1F) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1051_ScaleStepAt00658348;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1051_ScaleStepAt00658348;
        SELF_FIELD(unsigned char,0x11)=unsigned char(SELF_FIELD(unsigned char,0x11)-25);
    }
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==0x1F && F1024_PHASE(this).frameAt64==0) {
        if (SELF_FIELD(signed short,0xDA)<6) {
            ++SELF_FIELD(signed short,0xDA);
            SetAuxActionAt0040FB40(1);
            return;
        }
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        SELF_FIELD(signed short,0xDC)=2;
    }
    return;
}
