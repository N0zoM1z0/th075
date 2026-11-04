// F1116: original Japanese action 0x387, PE 0051B5AF..0051B89F,
// 752 native CODE bytes/167 x86 within ONE still-NONEXACT 81KB boss.
case 0x387: {
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
        SELF_FIELD(float,0x30)=float(RandomBoundaryAt00455580(0,0x167));
        F1037_MOTION(this).xMotion=float(RandomBoundaryAt00455580(0,16)-8);
        F1037_MOTION(this).yMotion=float(RandomBoundaryAt00455580(0,6)+12);
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1116_YOffsetAt00659888;
        SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1116_AngleOffsetAt0065786C;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (SELF_FIELD(signed short,0x62)==1) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            SetAuxActionAt0040FB40(2);
            F1037_MOTION(this).yMotion=-F1037_MOTION(this).yMotion;
            F1037_POSITION(this).yPosition=0.0f;
        }
    }
    if (SELF_FIELD(signed short,0x62)==2) {
        if (SELF_FIELD(unsigned char,0x11)>15)
            SELF_FIELD(unsigned char,0x11)-=15;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
