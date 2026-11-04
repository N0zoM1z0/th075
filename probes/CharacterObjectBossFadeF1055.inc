// F1055: one of the independently owned original 33C/33E/340/342/344
// character Object action interiors. Repeated C++ grammar: actual separate
// switch cases, no whole-game exact credit, native scaling and alpha fade.
case F1055_CASE: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
    }
    SELF_FIELD(float,0x1C) = SELF_FIELD(float,0x1C) * g_F1055_FadeScaleAt006598A4;
    SELF_FIELD(float,0x20) = SELF_FIELD(float,0x20) * g_F1055_FadeScaleAt006598A4;
    if (SELF_FIELD(unsigned char,0x11) >= 20)
        SELF_FIELD(unsigned char,0x11) -= 20;
    else
        SELF_FIELD(unsigned char,0x11) = 0;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
