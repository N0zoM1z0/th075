// F1091: actual Japanese original 0x352 at 0051497A..00514A9A,
// 288 CODE B /64 x86 inside ONE still-NONEXACT 81KB boss.
case 0x352: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=0.5f;
        SELF_FIELD(float,0x20)=0.5f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0xD8)=0;
    }
    SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1051_ScaleCeilingAt0065747C;
    SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1051_ScaleCeilingAt0065747C;
    if (F1024_PHASE(this).stageAt62>1) {
        if (SELF_FIELD(unsigned char,0x11)>20)
            SELF_FIELD(unsigned char,0x11)-=20;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
