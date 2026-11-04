// F1128 original Japanese action 0x393 at PE
// 0051D4F1..0051D70F: 542 native CODE B /110 x86, same NONEXACT boss.
case 0x393: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0xDA)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        if (SELF_FIELD(signed short,0xD8)<2-int(g_F1113_DifficultyAt006714D0))
            ++SELF_FIELD(signed short,0xD8);
        else if (SELF_FIELD(signed short,0xDA)==0) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x391,0.0f,float(RandomBoundaryAt00455580(0,60)+380),1,1);
            SELF_FIELD(signed short,0xDA)=1;
            SELF_FIELD(signed short,0xD8)=0;
        } else {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x391,1280.0f,float(RandomBoundaryAt00455580(0,120)+240),-1,1);
            SELF_FIELD(signed short,0xDA)=0;
            SELF_FIELD(signed short,0xD8)=0;
        }
        SetAuxActionAt0040FB40(1);
    }
    return;
}
