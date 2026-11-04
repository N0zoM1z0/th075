// F1108/F1109: five separate original Japanese native actions 0x360..0x364.
// Source is one genuine repeated game-logic family, instantiated at five
// distinct physical PE switch entries inside ONE NONEXACT 81KB callable.
// Original each 206 x86, but native CODE width is 952/952/951/964/964 B.
// NEXT_ID must retain 0x365/0x366/0x367/0x368/0x369 respectively.
case F1108_CASE: {
    if (PARENT_FIELD(signed short,0x60)>0x31 &&
        PARENT_FIELD(signed short,0x60)<0x96 &&
        SELF_FIELD(signed short,0x62)<2) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<2;++shot)
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0 &&
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
    if (SELF_FIELD(signed short,0x62)==0) {
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),
            float(SELF_FIELD(signed short,0xD8)));
        --SELF_FIELD(signed short,0xD8);
        if (SELF_FIELD(signed short,0xD8)<0)
            SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1068_ActionSpeedAt00657878;
    }
    if (F1037_POSITION(this).xPosition>g_F1101_RightAt00659424 ||
        F1037_POSITION(this).xPosition<g_F1076_LeftAt006595EC ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1076_LeftAt006595EC) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        PARENT_FIELD(unsigned int,0x314)=SELF_FIELD(unsigned int,0xC8);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            F1108_NEXT_ID,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
        NativeParentExpiredAt0045B830();
    }
    return;
}
