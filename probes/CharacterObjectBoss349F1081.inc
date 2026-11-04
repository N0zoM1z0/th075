// F1081: original Japanese game 00512815..005129C1, 428 original
// CODE bytes /94 x86 within ONE still nonexact CharacterObject boss.
case 0x349: {
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
    SELF_FIELD(unsigned int,0x44)=PARENT_FIELD(unsigned int,0x44);
    F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+g_F1081_ParentYOffsetAt00658268;
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)-g_F1081_AngleStepAt00657874;
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
