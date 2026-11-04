// F1082: original Japanese 005129C1..00512BA7, 486 native CODE B/102 x86.
// Real game action 0x34A inside ONE nonexact 81KB CharacterObject Advance.
case 0x34A: {
    SELF_FIELD(unsigned int,0x44)=PARENT_FIELD(unsigned int,0x44);
    SELF_FIELD(float,0x48)=0.0f;
    SELF_FIELD(signed short,0x8A)=1;
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=2.5f;
        SELF_FIELD(float,0x20)=2.5f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0x1A)=0x4E2;
        SELF_FIELD(float,0x2C)=0.0f;
        SELF_FIELD(float,0x30)=0.0f;
        SELF_FIELD(float,0x28)=-80.0f;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(0x10);
    }
    if (SELF_FIELD(signed short,0x62)==1) {
        // The original compares parent action +0x60 with 0x2C0, then
        // checks the parent's distinct +0x62 WORD against 0x2C0 and 6.
        // Do not collapse this to a simpler presumed stage condition.
        if (PARENT_FIELD(signed short,0x60)!=0x2C0 ||
            (PARENT_FIELD(signed short,0x62)==0x2C0 &&
             PARENT_FIELD(signed short,0x62)>6)) {
            SetAuxActionAt0040FB40(2);
            return;
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
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1051_ScaleCeilingAt0065747C;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    return;
}
