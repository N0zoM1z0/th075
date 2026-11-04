// F1114: genuine original Japanese action 0x385 at 0051AFF0..0051B21D:
// 557 original CODE bytes/114 x86, in ONE NONEXACT 81KB game callable.
case 0x385: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(int,0x7C)==6) {
        ++SELF_FIELD(signed short,0x80);
        SELF_FIELD(int,0x7C)=0;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=2.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(float,0x30)=15.0f;
    }
    if (F1024_PHASE(this).stageAt62==2) {
        SELF_FIELD(float,0x1C)=float(RandomBoundaryAt00455580(0,6))*
            g_F1057_SpeedScaleAt006590B4+g_F1114_RandomOffsetAt00659094;
        SELF_FIELD(float,0x20)=(*(&SELF_FIELD(float,0x1C)))+g_F1051_ScaleCeilingAt0065747C;
    }
    if (F1024_PHASE(this).stageAt62>2)
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)*g_F1114_FadeAt00659240;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==3 && F1024_PHASE(this).frameAt64==0) {
        if (SELF_FIELD(signed short,0xD8)<9) {
            ++SELF_FIELD(signed short,0xD8);
            SetAuxActionAt0040FB40(2);
        } else {
            SELF_FIELD(float,0x1C)=1.8f;
            SELF_FIELD(float,0x20)=1.0f;
        }
    }
    return;
}
