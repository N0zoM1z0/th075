// F1090: genuine original 0x351 at 00514537..0051497A, 1091 original
// CODE B /246 native x86, inside ONE still-NONEXACT CharacterObject.
case 0x351: {
    F1037_POSITION(this).xPosition = F1037_POSITION(PARENT).xPosition+float(PARENT_FIELD(signed char,0x66)*20);
    ++SELF_FIELD(signed short,0xDA);
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0x80)=99;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0xDA)=0;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=-1.0f;
    }
    if (PARENT_FIELD(signed short,0x62)>6 && F1024_PHASE(this).stageAt62<6) {
        SetAuxActionAt0040FB40(F1024_PHASE(this).stageAt62+5);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(15);
    }
    if (F1024_PHASE(this).stageAt62>5 && F1024_PHASE(this).stageAt62<11) {
        F1037_MOTION(this).yMotion=0.0f;
        if (SELF_FIELD(float,0x1C)>=g_F1070_InitSpeedAt00657858) {
            SetAuxActionAt0040FB40(F1024_PHASE(this).stageAt62+5);
            return;
        }
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1057_NudgeAt00657480;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1057_NudgeAt00657480;
    }
    if (F1024_PHASE(this).stageAt62>10 && F1024_PHASE(this).stageAt62<16) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x33A,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
    }
    if (F1024_PHASE(this).stageAt62>15) {
        if (SELF_FIELD(unsigned char,0x11)>5)
            SELF_FIELD(unsigned char,0x11)-=5;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (SELF_FIELD(signed short,0xDA)==35) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnSevenAt00453B50(
            0x352,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1,0,1);
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        SetAuxActionAt0040FB40(16);
        return;
    }
    if (F1024_PHASE(this).frameAt64==0) SELF_FIELD(int,0x7C)=0;
    if (F1024_PHASE(this).stageAt62==6 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    if (F1024_PHASE(this).stageAt62==11 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(6);
    if (F1024_PHASE(this).stageAt62==16 && F1024_PHASE(this).frameAt64==0 &&
        PARENT_FIELD(signed short,0x60)==0x2BF && PARENT_FIELD(signed short,0x62)>6 && PARENT_FIELD(signed short,0x62)<9) {
        SetAuxActionAt0040FB40(11);
    }
    return;
}
