// F878 native 201 full 267B/80 x86/8 true original PE fields.
// Stage5 contains TWO separate guards: sprite336, Prepare2, then POS30.
// Native 65782C threshold and 658350 drop are both physical PE evidence.
case 0x201: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_F873GroundDropAt00658350;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x336,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(2);
    }
    if (S16(0x62)==5 && S16(0x64)==0)
        POS=30.0f;
    return;
}
