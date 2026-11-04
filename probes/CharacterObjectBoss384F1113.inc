// F1113: genuine original TH075 Japanese action 0x384 inside ONE still
// NONEXACT CharacterObject Advance. PE 0051AAFD..0051AFF0: 1267B/277 x86.
case 0x384: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(float,0x1C)=0.0f;
        SELF_FIELD(float,0x20)=0.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
    }
    if (SELF_FIELD(signed short,0x62)<6) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1051_ScaleStepAt00658348;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1051_ScaleStepAt00658348;
        if (SELF_FIELD(float,0x1C)>g_F1057_NudgeAt00657480)
            SELF_FIELD(float,0x1C)=2.0f;
        if (SELF_FIELD(float,0x20)>g_F1057_NudgeAt00657480)
            SELF_FIELD(float,0x20)=2.0f;
    }
    if (SELF_FIELD(signed short,0x62)>5) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            F1037_POSITION(this).yPosition=0.0f;
            F1037_MOTION(this).yMotion=0.0f;
            F1037_MOTION(this).xMotion=0.0f;
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(11);
            SetNativeActionAt0040FAC0(0x385);
            if (g_F1113_DifficultyAt006714D0>0) {
                PARENT_FIELD(float,0x314)=3.0f;
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x38E,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x38E,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),-1,1);
            }
            if (g_F1113_DifficultyAt006714D0>1) {
                    PARENT_FIELD(float,0x314)=6.0f;
                    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                        0x38E,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
                    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                        0x38E,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),-1,1);
            }
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x347,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),SELF_FIELD(signed char,0x66),1);
                for (int shot=0;shot<15;++shot)
                    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                        0x33A,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),SELF_FIELD(signed char,0x66),1);
            reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
            return;
        }
    }
    if (PARENT_FIELD(signed short,0x62)==9 && SELF_FIELD(signed short,0x62)<6) {
        SetAuxActionAt0040FB40(SELF_FIELD(signed short,0x62)+5);
        F1037_MOTION(this).xMotion=float(SELF_FIELD(signed char,0x66)) *
            (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition)/g_F1113_DivisorAt0065988C;
        if (F1037_MOTION(this).xMotion<g_F1051_TrajectoryLowerAt00658290)
            F1037_MOTION(this).xMotion=6.0f;
        F1037_MOTION(this).yMotion=-12.0f;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        SetAuxActionAt0040FB40(6);
        return;
    }
    if (SELF_FIELD(signed short,0x62)==6 && SELF_FIELD(signed short,0x64)==0)
        SetAuxActionAt0040FB40(1);
    return;
}
