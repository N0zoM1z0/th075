// F1062: actual Japanese PE 0050EA5B..0050ED70 action 0x338,
// 789 native CODE B /175 x86 in ONE nonexact 81KB CharacterObject.
case 0x338: {
    if (PARENT_FIELD(signed short,0x60)>0x45 &&
        PARENT_FIELD(signed short,0x60)<0x96) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<13;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        return;
    }
    if (PARENT_FIELD(signed short,0x60)==0x25C && PARENT_FIELD(signed short,0x62)==0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(float,0x1C)=0.0f;
        SELF_FIELD(float,0x20)=0.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0x80)=5;
        SELF_FIELD(int,0x7C)=0;
    }
    if (SELF_FIELD(signed short,0x62)==1) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1062_ScaleStepAt006583F8;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1062_ScaleStepAt006583F8;
    }
    if (SELF_FIELD(signed short,0x62)==2 && SELF_FIELD(signed short,0x64)==0)
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x337,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        if (SELF_FIELD(signed short,0xD8)<5 && SELF_FIELD(signed short,0x80)>0) {
            SELF_FIELD(int,0x7C)=0;
            ++SELF_FIELD(signed short,0xD8);
            SetAuxActionAt0040FB40(2);
            return;
        }
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==2 && SELF_FIELD(signed short,0x64)==0)
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(8);
    return;
}
