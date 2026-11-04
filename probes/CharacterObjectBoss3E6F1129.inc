// F1129 original native TH075 0x3E6 at 0051E215..0051E3F4:
// genuine 479 original CODE B /105 x86, one switch interior of
// the same still-NONEXACT original 81KB CharacterObject::Advance.
case 0x3E6: {
    if (PARENT_FIELD(signed short,0x60)!=0xD1 &&
        PARENT_FIELD(signed short,0x60)!=0xD2 &&
        F1024_PHASE(this).stageAt62<2) {
        SetAuxActionAt0040FB40(2);
        return;
    }
    SELF_FIELD(unsigned int,0x44)=PARENT_FIELD(unsigned int,0x44);
    F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+g_F1057_YOffsetAt00657888;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(float,0x28)=0.0f;
        SELF_FIELD(float,0x2C)=0.0f;
        SELF_FIELD(float,0x30)=0.0f;
    }
    SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)-g_F1057_SpeedBaseAt006590BC;
    SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)-g_F1057_SpeedBaseAt006590BC;
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1051_ScaleCeilingAt0065747C;
    if (F1024_PHASE(this).stageAt62==2)
        SELF_FIELD(unsigned char,0x11)=unsigned char(SELF_FIELD(unsigned char,0x11)-12);
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
