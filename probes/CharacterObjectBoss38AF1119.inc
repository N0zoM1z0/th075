// F1119: real original TH075 game action 0x38A at PE
// 0051BFE2..0051C3ED, 1035 native CODE B/226 x86. Whole 81KB NONEXACT.
case 0x38A: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
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
    if (F1024_PHASE(this).stageAt62<6) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1051_ScaleStepAt00658348;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1051_ScaleStepAt00658348;
        if (SELF_FIELD(float,0x1C)>g_F1051_ScaleCeilingAt0065747C)
            SELF_FIELD(float,0x1C)=2.0f;
        if (SELF_FIELD(float,0x20)>g_F1051_ScaleCeilingAt0065747C)
            SELF_FIELD(float,0x20)=2.0f;
    }
    if (F1024_PHASE(this).stageAt62>5) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            F1037_POSITION(this).yPosition=0.0f;
            F1037_MOTION(this).yMotion=0.0f;
            F1037_MOTION(this).xMotion=0.0f;
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(11);
            SetNativeActionAt0040FAC0(0x385);
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x347,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),SELF_FIELD(signed char,0x66),1);
            int shot;
            for (shot=0;shot<15;++shot)
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x33A,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),SELF_FIELD(signed char,0x66),1);
            for (shot=0;shot<15;++shot)
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x389,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),SELF_FIELD(signed char,0x66),1);
            reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
            return;
        }
    }
    if (PARENT_FIELD(signed short,0x62)==9 && F1024_PHASE(this).stageAt62<6) {
        SetAuxActionAt0040FB40(F1024_PHASE(this).stageAt62+5);
        F1037_MOTION(this).xMotion=float(RandomBoundaryAt00455580(0,30)+10);
        F1037_MOTION(this).yMotion=-20.0f;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        SetAuxActionAt0040FB40(6);
        return;
    }
    if (F1024_PHASE(this).stageAt62==6 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
