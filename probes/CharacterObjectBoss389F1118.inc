// F1118: genuine Japanese 0x389 action, original PE
// 0051BB8B..0051BFE2: 1111 CODE B/238 x86, within ONE
// still-NONEXACT 81KB CharacterObject::Advance.
case 0x389: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(int,0x7C)==5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=short(RandomBoundaryAt00455580(0,300)+200);
        SELF_FIELD(signed short,0xDA)=short(RandomBoundaryAt00455580(0,50)+45);
        SELF_FIELD(signed short,0xDC)=short(RandomBoundaryAt00455580(0,15)+5);
        SetNativeTwoFloatsAt0040FB70(
            float(SELF_FIELD(signed short,0xDA)),
            float(SELF_FIELD(signed short,0xD8))*g_F1057_SpeedScaleAt006590B4);
    }
    if (F1024_PHASE(this).stageAt62<=1) {
        SetNativeTwoFloatsAt0040FB70(
            float(SELF_FIELD(signed short,0xDA)),
            float(SELF_FIELD(signed short,0xD8))*g_F1057_SpeedScaleAt006590B4);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x33C,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
        int random=RandomBoundaryAt00455580(0,4)-2;
        SELF_FIELD(float,0x1C)=float(double(random)*g_F1057_RandomDoubleAt00658A20+g_F1057_RandomBaseAt00657D00);
        SELF_FIELD(unsigned int,0x20)=SELF_FIELD(unsigned int,0x1C);
    }
    SELF_FIELD(signed short,0xD8)=short(SELF_FIELD(signed short,0xD8)-15);
    if (SELF_FIELD(signed short,0xD8)<SELF_FIELD(signed short,0xDC))
        SELF_FIELD(signed short,0xD8)=SELF_FIELD(signed short,0xDC);
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (SELF_FIELD(int,0x7C)!=0 && SELF_FIELD(int,0x7C)!=6 && F1024_PHASE(this).stageAt62==1) {
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        SetAuxActionAt0040FB40(2);
        SELF_FIELD(float,0x1C)=2.5f;
        SELF_FIELD(float,0x20)=2.5f;
        return;
    }
    if (F1024_PHASE(this).stageAt62>1) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)*g_F1055_FadeScaleAt006598A4;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)*g_F1055_FadeScaleAt006598A4;
        if (SELF_FIELD(unsigned char,0x11)>=25)
            SELF_FIELD(unsigned char,0x11)-=25;
        else {
            SELF_FIELD(unsigned char,0x11)=0;
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
