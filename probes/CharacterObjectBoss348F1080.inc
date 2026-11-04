// F1080 real original Japanese action 0x348: PE 005125A8..00512815,
// 621 native CODE B / 132 x86 inside ONE still nonexact 81KB game callable.
case 0x348: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=0;
    }
    SetNativeTwoFloatsAt0040FB70(
        float(PARENT_FIELD(signed short,0xF0E))+
             g_F1080_ParentScaleAt006590A8*static_cast<const float&>(SELF_FIELD(float,0xC8)),
        float(SELF_FIELD(signed short,0xD8)));
    if (SELF_FIELD(signed short,0xD8)<120)
        SELF_FIELD(signed short,0xD8)=short(SELF_FIELD(signed short,0xD8)+20);
    if (SELF_FIELD(signed short,0xD8)>120)
        SELF_FIELD(signed short,0xD8)=120;
    F1037_POSITION(this).xPosition=F1037_MOTION(this).xMotion+F1037_POSITION(PARENT).xPosition;
    F1037_POSITION(this).yPosition=F1037_MOTION(this).yMotion+F1037_POSITION(PARENT).yPosition+g_F1057_YOffsetAt00657888;
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1080_AngleIncreaseAt00657850;
    if (F1024_PHASE(this).stageAt62==1) {
        if (PARENT_FIELD(signed short,0x60)!=0x2BE ||
            (PARENT_FIELD(signed short,0x60)==0x2BE &&
             PARENT_FIELD(signed short,0x62)>8))
            SetAuxActionAt0040FB40(2);
    }
    if (F1024_PHASE(this).stageAt62>1) {
        if (SELF_FIELD(unsigned char,0x11)>25)
            SELF_FIELD(unsigned char,0x11)-=25;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
