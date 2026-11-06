// F1057: each of 33B/33D/33F/341/343 is 1908 ORIGINAL CODE B /402 x86
// in the ONE nonexact 0050A580 original CharacterObject Advance.
// Original PE proves the five share opcode, width, GPR, field/call policy.
// Only physical native stack scratch owners differ per independent case,
// and the native next-state sprite IDs are 33C/33E/340/342/344.
// The C++ source declares real per-case values; no fake locals/ASM.
// Original actor X/Y, target grandparent X/Y and actual native game calls.
case F1057_CASE: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (PARENT_FIELD(signed short,0x60)>49 &&
        PARENT_FIELD(signed short,0x60)<150 &&
        F1024_PHASE(this).stageAt62<2) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<3;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4, SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3, SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        return;
    }
    if (SELF_FIELD(int,0x7C)==5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(signed short,0x80)=3;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=10;
        SELF_FIELD(signed short,0xDA)=0;
        SELF_FIELD(signed short,0xDE)=0;
        SELF_FIELD(signed short,0xDC)=short(SELF_FIELD(float,0xC8));
    }
    if (F1024_PHASE(this).stageAt62<=1) {
        SELF_FIELD(signed short,0xDA)=short(F1057_FloatAtan2At00483300(
            (F1037_POSITION(PARENT_GRANDPARENT).yPosition-F1037_POSITION(this).yPosition)+g_F1057_YOffsetAt00657888,
            (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition)*float(SELF_FIELD(signed char,0x66))) /
            g_F1057_AngleDivAt00657828);
        if (SELF_FIELD(signed short,0xDA)>SELF_FIELD(signed short,0xDC)+10)
            SELF_FIELD(signed short,0xDC)=short(SELF_FIELD(signed short,0xDC)+1);
        if (SELF_FIELD(signed short,0xDA)<SELF_FIELD(signed short,0xDC)-10)
            SELF_FIELD(signed short,0xDC)=short(SELF_FIELD(signed short,0xDC)-1);
        if (SELF_FIELD(signed short,0xDC)>90)
            SELF_FIELD(signed short,0xDC)=90;
        if (SELF_FIELD(signed short,0xDC)<-90)
            SELF_FIELD(signed short,0xDC)=-90;
    }
    if (F1024_PHASE(this).stageAt62<=1) {
        SetNativeTwoFloatsAt0040FB70(
            float(SELF_FIELD(signed short,0xDC)),
            float(SELF_FIELD(signed short,0xD8))*g_F1057_SpeedScaleAt006590B4+g_F1057_SpeedBaseAt00657CBC);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            F1057_NEXT_CASE, SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
        SELF_FIELD(float,0x1C)=float(double(RandomBoundaryAt00455580(0,4)-2)*
            g_F1057_RandomDoubleAt00658A20+g_F1057_RandomBaseAt00657D00);
        SELF_FIELD(unsigned int,0x20)=SELF_FIELD(unsigned int,0x1C);
    }
    SELF_FIELD(signed short,0xD8)=short(SELF_FIELD(signed short,0xD8)+2);
    if (F1024_PHASE(this).stageAt62>0 && SELF_FIELD(signed short,0xDA)<60) {
        if ((*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1057_YOffsetAt00657888<F1037_POSITION(this).yPosition)
            SELF_FIELD(float,0xC8)=SELF_FIELD(float,0xC8)+g_F1057_NudgeAt00657480;
        if ((*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1057_YOffsetAt00657888>F1037_POSITION(this).yPosition)
            SELF_FIELD(float,0xC8)=SELF_FIELD(float,0xC8)-g_F1057_NudgeAt00657480;
        ++SELF_FIELD(signed short,0xDA);
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*SELF_FIELD(float,0x50)+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (SELF_FIELD(int,0x7C)!=0 && SELF_FIELD(int,0x7C)!=6 && F1024_PHASE(this).stageAt62==1) {
        if (SELF_FIELD(signed short,0x80)==0 || SELF_FIELD(int,0x7C)!=4) {
            SELF_FIELD(float,0x50)=0.0f;
            SELF_FIELD(float,0x54)=0.0f;
            SetAuxActionAt0040FB40(2);
            SELF_FIELD(float,0x1C)=2.5f;
            SELF_FIELD(float,0x20)=2.5f;
            return;
        }
        if (SELF_FIELD(signed short,0x80)>0 && SELF_FIELD(int,0x7C)==4 && SELF_FIELD(signed short,0x80)>0)
            SELF_FIELD(int,0x7C)=0;
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
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
