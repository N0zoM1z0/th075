// F1069: native Japanese original action 0x331 at
// 0050D53A..0050D88E, 852 original CODE B /185 actual x86 instructions.
// Genuine gameplay inside ONE still nonexact 81KB original CharacterObject.
case 0x331: {
    SELF_FIELD(unsigned char,0x66)=PARENT_FIELD(unsigned char,0x66);
    if (PARENT_FIELD(signed short,0x60)>0x95 &&
        PARENT_FIELD(signed short,0x60)<0x9A &&
        SELF_FIELD(signed short,0x62)==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(SELF_FIELD(signed char,0x66)*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1069_ParentYFirstAt00659138;
    }
    if (PARENT_FIELD(signed short,0x60)>0x99 &&
        PARENT_FIELD(signed short,0x60)<0x9E &&
        SELF_FIELD(signed short,0x62)==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(SELF_FIELD(signed char,0x66)*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1069_ParentYSecondAt00658264;
    }
    if (PARENT_FIELD(signed short,0x60)==0x9E &&
        SELF_FIELD(signed short,0x62)==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(SELF_FIELD(signed char,0x66)*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1057_YOffsetAt00657888;
    }
    if ((PARENT_FIELD(signed short,0x60)<0x96 ||
         PARENT_FIELD(signed short,0x60)>0x9E) &&
        SELF_FIELD(signed short,0x62)==0) {
        SetAuxActionAt0040FB40(1);
        PARENT_FIELD(signed short,0xF0A)=0;
    }
    if (SELF_FIELD(signed short,0x62)==0 &&
        SELF_FIELD(signed short,0x64)==0 &&
        SELF_FIELD(signed short,0xD8)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(float,0x2C)=50.0f;
        SELF_FIELD(signed short,0xD8)=1;
    }
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1057_NudgeAt00657480;
    if (SELF_FIELD(signed short,0x62)>0) {
        if (SELF_FIELD(unsigned char,0x11)>30)
            SELF_FIELD(unsigned char,0x11)-=30;
        else
            SELF_FIELD(unsigned char,0x11)=0;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (SELF_FIELD(signed short,0x62)==1 && SELF_FIELD(signed short,0x64)==0)
        SetAuxActionAt0040FB40(0);
    return;
}
