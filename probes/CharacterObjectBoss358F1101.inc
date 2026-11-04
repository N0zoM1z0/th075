// F1101: native Japanese 00515C0E..00515E7F action 0x358,
// 625 original CODE B/143 x86, within one still-NONEXACT 81KB owner.
case 0x358: {
    if (PARENT_FIELD(signed short,0x60)>0x31 &&
        PARENT_FIELD(signed short,0x60)<0x96 &&
        SELF_FIELD(signed short,0x62)<0x17) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<10;++shot)
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SELF_FIELD(signed short,0xD8)=0;
        F1037_MOTION(this).xMotion=8.0f;
    }
    if (SELF_FIELD(signed short,0x62)==1 && SELF_FIELD(signed short,0x64)==0) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(2);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x359,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
    }
    if (F1037_POSITION(this).xPosition>g_F1101_RightAt00659424 ||
        F1037_POSITION(this).xPosition<g_F1101_LeftAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        if (SELF_FIELD(signed short,0xD8)<5) {
            ++SELF_FIELD(signed short,0xD8);
            SetAuxActionAt0040FB40(1);
        } else
            NativeParentExpiredAt0045B830();
    }
    return;
}
