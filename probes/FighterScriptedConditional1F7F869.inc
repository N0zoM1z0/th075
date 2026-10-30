// F869 actual native game 1F7: 307B/90x86/11 physical original PE fields.
// Real stage4..6 U8+511 guard =>1F8 effect455B30; stage3 sprite337 Prepare3.
// True original function is whole fighter parent; no case exact CODE credit.
case 0x1F7: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_SubtractAt00657478;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (S16(0x62)>3 && S16(0x62)<7 && U8(0x511)==0x14) {
        SetNativeActionAt40FAC0(0x1F8);
        ResetAt453E20();
        NativeGameEffectAt455B30();
        return;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x337,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(3);
    }
    return;
}
