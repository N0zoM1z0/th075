// F1089: original Japanese 0x350, native 00514048..00514537,
// 1263 CODE B /273 x86 inside ONE nonexact original 81KB boss.
case 0x350: {
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        if (SELF_FIELD(signed short,0xD8)!=140)
            SELF_FIELD(signed short,0xD8)=0;
    }
    SetNativeTwoFloatsAt0040FB70(
        float(PARENT_FIELD(signed short,0xF0C))+
            g_F1085_ParentMultiplierAt0065989C*static_cast<const float&>(SELF_FIELD(float,0xC8)),
        float(SELF_FIELD(signed short,0xD8)));
    F1037_POSITION(this).xPosition=F1037_MOTION(this).xMotion+F1037_POSITION(PARENT).xPosition;
    F1037_POSITION(this).yPosition=(*(&F1037_MOTION(this).yMotion))*g_F1085_ParentYMultiplierAt00657F74+
        F1037_POSITION(PARENT).yPosition+g_F1085_YOffsetAt0065835C;
    if (SELF_FIELD(signed short,0xD8)<140)
        SELF_FIELD(signed short,0xD8)=short(SELF_FIELD(signed short,0xD8)+5);
    else
        SELF_FIELD(signed short,0xD8)=140;
    if ((PARENT_GRANDPARENT_FIELD(signed short,0x324)<=0 ||
        PARENT_FIELD(signed short,0x324)<=0 ||
        PARENT_FIELD(signed short,0x3A0)<=0) &&
        SELF_FIELD(signed short,0x62)<2)
        SetAuxActionAt0040FB40(2);
    if (PARENT_FIELD(signed short,0x60)==0x2C1 &&
        PARENT_FIELD(signed short,0x62)==2 &&
        SELF_FIELD(signed short,0x62)<2)
        SetAuxActionAt0040FB40(2);
    if (SELF_FIELD(signed short,0x62)==0) {
        if ((PARENT_FIELD(signed short,0x60)==0x192 && PARENT_FIELD(signed short,0x62)==4) ||
            (PARENT_FIELD(signed short,0x60)==0x260 && PARENT_FIELD(signed short,0x62)==4) ||
            (PARENT_FIELD(signed short,0x60)==0x261 && PARENT_FIELD(signed short,0x62)==4) ||
            (PARENT_FIELD(signed short,0x60)==0x262 && PARENT_FIELD(signed short,0x62)==4)) {
            for (int shot=0;shot<8;++shot) {
                PARENT_FIELD(float,0x314)=float(shot*45);
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x364,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
                    PARENT_FIELD(signed char,0x66),1);
            }
            SetAuxActionAt0040FB40(2);
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(4);
        }
    }
    if (SELF_FIELD(signed short,0x62)>1) {
        if (SELF_FIELD(unsigned char,0x11)>10)
            SELF_FIELD(unsigned char,0x11)-=10;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (SELF_FIELD(signed short,0x62)==1 &&
        PARENT_FIELD(signed short,0x60)==0x2C1 &&
        PARENT_FIELD(signed short,0x62)==3) {
        SetAuxActionAt0040FB40(0);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(20);
        return;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==2 && SELF_FIELD(signed short,0x64)==0) {
        SetAuxActionAt0040FB40(0);
        PARENT_FIELD(float,0x36C)=PARENT_FIELD(float,0x36C)-g_F1085_LastYAt006592A4;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(20);
    }
    return;
}
