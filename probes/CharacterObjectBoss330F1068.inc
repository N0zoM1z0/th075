// F1068: native real Japanese original 0050D17A..0050D53A,
// 960 original CODE bytes /209 x86. One case in still-NONEXACT
// original 81KB CharacterObject::Advance; not an independent callable.
case 0x330: {
    if (PARENT_FIELD(signed short,0x60)>0x45 &&
        PARENT_FIELD(signed short,0x60)<0x96 &&
        F1024_PHASE(this).stageAt62<3) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<5;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48),1,1);
        }
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48),1,1);
        }
        return;
    }
    if (SELF_FIELD(int,0x7C)==6) {
        ++SELF_FIELD(signed short,0x80);
        SELF_FIELD(int,0x7C)=0;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,60.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(float,0x54)=26.5f;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(3);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x345, SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
    }
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (F1024_PHASE(this).stageAt62==1) {
        SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1068_ActionSpeedAt00657878;
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1051_ScaleCeilingAt0065747C;
        if (F1037_MOTION(this).yMotion<g_F1044_GroundAt0065782C)
            F1037_MOTION(this).yMotion=0.0f;
    }
    if (F1024_PHASE(this).stageAt62==2) {
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1059_ScaleRatioAt00657478;
        F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
        // Real native 0x330 TEST AH,0x41; JNP enters impact handling
        // directly, then checks collision status 0/6 on the other path.
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C ||
            (SELF_FIELD(int,0x7C)!=0 && SELF_FIELD(int,0x7C)!=6)) {
            F1037_MOTION(this).yMotion=0.0f;
            SetAuxActionAt0040FB40(3);
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(5);
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(4);
        F1037_MOTION(this).xMotion=-20.0f;
        SELF_FIELD(float,0x30)=0.0f;
    }
    return;
}
