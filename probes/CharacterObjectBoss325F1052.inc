// F1052: native 0050B654..0050B821, action 0x325, 461 real CODE B /100 x86.
// This is a case of the ONE original 81KB CharacterObject, still nonexact.
case 0x325: {
    if (PARENT_FIELD(signed short,0x60)>49 &&
        PARENT_FIELD(signed short,0x60)<150 &&
        F1024_PHASE(this).stageAt62<2) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<3;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48),1,1);
        }
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48),1,1);
        }
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(0x17);
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
