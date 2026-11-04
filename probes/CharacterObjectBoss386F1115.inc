// F1115: genuine original Japanese 0x386 game action at
// PE 0051B21D..0051B5AF, 914 native CODE B /195 ordered x86.
// One true state of ONE still-NONEXACT 81KB CharacterObject::Advance.
case 0x386: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        F1037_MOTION(this).xMotion=3.0f;
        F1037_MOTION(this).yMotion=0.0f;
    }
    if (SELF_FIELD(signed short,0x62)==1) {
        SELF_FIELD(float,0x1C)=float(RandomBoundaryAt00455580(0,4))*
            g_F1057_SpeedScaleAt006590B4+g_F1115_RandomDoubleAt006583B8;
        SELF_FIELD(unsigned int,0x20)=SELF_FIELD(unsigned int,0x1C);
        if (F1115_AbsFloatAt00412D90(F1037_POSITION(this).xPosition-
            F1037_POSITION(PARENT_GRANDPARENT).xPosition)<g_F1115_DistanceAt0065786C) {
            F1037_MOTION(this).xMotion=0.0f;
            SELF_FIELD(float,0x1C)=1.0f;
            SELF_FIELD(float,0x20)=1.0f;
            reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
            SetAuxActionAt0040FB40(2);
            return;
        }
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(10.0f);
        for (int shot=0;shot<12;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x387,
                (*(&F1037_POSITION(this).xPosition))+g_F1069_ParentYSecondAt00658264-float(RandomBoundaryAt00455580(0,80)),
                float(RandomBoundaryAt00455580(0,320)),
                SELF_FIELD(signed char,0x66),1);
        }
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==2 && SELF_FIELD(signed short,0x64)==0)
        SetAuxActionAt0040FB40(1);
    return;
}
