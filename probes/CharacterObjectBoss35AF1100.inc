// F1100 authentic Japanese original action 0x35A at 00515EF2..00515F65,
// 115 native CODE B /27 x86, inside ONE nonexact original 81KB boss.
case 0x35A: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.5f;
        SELF_FIELD(float,0x20)=1.5f;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
